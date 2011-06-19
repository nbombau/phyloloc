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

    /*
    * Method: addTree
    * ---------------
    * Description: Adds a tree to the collection.
    * @return the recently added tree
    */
    virtual ITree<T>* addTree()
    {
        ITree<T>* const tree = new ITree<T>();
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
    ListIterator<ITree<T> > getIterator() const
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
        ListIterator<ITree<T> > it = this->getIterator();

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
         delete_container(trees);
    }

    //Destructor
    ~ITreeCollection()
    {
        //Call to MiLi's delete_container
        delete_container(trees);
    }

private:

    std::list<ITree<T>*> trees;
};
}

#endif
