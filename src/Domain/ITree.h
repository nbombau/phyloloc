#ifndef ITREE_H
#define ITREE_H

#include <stdlib.h>
#include <string>
#include <map>
#include <set>

#include "INode.h"

namespace Domain
{
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

    //Constructor
    ITree() : root() { }

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

    //TODO: Map de (name, T) que tenga las hojas para buscarlas e iterarlas

private:

    T root;
};
}

#endif
