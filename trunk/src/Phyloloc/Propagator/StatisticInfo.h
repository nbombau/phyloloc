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
    
    StatisticInfo() 
    : average(0),
    stdDeviation(0),
    median(0),
    percentile25(0),
    percentile75(0)
    {
        
    }
    
    StatisticInfo(const StatisticInfo& info) 
        : average(info.average),
        stdDeviation(info.stdDeviation),
        median(info.median),
        percentile25(info.percentile25),
        percentile75(info.percentile75)
    {
        
    }
};

typedef std::vector<StatisticInfo> StatisticInfoVector;
typedef std::vector<StatisticInfo>::iterator StatisticInfoIterator;
typedef std::vector<StatisticInfo>::const_iterator StatisticInfoConstIterator;
}

#endif