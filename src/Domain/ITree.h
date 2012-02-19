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

#ifndef ITREE_H
#define ITREE_H

#include <stdlib.h>
#include <string>
#include <map>
#include <set>

#include "INode.h"

namespace Domain
{

typedef unsigned int TreeId;

/**
* Class: ITree
* ----------------------
* Description: Class that defines a phylogenetic tree
* Type Parameter T: T is the underlying node class
*/
template <class T>
class ITree
{
public:

    ITree(TreeId treeId) : root(), id(treeId)
    {}

    ITree() : root(), id(1)
    {}

    /*
    * Method: getRoot
    * ---------------
    * Description: Returns the root node of the tree
    * @return tree's root
    */
    T* getRoot()
    {
        return &root;
    }

    /*
    * Method: getRoot
    * ---------------
    * Description: Returns the root node of the tree
    * @return tree's root
    */
    const T* getRoot() const
    {
        return &root;
    }

    /*
    * Method: getId
    * -------------
    * Description: gets the id of the tree
    * @return tree's id
    */
    TreeId getId() const
    {
        return id;
    }

private:
    T root;
    const TreeId id;
};
}

#endif
