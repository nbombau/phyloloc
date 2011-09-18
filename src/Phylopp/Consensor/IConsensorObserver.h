#ifndef ICONSENSOR_OBSERVER_H
#define ICONSENSOR_OBSERVER_H

#include "bitset.h"
#include "Domain/ITreeCollection.h"

namespace Consensus
{
/**
 * Interface: IConsensorObserver
 * ----------------------
 * Description: Interface for observers that shall be used during the
 * consensor algorithm. The consensors observers shall notify when a node
 * is included or excluded from de resulting consensed tree.
 * Type Parameter T: T is the underlying node class
 */
template <class Node>
class IConsensorObserver
{

public:


    virtual void onStart(const Domain::ITreeCollection<Node>& trees) = 0;

    /**
     * Method: notifyInclude
     * ---------------
     * Description: Notifies when a node is included in the consensed tree.
     * @param node node that has been included in the consensed tree
     */
    virtual void onInclude(Node* node, const bitset& cluster) = 0;

    /**
     * Method: notifyExclude
     * ---------------
     * Description: Notifies when a node is excluded in the consensed tree.
     * @param node node that has been excluded in the consensed tree
     */
    virtual void onExclude(Node* node, const bitset& cluster) = 0;

    virtual void onEnd(Domain::ITree<Node>* consensed) = 0;

};
}


#endif
