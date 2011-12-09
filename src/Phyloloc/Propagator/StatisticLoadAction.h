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
    StatisticLoadAction(const TreeStatisticsCollector& stats) :
        statistics(stats)
    {}

    VisitAction visitNode(Node* n)
    {
        if (statistics.hasStatistics(n->cluster))
        {
            n->loadStatistics(statistics.getClusterStatistics(n->cluster));
        }

        return ContinueTraversing;
    }
};
}


#endif
