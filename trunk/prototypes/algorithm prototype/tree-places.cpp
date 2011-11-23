/*
tree-places: A program to summarize the places of a tree.
    Copyright (C) 2009  Daniel Gutson, FuDePAN

    tree-places is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    tree-places is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with tree-places.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iterator> // for debug!
#include "phylopp.h"

#include <stdlib.h>
#include <cmath>
#include <mili/mili.h>
using namespace std;

enum Arguments
{
    ProgName = 0,
    TreeName,
    PlacesName,
    LeafName,
    // ---------------
    MinNumberOfArguments = LeafName,
    MaxNumberOfArguments
};

typedef string Place;
typedef map<Place, float> PlacesSet;

class PlacesNode : public TreeNodeBase<PlacesNode>
{
    PlacesSet places_set;
    float distribution;
    Place place;

    void merge_place(const PlacesSet& child_places_set);

    virtual void set_data(std::stringstream& ss)
    {
        ss >> place;
        //std::cout << name << "," << place << endl;
    }

public:
    PlacesNode(TreeData<PlacesNode>& td, size_t depth)
        : TreeNodeBase<PlacesNode>(td, depth)
    {}

    ~PlacesNode()
    {
        delete_container(children);
    }

    void calc_sets();
    void calc_distribution();
    float get_distribution() const { return distribution; }

    void show_places_set() const
    {
        cerr << " [ ";
        for (PlacesSet::const_iterator it = places_set.begin(); it != places_set.end(); ++it)
            cerr << it->first << ":" << it->second << " ";
        cerr << "] ";
    }

    void show(size_t lvl) const
    {
        cerr << string(lvl, '-') << name;
        show_places_set();
        cerr << " (" << distribution << ")" << endl;
        for(list<PlacesNode*>::const_iterator it = children.begin(); it != children.end(); ++it)
            (*it)->show(lvl+1);
    }
};

class DistributionCalc
{
public:
    float calc(const PlacesSet& places_set)
    {
        const size_t places_count = places_set.size();

        if (places_count == 1)
            return 1.0f;
        else
        {
            // calc max and sum:
            float sum  = 0;
            const float n = float(places_count);
            const float denom = (n-1 + square(n-1));
            const float inv_n = 1.0f / n;

            for (PlacesSet::const_iterator place = places_set.begin(); place != places_set.end(); ++place)
                sum += square(place->second - inv_n);

            return std::sqrt(sum / denom) * n;
        }
    }
};
static DistributionCalc distribution_calc;

static void usage();
static void calc_threshold(PlacesNode* root);
static void do_upstream(const PlacesNode* leaf);

int main(int argc, char* argv[])
{
    int ret = EXIT_FAILURE;
    size_t tree_num = 0;

    if (!in_range(argc, int(MinNumberOfArguments), int(MaxNumberOfArguments)))
        usage();
    else
    {
        TreesCollection<PlacesNode> collection;

        if (load_trees(argv[TreeName], &collection) && 
            load_data(argv[PlacesName], &collection))
        {
            foreach_tree(collection, tree, PlacesNode)
            {
                tree_num++;
                cout << "Tree #" << tree_num << "\tDepth: " << tree->get_depth() << endl;
                tree->get_root()->calc_sets();
                tree->get_root()->calc_distribution();
                calc_threshold(tree->get_root());
                tree->get_root()->show(0);

                cout << "Leaves:" << endl;
                cout << "\tName\tDepth" << endl;
                foreach_leaf(tree, leaf, PlacesNode)
                {
                    cout << "\t" << leaf->get_name() << "\t" << leaf->get_depth() << endl;
                }

                if (argc == MaxNumberOfArguments)
                    do_upstream(tree->get_leaf(argv[LeafName]));

                cout << endl;
            }

            ret = EXIT_SUCCESS;
        }
    }

    return ret;
}

void calc_threshold(PlacesNode* root)
{
    //root.calc_distribution(); TODO
}

void PlacesNode::calc_sets()
{
    // initialize mine:

    if (!name.empty())  // leaf
    {
        if (place.empty())
            place = "UNKNOWN";

        places_set[place] = 1.0f;
    }

    // merge with children:
    foreach_child(child)
    {
        child->calc_sets();
        merge_place(child->places_set);
    }
}

void PlacesNode::merge_place(const PlacesSet& child_places)
{
    const float children_count = float(children.size());

    // for each element in child_places_set, add it in our set:
    for(PlacesSet::const_iterator childit = child_places.begin();
        childit != child_places.end();
        ++childit)
    {
        PlacesSet::iterator myit = places_set.find(childit->first);
        if (myit != places_set.end())
        {
            // already found: add occurrences
            myit->second += childit->second / children_count;
        }
        else
        {
            // bring it as it is
            places_set[childit->first] = childit->second / children_count;
        }
    }
}

void PlacesNode::calc_distribution()
{
    distribution = distribution_calc.calc(places_set);

    // merge with children:
    foreach_child(child)
    {
        child->calc_distribution();
    }
}

void do_upstream(const PlacesNode* leaf)
{
    if (leaf == NULL)
        cout << "Leaf not found" << endl;
    else
    {
        const PlacesNode* node = leaf;
        cout << "Upstream: " << leaf->get_name() << endl;
        cout << "\tPlaces\tDistribution Factor" << endl;
        while (node != NULL)
        {
            node->show_places_set();
            cout << "\t" << node->get_distribution();
            node = node->get_parent();
            cout << endl;            
        }
    }
}

void usage()
{
    cerr << "Usage: tree-places treefile placesfile [leafname]" << endl;
}

