#ifndef NEWICK_PARSER_H
#define NEWICK_PARSER_H

#include <string>
#include <iostream>
#include <mili/mili.h>
#include "Domain/ITree.h"
#include "Domain/ListIterator.h"

typedef std::string NodeName;

class TreeFileExceptionHierarchy {};

typedef GenericException<TreeFileExceptionHierarchy> TreeFileException;

/**
* MissingTreeSeparator
* --------------------
* Description: Exception used when the nodes separator its not found
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(MissingTreeSeparator,
                               TreeFileExceptionHierarchy,
                               "Missing tree separator (;)");

/**
* TreeFileNotFound
* --------------------
* Description: Exception used when the input file is missing.
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(TreeFileNotFound,
                               TreeFileExceptionHierarchy,
                               "The input tree file does not exist.");

/**
* MalformedExpression
* --------------------
* Description: Exception used when the input file is missing.
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(MalformedExpression,
                               TreeFileExceptionHierarchy,
                               "the input is not correctly formed");

template <class T>
class NewickParser
{
public:

    void loadNewickFile(const std::string& fname, Domain::ITreeCollection<T>& trees, VariantsSet& set)
    {
        std::ifstream f(fname.c_str());

        if (!f)
            throw TreeFileNotFound();

        this->set = set;

        std::string line;

        currentLineNumber=1;
        while (getline(f, line))
        {
            std::string tree_str = line;

            character = tree_str.c_str();

            do
            {
                Domain::ITree<T>* tree = trees.addTree();
                load_node(tree->getRoot());
                consume_whitespace();
                if (*character != ';')
                    throw MissingTreeSeparator(getLineNumberText());
                else
                    ++character;
            }
            while (*character != 0);

            currentLineNumber++;
        }
    }

private:
    VariantsSet set;
    const char* character;

    /****************************************************
     ** This variable and method will no longer be
     ** needed when mili generic exceptions is updated **/

    unsigned int currentLineNumber;

    std::string getLineNumberText() const
    {
        std:: stringstream s;
        s << "Line: " << currentLineNumber;
        return s.str();
    }
    /****************************************************/

    void load_node(T* node)
    {
        std::string name;
        float branchLength = 0.0f;

        // Output: either ',' or ')' (depending on the node type)
        consume_whitespace();

        switch (*character)
        {
            case '(':
                // We are nonleaf. Load new child.
                ++character;
                load_children(node); // leaves in a parent
                character++;

                name = consume_name();
                node->setName(name);
                branchLength = consume_branch_length();
                node->setBranchLength(branchLength);
                // Set location, if exists, for the node
                set_location(name, set, node);

                break;
            case ',':
            case ')':
                //Allow nameless nodes: dont consume character.
                node->setName("");
                node->setBranchLength(0.0f);
                break;
            case 0:
                throw MalformedExpression(getLineNumberText());
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

    void set_location(const NodeName& name, const VariantsSet& set, T* node)
    {
        std::string location;
        try
        {
            set.get_element(name, location);
            node->setLocation(location);
        }
        catch (const BadElementName&) { }
    }

    void load_children(T* parent)
    {
        T* child;
        bool keep_reading = true;

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
                    throw MalformedExpression(getLineNumberText());
            }
        }
        while (keep_reading);
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
};

#endif
