/*
phylopp.h: A header library to process phylogenetic trees.
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

#ifndef PHYLOPP_H
#define PHYLOPP_H

#include <stdlib.h>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <mili/mili.h>
using namespace std;

typedef string NodeName;

typedef map<NodeName, stringstream*> DataBag;

struct TreeNodeInterface
{
    virtual void set_data_from_bag(const DataBag& bag) = 0;
    virtual void set_name(const NodeName& name) = 0;
    virtual TreeNodeInterface* add_child() = 0;
};

struct TreeInterface
{
    virtual const TreeNodeInterface* get_root_interface() const = 0;
    virtual TreeNodeInterface* get_root_interface() = 0;
};

struct TreesCollectionInterface
{
    virtual TreeInterface* new_tree() = 0;
    virtual void set_data_from_bag(const DataBag& bag) = 0;
};

#define foreach_child(child) for(ChildrenIterator child(children.begin()); child.it != children.end(); ++child.it)

template <class TreeNode>
struct TreeData
{
    map<NodeName, TreeNode*> leaves;
    size_t depth;

    TreeData() : depth(0){}
};

template <class TreeNode>
class TreeNodeBase : public TreeNodeInterface
{
    TreeNode* This() { return static_cast<TreeNode*>(this); }
    const TreeNode* This() const { return static_cast<const TreeNode*>(this); }
    TreeData<TreeNode>& tree_data;
    const size_t depth;
protected:
    TreeNode* parent;
    typedef list<TreeNode*> Children;
    Children children;
    NodeName name;
    virtual void set_data(std::stringstream& ss) {}

    struct ChildrenIterator
    {
        typename Children::iterator it;
        ChildrenIterator(typename Children::iterator it)
            : it(it)
        {}

        TreeNode* operator ->() { return *it; }
        TreeNode& operator *()  { return **it; }
    };

    TreeNodeBase(TreeData<TreeNode>& td, size_t depth)
        : tree_data(td), depth(depth)
    {
        if (depth > tree_data.depth)
            tree_data.depth = depth;
    }
public:

    ~TreeNodeBase()
    {
        delete_container(children);
    }

    bool root() const { return parent == NULL; }

    TreeNode* get_parent() const
    {
        return parent;
    }

    size_t get_depth() const
    {
        return depth;
    }

    NodeName get_name() const
    {
        return name;
    }
private:
    virtual void set_data_from_bag(const DataBag& bag)
    {
        if (!name.empty())
        {
            const DataBag::const_iterator it = bag.find(name);
            if (it != bag.end())
            {
                std::stringstream ss_copy((it->second)->str());
                set_data(ss_copy);
            }
        }

        foreach_child(child)
            child->set_data_from_bag(bag);
    }

    virtual void set_name(const NodeName& n)
    {
        name = n;
        tree_data.leaves[name] = This();
    }

    virtual TreeNodeInterface* add_child()
    {
        TreeNode* child = new TreeNode(tree_data, depth + 1);
        static_cast<TreeNodeBase<TreeNode>*>(child)->parent = This();
        insert_into(children, child);
        return child;
    }
};

template <class TreeNode>
class Tree : public TreeInterface
{
    TreeNode root;
    TreeData<TreeNode> data;

    virtual const TreeNodeInterface* get_root_interface() const
    {
        return &root;
    }

    virtual TreeNodeInterface* get_root_interface()
    {
        return &root;
    }

public:
    struct LeavesIterator
    {
        typename map<NodeName, TreeNode*>::iterator it;
        LeavesIterator(typename map<NodeName, TreeNode*>::iterator it)
            : it(it)
        {}

        TreeNode* operator ->() { return it->second; }
        TreeNode& operator *()  { return *(it->second); }
    };

    Tree()
        : root(data, 0)
    {}

    TreeNode* get_root()
    {
        return &root;
    }

    size_t get_depth() const
    {
        return data.depth;
    }

    TreeNode* get_leaf(const NodeName& name)
    {
        return find(data.leaves, name, nothrow);
    }

    const TreeNode* get_leaf(const NodeName& name) const
    {
        return find(data.leaves, name, nothrow);
    }

    LeavesIterator begin()  {   return LeavesIterator(data.leaves.begin()); }
    LeavesIterator end()    {   return LeavesIterator(data.leaves.end()); }
};

template <class TreeNode>
class TreesCollection : public TreesCollectionInterface
{
    list<Tree<TreeNode>*> trees;

    virtual TreeInterface* new_tree()
    {
        Tree<TreeNode>* const new_tree = new Tree<TreeNode>;
        trees.push_back(new_tree);
        return new_tree;
    }

    virtual void set_data_from_bag(const DataBag& bag)
    {
        // for each tree:
        for(typename list<Tree<TreeNode>*>::iterator it = trees.begin(); it != trees.end(); ++it)
            static_cast<TreeInterface*>((*it))->get_root_interface()->set_data_from_bag(bag);
    }
public:
    struct TreesIterator
    {
        typename list<Tree<TreeNode>*>::iterator it;
        TreesIterator(typename list<Tree<TreeNode>*>::iterator it)
            : it(it)
        {}

        Tree<TreeNode>* operator ->() { return *it; }
        Tree<TreeNode>& operator *()  { return **it; }
    };

    ~TreesCollection()
    {
        delete_container(trees);
    }

    TreesIterator begin()   {   return TreesIterator(trees.begin());    }
    TreesIterator end()     {   return TreesIterator(trees.end());    }
};

#define foreach_tree(collection, tree, TreeNodeType) for(TreesCollection<TreeNodeType>::TreesIterator tree(collection.begin().it); tree.it != collection.end().it; ++tree.it)
#define foreach_leaf(tree, leaf, TreeNodeType) for(Tree<TreeNodeType>::LeavesIterator leaf(tree->begin().it); leaf.it != tree->end().it; ++leaf.it)

bool load_trees(const string& file, TreesCollectionInterface* collection);
bool load_data(const string& file, TreesCollectionInterface* collection);

#endif

