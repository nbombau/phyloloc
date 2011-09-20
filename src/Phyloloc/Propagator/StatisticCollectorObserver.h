#ifndef STATISTIC_COLLECTOR_OBSERVER_H
#define STATISTIC_COLLECTOR_OBSERVER_H

#include "PropagatorAspect.h"
//#include "TraversalPredicates.h"
#include "StatisticCollector.h"
#include "StatisticLoadAction.h"
#include "Phylopp/Consensor/bitset.h"
#include "Phylopp/Consensor/ConsensorAspect.h"
#include "Phylopp/Consensor/IConsensorObserver.h"
#include "Phylopp/Traversal/Traverser.h"

namespace Propagation
{
/**
 * Interface: IConsensorObserver
 * ----------------------
 * Description: Interface for observers that shall be used during the
 * consensor algorithm. The consensors observers shall notify when a node
 * is included or excluded from de resulting consensed tree.
 * Type Parameter T: T is the underlying node class
 */
template <class Node2>
class StatisticCollectorObserver : public Consensus::IConsensorObserver<Node2>
{
private:

    TreeStatisticsCollector collector;

public:

    StatisticCollectorObserver(unsigned int locationsCount) : collector(locationsCount)
    { }

    void onStart(const Domain::ITreeCollection<Node2>& /*trees*/)
    {

    }
    /**
     * Method: notifyInclude
     * ---------------
     * Description: Notifies when a node is included in the consensed tree.
     * @param node node that has been included in the consensed tree
     */
    void onInclude(Node2 * node, const Consensus::bitset& cluster)
    {
       /* printf("\n");
        for(unsigned int i = 0; i < cluster.size(); i++)
            printf("%s", cluster[i] == Consensus::bitset::bit::true_bit ? "1" :"0" );*/
        
        collector.addStatistic(cluster, node->getProbabilitiesIterator());
    }

    /**
     * Method: notifyExclude
     * ---------------
     * Description: Notifies when a node is excluded in the consensed tree.
     * @param node node that has been excluded in the consensed tree
     */
    void onExclude(Node2 * /*node*/, const Consensus::bitset& /*cluster*/)
    {

    }

    void onEnd(Domain::ITree<Node2>* consensed)
    {
        StatisticLoadAction<Node2> action(collector);
        Traversal::Traverser<Node2, StatisticLoadAction<Node2>, AlwaysTruePredicate<Node2> > traverser;
        traverser.traverseDescendants(consensed, action);
    }
};
}


#endif
