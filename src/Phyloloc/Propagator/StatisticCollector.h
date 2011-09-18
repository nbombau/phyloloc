#ifndef STATISTIC_COLLECTOR_H
#define STATISTIC_COLLECTOR_H

#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stdio.h>
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
    StatisticVector statisticSums;
    StatisticVector statisticSquareSums;
    unsigned int statisticsCount;
    unsigned int locationsCount;

    Statistic calculateAverage(unsigned int i)
    {
        return statisticSums[i] / statisticsCount;
    }

    Statistic calculateStdDeviation(unsigned int i)
    {
        Statistic numerator = sqrt(
                                  statisticsCount * statisticSquareSums[i] - pow(statisticSums[i], 2)
                              );

        return  numerator / statisticsCount;
    }

    Statistic calculatePercentile(unsigned int i, unsigned int percentile)
    {
        //TODO: Weighted percentile
        unsigned int idx = int((percentile / 100.0) * statisticsCount + 0.5) - 1;
        return statistics[i][idx];
    }

    Statistic round(Statistic r) {
        return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
    }


public:

    NodeStatisticsCollector(unsigned int locCount)
        : statisticsCount(0),
          locationsCount(locCount)

    {
        statisticSums.resize(locationsCount);
        statisticSquareSums.resize(locationsCount);
        statistics.resize(locationsCount);
    }

    void addStatistic(StatisticConstIterator it)
    {
        //TODO: check iterator size, assert its statistics size
        for(unsigned int i = 0; i < locationsCount; i++)
        {
            statistics[i].push_back(*it);

            statisticSums[i] += *it;
            statisticSquareSums[i] += pow(*it, 2);
            it++;
        }
        statisticsCount++;
    }

    StatisticInfoVector calculateStatistics()
    {
        StatisticInfoVector ret;

        for(unsigned int i = 0; i < locationsCount; i++)
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
        if(treeStatistics.count(b) == 0)
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
