#ifndef STRICT_CONSENSOR_H
#define STRICT_CONSENSOR_H

#include "Phylopp/Consensor/IConsensorObserver.h"
#include "Phylopp/Consensor/StrictConsensor.h"

namespace Consensus
{
template <class Node>
class StatisticStrictConsensor : StrictConsensor<Node>
{
public:

    virtual ITree<Node> consensus(ITreeCollection<Node> trees, IConsensorObserver<Node> observer)
    {
        ITree<Node> t = consensus(trees, observer);

        //iterate through t assigning statistics
    }
};

}