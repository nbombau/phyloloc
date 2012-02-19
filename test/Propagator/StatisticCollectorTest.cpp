
#include <stddef.h>
#include <gtest/gtest.h>
#include "../../src/Phyloloc/Propagator/StatisticCollector.h"
#include "../../src/Phylopp/Consensor/bitset.h"


namespace
{

using namespace Propagation;
using namespace Consensus;
using ::testing::Test;

class StatisticCollectorTest : public Test
{
protected:

    StatisticCollectorTest() { }

    virtual ~StatisticCollectorTest() { }


    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {
    }
};




TEST_F(StatisticCollectorTest, NodeStatisticTest)
{
    const Statistic epsilon = 0.001;
    NodeStatisticsCollector col(4);
    std::vector<Statistic> v1(4);
    v1[0] = 0.5;
    v1[1] = 0.25;
    v1[2] = 0.1;
    v1[3] = 0.15;

    std::vector<Statistic> v2(4);
    v2[0] = 0.2;
    v2[1] = 0.25;
    v2[2] = 0.5;
    v2[3] = 0.05;
    std::vector<Statistic> v3(4);
    v3[0] = 0.8;
    v3[1] = 0.1;
    v3[2] = 0.05;
    v3[3] = 0.05;
    col.addStatistic(v1.begin());

    col.addStatistic(v2.begin());

    col.addStatistic(v3.begin());

    StatisticInfoVector ret = col.calculateStatistics();

    EXPECT_EQ(ret.size(), 4);
    //first location statistic info
    /* distribution[0] 0.5 0.2 0.8
     * Avg 0.5
     * Median 0.5
     * std deviation 0.24494
     * */
    StatisticInfo i = ret[0];

    ASSERT_NEAR(i.average, 0.5, epsilon);
    ASSERT_NEAR(i.median, 0.5, epsilon);
    ASSERT_NEAR(i.stdDeviation, 0.24494, epsilon);
    /* distribution[1] 0.25 0.25 0.1
     * Avg 0.2
     * Median 0.25
     * std deviation 0.095742713
     * */
    i = ret[1];

    ASSERT_NEAR(i.average, 0.2, epsilon);
    ASSERT_NEAR(i.median, 0.25, epsilon);
    ASSERT_NEAR(i.stdDeviation, 0.070710678, epsilon);

    /* distribution[0] 0.1 0.5 0.05
     * Avg 0.216666667
     * Median 0.1
     * std deviation 0.201384101
     * */
    i = ret[2];

    ASSERT_NEAR(i.average, 0.216666667, epsilon);
    ASSERT_NEAR(i.median, 0.1, epsilon);
    ASSERT_NEAR(i.stdDeviation, 0.201384101, epsilon);

}

TEST_F(StatisticCollectorTest, TreeStatisticTest)
{
    const Statistic epsilon = 0.001;

    std::vector<Statistic> v1(4);
    v1[0] = 0.5;
    v1[1] = 0.25;
    v1[2] = 0.1;
    v1[3] = 0.15;
    std::vector<Statistic> v2(4);
    v2[0] = 0.2;
    v2[1] = 0.25;
    v2[2] = 0.5;
    v2[3] = 0.05;
    std::vector<Statistic> v3(4);
    v3[0] = 0.8;
    v3[1] = 0.1;
    v3[2] = 0.05;
    v3[3] = 0.05;

    std::vector<Statistic> t1(4);
    t1[0] = 0.25;
    t1[1] = 0.5;
    t1[2] = 0.01;
    t1[3] = 0.1;
    std::vector<Statistic> t2(4);
    t2[0] = 0.22;
    t2[1] = 0.2;
    t2[2] = 0.23;
    t2[3] = 0.35;
    std::vector<Statistic> t3(4);
    t3[0] = 0.8;
    t3[1] = 0.01;
    t3[2] = 0.09;
    t3[3] = 0.05;

    TreeStatisticsCollector col(4);

    bitset v(4);
    v.set(1);

    bitset t(4);
    t.set(2);

    col.addStatistic(v, v1.begin());
    col.addStatistic(v, v2.begin());
    col.addStatistic(v, v3.begin());

    col.addStatistic(t, t1.begin());
    col.addStatistic(t, t2.begin());
    col.addStatistic(t, t3.begin());
    StatisticInfoVector ret = col.getClusterStatistics(v);

    EXPECT_EQ(ret.size(), 4);
    //first location statistic info
    /* distribution[0] 0.5 0.2 0.8
     * Avg 0.5
     * Median 0.5
     * std deviation 0.24494
     * */
    StatisticInfo i = ret[0];

    ASSERT_NEAR(i.average, 0.5, epsilon);
    ASSERT_NEAR(i.median, 0.5, epsilon);
    ASSERT_NEAR(i.stdDeviation, 0.24494, epsilon);

    /* distribution[1] 0.25 0.25 0.1
     * Avg 0.2
     * Median 0.25
     * std deviation 0.095742713
     * */
    i = ret[1];

    ASSERT_NEAR(i.average, 0.2, epsilon);
    ASSERT_NEAR(i.median, 0.25, epsilon);
    ASSERT_NEAR(i.stdDeviation, 0.070710678, epsilon);

    /* distribution[0] 0.1 0.5 0.05
     * Avg 0.216666667
     * Median 0.1
     * std deviation 0.201384101
     * */
    i = ret[2];


    ASSERT_NEAR(i.average, 0.216666667, epsilon);
    ASSERT_NEAR(i.median, 0.1, epsilon);
    ASSERT_NEAR(i.stdDeviation, 0.201384101, epsilon);

}
}
