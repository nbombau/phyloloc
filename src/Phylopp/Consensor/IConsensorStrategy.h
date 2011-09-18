#ifndef ICONSENSOR_STRATEGY_H
#define ICONSENSOR_STRATEGY_H

#include "IConsensorObserver.h"
#include "ClusterTree.h"
#include "Domain/ITreeCollection.h"

namespace Consensus
{
template <class Node, class Observer>
class IConsensorStrategy
{
public:
    virtual Domain::ITree<Node>
    consensus(Domain::ITreeCollection<Node>& trees, Observer& observer) = 0;

};
}

#endif