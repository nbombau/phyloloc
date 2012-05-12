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

#ifndef STATISTICS_ASPECT_H
#define STATISTICS_ASPECT_H

#include <vector>
#include "phyloloc/Propagator/StatisticInfo.h"

namespace Propagation
{
typedef std::vector<StatisticInfo> StatisticsVector;

template <class T>
class StatisticAspect : public T
{
private:
    StatisticInfoVector statistics;

public:

    void loadStatistics(StatisticInfoVector s)
    {
        statistics = s;
    }

    const StatisticInfoVector& getStatistics() const
    {
        return statistics;
    }
};
}

#endif
