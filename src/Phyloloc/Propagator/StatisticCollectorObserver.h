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

#ifndef STATISTIC_COLLECTOR_OBSERVER_H
#define STATISTIC_COLLECTOR_OBSERVER_H

#include "PropagatorAspect.h"
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

    StatisticCollectorObserver(unsigned int locationsCount) :
        collector(locationsCount)
    {}

    void onStart(const Domain::ITreeCollection<Node2>& /*trees*/)
    {}

    /**
     * Method: notifyInclude
     * ---------------
     * Description: Notifies when a node is included in the consensed tree.
     * @param node node that has been included in the consensed tree
     */
    void onInclude(const Node2* const node, const Consensus::bitset& cluster)
    {
        collector.addStatistic(cluster, node->probabilitiesBegin());
    }

    /**
     * Method: notifyExclude
     * ---------------
     * Description: Notifies when a node is excluded in the consensed tree.
     * @param node node that has been excluded in the consensed tree
     */
    void onExclude(const Node2* const /*node*/, const Consensus::bitset& /*cluster*/)
    {}

    void onEnd(Domain::ITree<Node2>* consensed)
    {
        StatisticLoadAction<Node2> action(collector);
        Traversal::Traverser<Node2, StatisticLoadAction<Node2>, AlwaysTruePredicate<Node2> > traverser;
        traverser.traverseDescendants(consensed, action);
    }
};
}

#endif
