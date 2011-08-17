/*
NewickParser: a parser for loading trees in newick format from a file


    Copyright (C) 2011 Emmanuel Teisaire, Nicolás Bombau, Carlos Castro, Damián Domé, FuDePAN

    This file is part of the Phyloloc project.

    Phyloloc is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Phyloloc is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Phyloloc.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef NEWICK_PARSER_H
#define NEWICK_PARSER_H

#include <string>
#include <iostream>
#include <mili/mili.h>
#include "Domain/ITree.h"
#include "Domain/ListIterator.h"
#include "Domain/LocationManager.h"
#include "TreeValidationPolicies.h"

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
                               "The input is not correctly formed");


/**
* MissingDataException
* --------------------
* Description: Exception used when missing data in leaf nodes is not allowed
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(MissingDataException,
                               TreeFileExceptionHierarchy,
                               "Missing data not allowed. All terminal nodes should have name");


template < class T, class ValidationPolicy = DefaultValidationPolicy >
class NewickParser
{
public:

    /**
     * Constructor
     * 
     * @param validationPolicy policy used to validate nodes
     */
    NewickParser(const ValidationPolicy& validationPolicy = ValidationPolicy()) : validationPolicy(validationPolicy) {}

    /**
     * Loads a tree in newick format from a file
     * 
     * @param fname file path
     * @param locationManager Manager of locations and distances between locations
     * @param trees Collection to be filled with the parsed trees
     */
    void loadNewickFile(const std::string& fname, const Locations::LocationManager locationManager, Domain::ITreeCollection<T>& trees)
    {
        std::ifstream f(fname.c_str());

        if (!f)
            throw TreeFileNotFound();

        std::string line;

        currentLineNumber = 1;
        while (getline(f, line))
        {
            std::string tree_str = line;

            character = tree_str.c_str();

            do
            {
                Domain::ITree<T>* tree = trees.addTree();
                load_node(locationManager, tree->getRoot());
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
    ValidationPolicy validationPolicy;
    VariantsSet set;
    const char* character;

    /****************************************************
     ** This variable and method will no longer be
     ** needed when mili generic exceptions is updated.
     *********       mili issue 35              ********/

    unsigned int currentLineNumber;

    std::string getLineNumberText() const
    {
        std:: stringstream s;
        s << "Line: " << currentLineNumber;
        return s.str();
    }
    /****************************************************/

    /**
     * Loads a node and all its children recursively
     * 
     * @param locationManager Manager of locations and distances between locations
     * @param node Node to be filled
     */
    void load_node(const Locations::LocationManager locationManager, T* node)
    {
        std::string name;
        float branchLength = 0.0f;
        Locations::LocationId locationId;
        // Output: either ',' or ')' (depending on the node type)
        consume_whitespace();

        switch (*character)
        {
            case '(':
                // We are nonleaf. Load new child.
                ++character;
                load_children(locationManager, node); // leaves in a parent
                character++;
                name = consume_name();
                node->setName(name);
                branchLength = consume_branch_length();
                node->setBranchLength(branchLength);
                
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
                // Set location id, if exists, for the node
                locationId = locationManager.getNameLocationId(name);
                if (locationId != Locations::LOCATION_NOT_FOUND)
                {                                
                    node->setLocationId(locationId);
                }
                //else no location is set for that node
        }
        if (!validationPolicy.validate(node))
            throw MissingDataException(getLineNumberText());
    }

    /**
     * Loads a nodes children
     * 
     * @param locationManager Manager of locations and distances between locations
     * @param parent node whose children will be loaded
     */
    void load_children(const Locations::LocationManager locationManager, T* parent)
    {
        T* child;
        bool keep_reading = true;

        // Input: first char of first child.
        // output: ')'
        do
        {
            child = parent->template addChild<T>();
            load_node(locationManager, child);
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
                throw MalformedExpression(getLineNumberText());

        }
        return ret;
    }
};

#endif
