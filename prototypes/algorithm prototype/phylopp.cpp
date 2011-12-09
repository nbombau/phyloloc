/*
phylopp.cpp: library implementation to process phylogenetic trees.
    Copyright (C) 2009  Daniel Gutson, FuDePAN

    phylopp.h is part of phylopp.

    phylopp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    phylopp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with phylopp.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "phylopp.h"

bool load_data(const string& file, TreesCollectionInterface* collection)
{
    ifstream f(file.c_str());
    bool ret(true);
    vector<string> values;

    if (f)
    {
        DataBag bag;
        stringstream* ss;
        NodeName name;

        while (f >> Separator(values, ',') && ret)
        {
            if (values.size() == 1)
            {
                ret = false;
                cerr << "Malformed data file: line has no data.\n";
            }
            else if (values.size() > 1)
            {
                vector<string>::const_iterator it = values.begin();

                name = trim(*it);

                ss = new stringstream;
                for (++it; it != values.end(); ++it)
                    (*ss) << *it;

                bag[name] = ss;
                values.clear();
            }
        }

        collection->set_data_from_bag(bag);
    }
    else
    {
        ret = false;
        cerr << "Data file " << file << " not found\n";
    }

    return ret;
}

static bool load_node(const char*& character, TreeNodeInterface* parent);
static bool load_children(const char*& character, TreeNodeInterface* parent);

static void consume_whitespace(const char*& character)
{
    while (*character == ' ' || *character == '\t')
        ++character;
}


bool load_trees(const string& file, TreesCollectionInterface* collection)
{
    ifstream f(file.c_str());

    if (f)
    {
        const char* ptr;
        string tree_str, line;
        bool ret(true);
        TreeInterface* tree;

        while (getline(f, line))
            tree_str += line;

        ptr  = tree_str.c_str();
        do
        {
            tree = collection->new_tree();
            ret = load_node(ptr, tree->get_root_interface());

            if (ret)
            {
                consume_whitespace(ptr);
                ret = (*ptr == ';');
                if (!ret)
                    cerr << "Missing tree separator (;)." << endl;
                else
                    ++ptr;
            }
        }
        while (ret && *ptr != 0);

        return ret;
    }
    else
    {
        cerr << "Tree file " << file << " not found\n";
        return false;
    }
}

static inline bool is_namechar(char c)
{
    return in_range(c, '0', '9') ||
           in_range(c, 'a', 'z') ||
           in_range(c, 'A', 'Z') ||
           c == '_' ||
           c == '-';
}

static string consume_name(const char*& character)
{
    string ret;
    while (is_namechar(*character))
    {
        ret += *character;
        ++character;
    }

    return ret;
}

bool load_node(const char*& character, TreeNodeInterface* node)
{
    bool ret = true;
    NodeName name;

    // output: either ',' or ')' (depending on the node type)

    consume_whitespace(character);

    switch (*character)
    {
        case '(':
            // we are nonleaf. Load new child.
            ret = load_children(++character, node); // leaves in a parent
            character++;
            break;

        case ',':
        case ')':
        case 0:
            ret = false;
            cerr << "Malformed expression: missing node name\n";
            break;

        default:
            // we are leaf.
            name = consume_name(character);
            node->set_name(name);
    }

    return ret;
}

bool load_children(const char*& character, TreeNodeInterface* parent)
{
    TreeNodeInterface* child;
    bool keep_reading;
    bool ret;

    // input: first char of first child.
    // output: ')'

    do
    {
        child = parent->add_child();
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
                    cerr << "Malformed expression: expected ')' or ',', read '" << *character << "'\n";
            }
        }
    }
    while (keep_reading && ret);

    return ret;
}

