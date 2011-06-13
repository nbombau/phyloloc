#ifndef NEWICK_FILE_H
#define NEWICK_FILE_H

#include <string>
#include <iostream>
#include <fstream>
#include <mili/mili.h>
#include "Domain/ITree.h"
#include "Domain/ListIterator.h"

typedef std::string NodeName;

template <class T>
class NewickParser
{
public:

     /**
     * Class: TreeFileNotFound
     * --------------------
     * Description: Exception used when the nodes separator its not found
     */  
    class MissingTreeSeparator : public std::exception 
    {
        virtual const char* what() const throw()
        {
            return "Missing tree separator (;)";
        } 
    };

     /**
     * Class: TreeFileNotFound
     * --------------------
     * Description: Exception used when the input file is missing.
     */   
    class TreeFileNotFound : public std::exception 
    { 
        virtual const char* what() const throw()
        {
            return "The input tree file does not exist";
        }
    };  

     /**
     * Class: MalformedExpression
     * --------------------
     * Description: Exception used when the input file is missing.
     */   
    class MalformedExpression : public std::exception 
    { 
        virtual const char* what() const throw()
        {
            return "The input is not correctly formed";
        }
    };  

    void loadNewickFile(const std::string& fname, Domain::ITreeCollection<T>& trees, VariantsSet& set)
    {
        std::ifstream f(fname.c_str());

        this->set = set;
        
        if (f)
        {
            std::string tree_str, line;
            bool ret(true);

            while (getline(f, line))
                tree_str += line;

            character = tree_str.c_str();
            
            do
            {
                Domain::ITree<T>* tree = trees.addTree();
                load_node(tree->getRoot());
                consume_whitespace();
                ret = (*character == ';');
                if (!ret)
                    throw MissingTreeSeparator();
                else
                    ++character;
                
            }
            while (ret && *character != 0);
        }
        else
        {
            throw TreeFileNotFound();
        }       
    }

    void saveNewickFile(const std::string& fname, Domain::ITreeCollection<T>& trees)
    {
        Domain::ListIterator< Domain::ITree<T> >* iter = trees.getIterator();

        std::ofstream os(fname.c_str());
        
        while (!iter->end())
        {
            Domain::ITree<T>* tree = iter->get();
            saveTree(tree->getRoot(), os);
            os << ";\n";
            iter->next();
        }
        delete iter;
    }

private:
    VariantsSet set;
    const char *character;
    
    void load_node(T* node)
    {
        bool ret;
        std::string name;
        float branchLength = 0.0;

        // Output: either ',' or ')' (depending on the node type)
        consume_whitespace();
        
        switch (*character)
        {
            case '(':
                // We are nonleaf. Load new child.
                ++character;
                ret = load_children(node); // leaves in a parent
                character++;
                if (ret) //Consume nonleaf name and branchlength, if present
                {
                    name = consume_name();
                    node->setName(name);
                    branchLength = consume_branch_length();
                    node->setBranchLength(branchLength);                   
                    // Set location, if exists, for the node
                    set_location(name, set, node);
                }
                else
                {
                    throw MalformedExpression();
                }    
                break;
            case ',':
            case ')':
                //Allow nameless nodes: dont consume character.
                node->setName("");
                node->setBranchLength(0.0);
                break;
            case 0:
                throw MalformedExpression();
                break;
            default:
                // We are leaf.
                name = consume_name();
                node->setName(name);
                branchLength = consume_branch_length();
                node->setBranchLength(branchLength);             
                // Set location, if exists, for the node
                set_location(name, set, node);
        }
    }

    void set_location(const NodeName name, const VariantsSet set, T* node)
    {
        std::string location;
        try
        {
            set.get_element(name, location);
            node->setLocation(location);
        }
        catch(const BadElementName&) { }         
    }

    bool load_children(T* parent)
    {
        T* child;
        bool keep_reading=true;
        bool ret=true;

        // Input: first char of first child.
        // output: ')'
        do
        {
            child = parent->addChild();
            load_node(child);
            consume_whitespace();
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
                }
        }
        while (keep_reading && ret);

        return ret;
    }

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

    std::string consume_name()
    {
        std::string ret;
        while (is_namechar(*character))
        {
            ret += *character;
            ++character;
        }

        return ret;
    }

    void consume_whitespace()
    {
        while (*character == ' ' || *character == '\t')
            ++character;
    }

    float consume_branch_length()
    {
        consume_whitespace();
        float ret = 0.0f;
        if (*character == ':')
        {
            ++character;
            std::string branchLenStr;
            while (is_branchlen_char(*character))
            {
                branchLenStr += *character;
                ++character;
            }

            if (!from_string(branchLenStr, ret))
                ret = 0.0f;

        }
        return ret;
    }

    static void saveTree(T* node, std::ostream& os)
    {
       
        if (!node->isLeaf())
        {
            os << '(';
            Domain::ListIterator<T>* iter = node->getChildrenIterator();

            while (!iter->end())
            {
                saveTree(iter->get(), os);

                iter->next();

                if (!iter->end())
                {
                    os << ',';
                }
            }
            delete iter;
            os << ')';

        }
        os << node->getName() << ':' << node->getBranchLength();
    }
};

#endif
