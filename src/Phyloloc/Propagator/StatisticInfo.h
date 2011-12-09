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

#ifndef STATISTIC_INFO_H
#define STATISTIC_INFO_H

namespace Propagation
{
typedef float Statistic;

class StatisticInfo
{
public:
    Statistic average;
    Statistic stdDeviation;
    Statistic median;
    Statistic percentile25;
    Statistic percentile75;

    StatisticInfo() :
        average(0),
        stdDeviation(0),
        median(0),
        percentile25(0),
        percentile75(0)
    {}

    StatisticInfo(const StatisticInfo& info) :
        average(info.average),
        stdDeviation(info.stdDeviation),
        median(info.median),
        percentile25(info.percentile25),
        percentile75(info.percentile75)
    {}
};

typedef std::vector<StatisticInfo> StatisticInfoVector;
typedef std::vector<StatisticInfo>::iterator StatisticInfoIterator;
typedef std::vector<StatisticInfo>::const_iterator StatisticInfoConstIterator;
}

#endif
