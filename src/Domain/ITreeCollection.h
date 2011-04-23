#ifndef ITREE_COLLECTION_H
#define ITREE_COLLECTION_H

#include <list>

#include "ListIterator.h"
#include "INode.h"
#include "ITree.h"

namespace Domain
{
    using namespace std;

    /**
    * Class: ITreeCollection
    * ----------------------
    * Description: Class that defines a collection of phylogenetic trees
    * Type Parameter T: T is the underlying node class 
    */
    template <class T>
    class ITreeCollection
    {
        list<ITree<T>*> trees;

        /*
        * Method: addTree
        * ---------------
        * Description: Adds a tree to the collection.
        * @return the recently added tree
        */
        virtual ITree<T>* addTree()
        {
            ITree<T>* const tree = new ITree<T>;
            trees.push_back(tree);
            return tree;
        }

    public:

        /*
        * Method: getIterator
        * -------------------
        * Description: Provides the user a way to iterate through the 
        * trees of the collection.
        * @return trees iterator 
        */
        ListIterator<ITree<T>> getIterator()
        {
            return new ListIterator<ITree<T>>(trees);
        }

    protected:

        //Destructor
        ~ITreeCollection()
        {
            delete_container(trees);
        }
    };
}

#endif
