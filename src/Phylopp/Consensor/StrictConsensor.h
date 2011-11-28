#ifndef STRICT_CONSENSOR_H
#define STRICT_CONSENSOR_H

#include <mili/mili.h>
#include "ClusterTree.h"

class StrictConsensorExceptionHierarchy {};
typedef GenericException<StrictConsensorExceptionHierarchy> StrictConsensorException;


/**
* StrictConsensorException
* ------------------------
* Description: Exception thrown when no trees exist for consensus
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(EmptyTreeCollectionException,
                               StrictConsensorExceptionHierarchy,
                               "No trees were supplied");
                               

namespace Consensus
{
    template <class Node2, class Observer>
    class StrictConsensor
    {
    public:

        Domain::ITree<Node2> *consensus(Domain::ITreeCollection<Node2>& trees,
                                        Observer& observer,
                                        Locations::LocationManager& locManager)
        {
            unsigned int i=0;
            observer.onStart(trees);
            Domain::ListIterator<Domain::ITree<Node2> > it = trees.getIterator();

            if(it.count() == 0)
                throw EmptyTreeCollectionException();

            ClusterTree<Node2,Observer> first(trees.elementAt(i),observer, locManager);

            ClusterTree<Node2,Observer> consensusCluster(first,observer, locManager);

            if(it.count() > 1)
            {
                it.next();
                i++;
                for(; i<it.count() && !it.end(); ++i,it.next())
                {
                    ClusterTree<Node2,Observer> current(trees.elementAt(i),observer, locManager);
                    consensusCluster.intersectWith(current);
                }
            }

            Domain::ITree<Node2> * consensedTree = consensusCluster.toTree();
            observer.onEnd(consensedTree);

            return consensedTree;
        }
    };

}


#endif
