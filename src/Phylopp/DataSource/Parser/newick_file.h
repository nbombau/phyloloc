#ifndef NEWICK_FILE_H
#define NEWICK_FILE_H

#include <string>

#include "../../../Domain/ITree.h"
#include "../../../Domain/ListIterator.h"
#include <iostream>
#include <fstream>
//#include "../mili/mili.h"
#include <mili/mili.h>


namespace Parser{
    
    static inline bool is_namechar(char c)
    {
        return in_range(c, '0', '9') ||
              in_range(c, 'a', 'z') ||
              in_range(c, 'A', 'Z') ||
              c == '_' ||
              c == '-';
    }

    static inline bool is_branchlen_char(char c)
    {
        return in_range(c, '0', '9') ||
              c == '.';
    }

    static std::string consume_name(const char*& character)
    {
        std::string ret;
        while(is_namechar(*character))
        {
            ret += *character;
            ++character;
        }

        return ret;
    }

    static void consume_whitespace(const char*& character)
    {
        while(*character == ' ' || *character == '\t')
            ++character;
    }

    static float consume_branch_length(const char*& character)
    {
        consume_whitespace(character);
        float ret=0.0;
        if (*character == ':')
        {
            ++character;
            std::string branchLenStr;
            while(is_branchlen_char(*character))
            {
                branchLenStr += *character;
                ++character;
            }
            ret=atof(branchLenStr.c_str()); 
            //if its an invalid number, branchlength will be 0.0
        }
        return ret;
    }

    template <class T> 
    class NewickParser
    {
    public:

        bool loadNewickFile(const std::string fname,Domain::ITreeCollection<T>& trees)
        {
            std::ifstream f(fname.c_str());

            if (f)
            {
                const char* ptr;
                std::string tree_str, line;
                bool ret(true);

                while(getline(f, line))
                    tree_str += line;

                ptr  = tree_str.c_str();
                do
                {
                    Domain::ITree<T>* tree = trees.addTree();
                    ret = load_node(ptr, tree->getRoot());

                    if (ret)
                    {
                        consume_whitespace(ptr);
                        ret = (*ptr == ';');
                        if (!ret)
                            std::cerr << "Missing tree separator (;)." << std::endl;
                        else
                            ++ptr;
                    }
                }while(ret && *ptr != 0);

                return ret;
            }
            else
            {
                std::cerr << "Tree file " << fname << " not found\n";
                return false;
            }
        }

        void saveNewickFile(const std::string fname,Domain::ITree<T>*phyloTree)
        {
            std::ofstream os(fname.c_str());
            saveTree(phyloTree->getRoot(), os);
            os.close();
        }

    private:

        bool load_node(const char*& character, T* node)
        {
            bool ret = true;
            std::string name;
            float branchLength=0.0;

            // output: either ',' or ')' (depending on the node type)

            consume_whitespace(character);

            switch (*character)
            {
                case '(':
                    // we are nonleaf. Load new child.
                    ret = load_children(++character, node); // leaves in a parent
                    character++;
                    if (ret) //consume nonleaf name and branchlength, if present
                    {
                        name = consume_name(character);
                        node->setName(name);
                        branchLength = consume_branch_length(character);
                        node->setBranchLength(branchLength);
                    }
                    break;

                case ',':
                case ')':
                    //allow nameless nodes: dont consume character.
                    node->setName("");
                    node->setBranchLength(0.0);
                    break;
                case 0:
                    ret = false;
                    std::cerr << "Malformed expression\n";
                    break;

                default:
                    // we are leaf.
                    name = consume_name(character);
                    node->setName(name);
                    branchLength = consume_branch_length(character);
                    node->setBranchLength(branchLength);

            }

            return ret;
        }

        bool load_children(const char*& character, T* parent)
        {
            T* child;
            bool keep_reading;
            bool ret;

            // input: first char of first child.
            // output: ')'

            do
            {
                child = parent->addChild();
                ret = load_node(character, child);

                if (ret)
                {
                    consume_whitespace(character);

                    switch (*character)
                    {
                        case ',':
                            keep_reading = true;
                            ++character;
                            break;
                        case ')':
                            keep_reading = false;
                            break;
                        default:
                            ret = false;
                            std::cerr << "Malformed expression: expected ')' or ',', read '" << *character << "'\n";
                    }
                }
            }while(keep_reading && ret);

            return ret;
        }



        void saveTree(T *node,std::ostream& os)
        {
            if (node->isLeaf())
            {
                os << node->getName();
            }
            else
            {
                os << '(';
                Domain::ListIterator<T>* iter = node->getChildrenIterator();

                while (!iter->end())
                {
                    saveTree(&iter->get(),os);

                    iter->next();

                    if (!iter->end())
                    {
                        os << ',';
                    }
                }
                delete iter;
                os << ')';

            }
            os << ':' << node->getBranchLength();
        }
    };
}

#endif