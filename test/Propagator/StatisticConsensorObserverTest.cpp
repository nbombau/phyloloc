
#include <stddef.h>
#include <gtest/gtest.h>

#include "../../src/Phylopp/Consensor/ClusterTree.h"
#include "../../src/Domain/INode.h"
#include "../../src/Domain/ITree.h"
#include "../../src/Domain/ITreeCollection.h"
#include "../../src/Domain/LocationAspect.h"
#include "../../src/Phyloloc/Propagator/Propagator.h"
#include "../../src/Phyloloc/Propagator/PropagatorAspect.h"
#include "../../src/Phylopp/Consensor/ConsensorAspect.h"
#include "../../src/Phylopp/Consensor/StrictConsensor.h"
#include "../../src/Phyloloc/Propagator/StatisticsAspect.h"
#include "../../src/Phyloloc/Propagator/StatisticCollectorObserver.h"


namespace {

using namespace Consensus;
using namespace Domain;
using namespace Locations;
using namespace Propagation;
using ::testing::Test;

class StatisticCollectorObserverTest : public Test
{
protected:

    StatisticCollectorObserverTest() { }

    virtual ~StatisticCollectorObserverTest() { }


    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {
    }
};

typedef Propagation::StatisticAspect<Consensus::ConsensorAspect<Propagation::PropagatorAspect<Locations::LocationAspect<Domain::Node> > > > PropNode;


TEST_F(StatisticCollectorObserverTest, StatisticConsensusTest)
{
    ITreeCollection<PropNode> trees;

    PropNode::clear();
    /*tree 1*/
    Domain::ITree<PropNode>* t1 = trees.addTree();
    PropNode* root = t1->getRoot();

    PropNode* c1 = root->addChild<PropNode>();
    PropNode* c11 = c1->addChild<PropNode>();
    PropNode* c12 = c1->addChild<PropNode>();
    PropNode* c111 = c11->addChild<PropNode>();
    PropNode* c112 = c11->addChild<PropNode>();
    PropNode* c4 = root->addChild<PropNode>();

    c12->setName("C");
    c111->setName("A");
    c112->setName("B");
    c4->setName("D");

    root->setBranchLength(0);
    /*c1->setBranchLength(1);
     *        c2->setBranchLength(2);
     *        c3->setBranchLength(3);
     *        c4->setBranchLength(4);
     *        c5->setBranchLength(4);*/

    PropNode::addLocation("A", "A");
    PropNode::addLocation("B", "B");
    PropNode::addLocation("C", "C");
    PropNode::addLocation("D", "D");

    PropNode::addDistance(0, "A", "A");
    PropNode::addDistance(0, "B", "B");
    PropNode::addDistance(0, "C", "C");
    PropNode::addDistance(0, "D", "D");
    PropNode::addDistance(0, "A", "D");
    PropNode::addDistance(0, "B", "D");
    PropNode::addDistance(0, "C", "D");
    PropNode::addDistance(0, "D", "C");
    PropNode::addDistance(0, "D", "B");
    PropNode::addDistance(0, "D", "A");

    PropNode::addDistance(2, "A", "B");
    PropNode::addDistance(2, "A", "C");
    PropNode::addDistance(3, "B", "A");
    PropNode::addDistance(3, "B", "C");
    PropNode::addDistance(2, "C", "A");
    PropNode::addDistance(4, "C", "B");
    ClusterTree<PropNode> cluster1(*t1);

    /*tree 2*/

    Domain::ITree<PropNode>* t2 = trees.addTree();
    PropNode* root2 = t2->getRoot();

    PropNode* d1 = root2->addChild<PropNode>();
    PropNode* d11 = d1->addChild<PropNode>();
    PropNode* d12 = d1->addChild<PropNode>();
    PropNode* d111 = d11->addChild<PropNode>();
    PropNode* d112 = d11->addChild<PropNode>();
    PropNode* d4 = root2->addChild<PropNode>();

    d12->setName("A");
    d111->setName("C");
    d112->setName("B");
    d4->setName("D");

    root2->setBranchLength(0);

    Propagator<PropNode>::propagate(t1, 2, 0.25, 0.25);
    Propagator<PropNode>::propagate(t2, 2, 0.25, 0.25);

    StatisticCollectorObserver<PropNode> obs(4);

    /* StrictConsensor<PropNode, StatisticCollectorObserver<PropNode> > consensor;
     *        consensor.consensus(trees, obs);*/

    //PropNode::clear();
}
}
