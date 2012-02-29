/*
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

#ifndef INODE_H
#define INODE_H

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <mili/mili.h>

#include "ListIterator.h"



namespace Domain
{

typedef float BranchLength;
typedef std::string NodeName;
/**
* Class: Node
* -----------
* Description: Base phylogenetic node implementation
*/
class Node
{
public:
    Node() :
        parent(NULL),
        branchLength(0)
    {}

    virtual ~Node()
    {
        //Call to MiLi's delete_container
        mili::delete_container(children);
    }


    /**
    * Method: isRoot
    * ---------------
    * Description: Informs whether the node is the root of a tree.
    * @return true if the node is root, false otherwise
    */
    bool isRoot() const
    {
        return parent == NULL;
    }


    /**
    * Method: isLeaf
    * ---------------
    * Description: Informs whether the node is a Leaf
    * @return true if the node is leaf
    */
    bool isLeaf() const
    {
        return children.empty();
    }


    /**
    * Method: getParent
    * -----------------
    * Description: Allows the client to get the parent of the node.
    * @return if the node is not root, the parent of the node; and
    * null otherwise
    */
    template <class T>
    T* getParent() const
    {
        return static_cast<T*>(parent);
    }


    /**
    * Method: getChildrenIterator
    * ---------------------------
    * Description: Returns a ListIterator object that allows the
    * client to iterate through the node's children.
    * @returns ListIterator to iterate through the node's children
    */
    template <class T>
    ListIterator<T, Node> getChildrenIterator() const
    {
        ListIterator<T, Node> iter(children);
        return iter;
    }

    /**
    * Method: addChild
    * ----------------
    * Description: Adds a child to the node, and returns it being
    * already topologically binded to the tree.
    * @return Node already binded to the current node.
    */
    template <class T>
    T* addChild()
    {
        T* child = new T();
        child->parent = this;
        children.push_back(child);
        return child;
    }

    /**
    * Method: getName
    * ---------------
    * Description: Gets the name associated to the node
    * @return the node's name
    */
    NodeName getName() const
    {
        return name;
    }

    /**
    * Method: setName
    * ---------------
    * Description: Sets the name associated to the node
    */
    void setName(const NodeName& n)
    {
        name = n;
    }

    /**
    * Method: getBranchLength
    * ---------------
    * Description: Gets the branch length associated to the node
    * @return the node's branch length
    */
    BranchLength getBranchLength() const
    {
        return branchLength;
    }

    /**
    * Method: setBranchLength
    * ---------------
    * Description: Sets the name associated to the node
    */
    void setBranchLength(const BranchLength n)
    {
        branchLength = n;
    }
protected:

    Node* parent;
    std::list<Node*> children;

    NodeName name;
    BranchLength branchLength;


};
}

#endif
