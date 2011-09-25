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
        StatisticVector statisticSums;
        StatisticVector statisticSquareSums;
        unsigned int statisticsCount;
        unsigned int locationsCount;

        Statistic calculateAverage(unsigned int i) const
        {
            Statistic ret = 0;
            if(statisticsCount > 0)
                ret = statisticSums[i] / statisticsCount;
            return ret;
        }

        Statistic calculateStdDeviation(unsigned int i) const
        {
            Statistic ret = 0;
            
            if(statisticsCount > 0)
            {
                Statistic numerator = sqrt(
                    statisticsCount * statisticSquareSums[i] - statisticSums[i] * statisticSums[i]
                );
                ret = numerator / statisticsCount;
            }

            return ret;
        }

        Statistic calculatePercentile(unsigned int i, unsigned int percentile) const
        {
            //TODO: Weighted percentile
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

        NodeStatisticsCollector(unsigned int locCount)
            : statisticsCount(0),
            locationsCount(locCount)

        {
            statisticSums.resize(locationsCount);
            statisticSquareSums.resize(locationsCount);
            statistics.resize(locationsCount);
        }
        
        NodeStatisticsCollector(const NodeStatisticsCollector& other)
        : statisticsCount(other.statisticsCount),
        locationsCount(other.locationsCount)
        {
            statisticSums = StatisticVector(other.statisticSums);
            statisticSquareSums = StatisticVector(other.statisticSquareSums);
            statistics = NodeStatistics(other.statistics);
        }

        void addStatistic(StatisticConstIterator it)
        {
            //TODO: check iterator size, assert its statistics size
            for(unsigned int i = 0; i < locationsCount; i++)
            {
                statistics[i].push_back(*it);
                statisticSums[i] += *it;
                statisticSquareSums[i] += square(*it);
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
