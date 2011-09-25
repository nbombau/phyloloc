#ifndef STATISTICS_ASPECT_H
#define STATISTICS_ASPECT_H

#include <vector>

#include "StatisticInfo.h"

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
