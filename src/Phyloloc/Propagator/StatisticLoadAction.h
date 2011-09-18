#ifndef STATISTIC_LOAD_ACTION_H
#define STATISTIC_LOAD_ACTION_H

#include "PropagatorAspect.h"
#include "Phylopp/Consensor/ConsensorAspect.h"


namespace Propagation
{

template <class Node>
class StatisticLoadAction
{
private:

    const TreeStatisticsCollector& statistics;

public:
    StatisticLoadAction(const TreeStatisticsCollector& stats)
        : statistics(stats) {}

    VisitAction visitNode(Node* n)
    {
        if(statistics.hasStatistics(n->cluster))
            n->loadStatistics(statistics.getClusterStatistics(n->cluster));

        return ContinueTraversing;
    }
};
}


#endif
