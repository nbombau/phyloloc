#ifndef STATISTIC_INFO_H
#define STATISTIC_INFO_H

namespace Propagation
{
typedef float Statistic;

struct StatisticInfo
{
    Statistic average;
    Statistic stdDeviation;
    Statistic median;
    Statistic percentile25;
    Statistic percentile75;
};

typedef std::vector<StatisticInfo> StatisticInfoVector;
typedef std::vector<StatisticInfo>::iterator StatisticInfoIterator;
typedef std::vector<StatisticInfo>::const_iterator StatisticInfoConstIterator;
}

#endif