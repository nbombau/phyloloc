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

#ifndef STATISTIC_COLLECTOR_H
#define STATISTIC_COLLECTOR_H

#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <mili/mili.h>
#include "StatisticInfo.h"
#include "Phylopp/Consensor/bitset.h"

namespace Propagation
{

typedef std::vector<Statistic> StatisticVector;
typedef std::vector<Statistic>::iterator StatisticIterator;
typedef std::vector<Statistic>::const_iterator StatisticConstIterator;
typedef std::vector<StatisticVector> NodeStatistics;
typedef std::vector<StatisticVector>::iterator NodeStatisticsIterator;

class NodeStatisticsCollector
{
private:
    NodeStatistics statistics;
    StatisticVector averages;
    StatisticVector variances;
    unsigned int statisticsCount;
    unsigned int locationsCount;

    Statistic calculateAverage(unsigned int i) const
    {
        Statistic ret = 0;
        if (statisticsCount > 0)
            ret = averages[i];
        return ret;
    }

    Statistic calculateStdDeviation(unsigned int i) const
    {
        Statistic ret = 0;

        if (statisticsCount > 0)
        {
            ret = sqrt(variances[i] / statisticsCount);
        }

        return ret;
    }

    Statistic calculatePercentile(unsigned int i, unsigned int percentile) const
    {
        //TODO: O(nlog(n)) solution. Consider implementing a O(n) solution,
        // as presented in Introduction To Algorithms, Cormen, chapter 7,
        //Order Statistics
        unsigned int idx = static_cast<unsigned int>(
                               (percentile / 100.0) * statisticsCount - 0.5
                           );
        return statistics[i][idx];
    }

    static Statistic round(Statistic r)
    {
        return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
    }


public:

    NodeStatisticsCollector(unsigned int locCount) :
        statisticsCount(0),
        locationsCount(locCount)

    {
        averages.resize(locationsCount);
        variances.resize(locationsCount);
        statistics.resize(locationsCount);
    }

    void addStatistic(StatisticConstIterator it)
    {
        //TODO: check iterator size, assert its statistics size
        for (unsigned int i = 0; i < locationsCount; i++)
        {
            //save the statistics for the percentile's calculation
            statistics[i].push_back(*it);

            //Variance, Standard Deviation and average calculated using Welford's
            //Algorithm, presented in Knuth, Art of Computer Programming volume 2,
            //statistics calculation chapter
            if (statisticsCount == 0)
            {
                averages[i] = *it;
                variances[i] = 0.0;
            }
            else
            {
                Statistic prevAverage = averages[i];
                //update the average
                averages[i] += (*it - averages[i]) / (statisticsCount + 1);

                //update the standardDeviations
                variances[i] += (*it - prevAverage) * (*it - averages[i]);
            }
            it++;
        }
        statisticsCount++;
    }

    StatisticInfoVector calculateStatistics()
    {
        StatisticInfoVector ret;

        for (unsigned int i = 0; i < locationsCount; i++)
        {
            StatisticInfo info;

            sort(statistics[i].begin(), statistics[i].end());

            info.average = calculateAverage(i);
            info.stdDeviation = calculateStdDeviation(i);
            info.median = calculatePercentile(i, 50);
            info.percentile25 = calculatePercentile(i, 25);
            info.percentile75 = calculatePercentile(i, 75);

            ret.push_back(info);
        }

        return ret;
    }
};

class TreeStatisticsCollector
{
private:

    std::map<Consensus::bitset, NodeStatisticsCollector> treeStatistics;
    unsigned int locationsCount;

public:

    TreeStatisticsCollector(unsigned int count) : locationsCount(count) {}

    void addStatistic(const Consensus::bitset& b, StatisticConstIterator it)
    {
        if (treeStatistics.count(b) == 0)
        {
            NodeStatisticsCollector statCol(locationsCount);
            statCol.addStatistic(it);
            treeStatistics.insert(
                std::pair<Consensus::bitset, NodeStatisticsCollector>(b, statCol)
            );
        }
        else
        {
            NodeStatisticsCollector& c = treeStatistics.find(b)->second;
            c.addStatistic(it);
        }
    }

    StatisticInfoVector getClusterStatistics(const Consensus::bitset& b) const
    {
        NodeStatisticsCollector c = treeStatistics.find(b)->second;
        return c.calculateStatistics();
    }

    bool hasStatistics(const Consensus::bitset& b) const
    {
        return treeStatistics.count(b) > 0;
    }
};

}

#endif
