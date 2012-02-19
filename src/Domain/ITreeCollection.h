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

#ifndef ITREE_COLLECTION_H
#define ITREE_COLLECTION_H

#include <list>
#include <mili/mili.h>
#include "ListIterator.h"
#include "ITree.h"

namespace Domain
{

/**
* Class: ITreeCollection
* ----------------------
* Description: Class that defines a collection of phylogenetic trees
* Type Parameter T: T is the underlying node class
*/
template <class T>
class ITreeCollection
{

public:

    typedef ListIterator<ITree<T> > iterator;

    ITreeCollection() : nextTreeId(1) { }

    /*
    * Method: addTree
    * ---------------
    * Description: Adds a tree to the collection.
    * @return the recently added tree
    */
    virtual ITree<T>* addTree()
    {
        const TreeId nextId = getNextTreeId();
        ITree<T>* const tree = new ITree<T>(nextId);
        trees.push_back(tree);
        return tree;
    }

    /*
    * Method: getIterator
    * -------------------
    * Description: Provides the user a way to iterate through the
    * trees of the collection.
    * @return trees iterator
    */
    iterator getIterator() const
    {
        ListIterator<ITree<T> > iter = ListIterator<ITree<T> >(trees);
        return iter;
    }

    /*
    * Method: elementAt
    * -------------------
    * Description: Returns the element at certain index
    * @return element at certain index, null otherwise
    */
    ITree<T>* elementAt(unsigned int index) const
    {
        unsigned int i = 0;
        ITree<T>* ret = NULL;
        iterator it = this->getIterator();

        while (i < index && !it.end())
        {
            it.next();
            i++;
        }

        if (i == index)
        {
            ret = it.get();
        }

        return ret;
    }

    /*
    * Method: clear
    * -------------------
    * Description: Clears the tree collection
    */
    void clear()
    {
        nextTreeId = 1;
        mili::delete_container(trees);
    }

    //Destructor
    ~ITreeCollection()
    {
        //Call to MiLi's delete_container
        mili::delete_container(trees);
    }

private:

    TreeId getNextTreeId()
    {
        return nextTreeId++;
    }

    std::list<ITree<T>*> trees;
    TreeId nextTreeId;
};
}

#endif
