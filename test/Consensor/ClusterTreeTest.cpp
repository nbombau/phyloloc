
#include <stddef.h>
#include <gtest/gtest.h>

#include "../../src/Phylopp/Consensor/ClusterTree.h"
#include "../../src/Phylopp/Consensor/ConsensorAspect.h"
#include "../../src/Domain/ITree.h"
#include "../../src/Domain/LocationAspect.h"
#include "../../src/Phylopp/Consensor/IConsensorObserver.h"
#include "DummyObserver.h"


namespace
{

using namespace Consensus;
using namespace Domain;
using namespace Locations;
using ::testing::Test;

class ClusterTreeTest : public Test
{
protected:

    ClusterTreeTest() { }

    virtual ~ClusterTreeTest() { }


    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {
    }
};




typedef ConsensorAspect<LocationAspect<Node> > PropNode;

// Check the getters work properly
TEST_F(ClusterTreeTest, ClusterTreeCreationTest)
{
    Locations::LocationManager locMgr;
    Domain::ITree<PropNode> t;
    DummyObserver<PropNode> observer;
    PropNode* root = t.getRoot();

    PropNode* c1 = root->addChild<PropNode>();
    PropNode* c2 = root->addChild<PropNode>();
    PropNode* c3 = root->addChild<PropNode>();
    PropNode* c4 = root->addChild<PropNode>();

    c1->setName("A");
    c2->setName("A");
    c3->setName("B");
    c4->setName("C");

    root->setBranchLength(0);
    c1->setBranchLength(1);
    c2->setBranchLength(2);
    c3->setBranchLength(3);
    c4->setBranchLength(4);

    locMgr.addLocation("A", "A");
    locMgr.addLocation("B", "B");
    locMgr.addLocation("C", "C");

    locMgr.addDistance(0, "A", "A");
    locMgr.addDistance(0, "B", "B");
    locMgr.addDistance(0, "C", "C");

    locMgr.addDistance(2, "A", "B");
    locMgr.addDistance(2, "A", "C");
    locMgr.addDistance(3, "B", "A");
    locMgr.addDistance(3, "B", "C");
    locMgr.addDistance(2, "C", "A");
    locMgr.addDistance(4, "C", "B");

    ClusterTree<PropNode, DummyObserver<PropNode> > cluster(&t, observer, locMgr);

    Consensus::bitset b1(3);
    b1.set(0);

    Consensus::bitset b2(3);
    b2.set(1);

    Consensus::bitset b3(3);
    b3.set(2);

    Consensus::bitset b11(3);
    b11.set(0);
    b11.set(1);

    Consensus::bitset b12(3);
    b12.set(1);
    b12.set(2);

    Consensus::bitset b13(3);
    b13.set(0);
    b13.set(2);

    Consensus::bitset b23(3);
    b23.set(1);
    b23.set(2);

    Consensus::bitset b33(3);
    b33.set(0);
    b33.set(1);
    b33.set(2);

    ASSERT_TRUE(cluster.containsCluster(b1));
    ASSERT_TRUE(cluster.containsCluster(b2));
    ASSERT_TRUE(cluster.containsCluster(b3));
    ASSERT_TRUE(cluster.containsCluster(b33));
    ASSERT_FALSE(cluster.containsCluster(b12));
    ASSERT_FALSE(cluster.containsCluster(b11));
    ASSERT_FALSE(cluster.containsCluster(b13));
    ASSERT_FALSE(cluster.containsCluster(b23));



}

TEST_F(ClusterTreeTest, ClusterIntersectionTest)
{
    Locations::LocationManager locMgr;
    /*tree 1*/
    Domain::ITree<PropNode> t1;
    DummyObserver<PropNode> observer;

    PropNode* root = t1.getRoot();

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
    c1->setBranchLength(1);
    c11->setBranchLength(2);
    c12->setBranchLength(3);
    c111->setBranchLength(4);
    c112->setBranchLength(4);
    c4->setBranchLength(4);

    locMgr.addLocation("A", "A");
    locMgr.addLocation("B", "B");
    locMgr.addLocation("C", "C");
    locMgr.addLocation("D", "D");

    locMgr.addDistance(0, "A", "A");
    locMgr.addDistance(0, "B", "B");
    locMgr.addDistance(0, "C", "C");
    locMgr.addDistance(0, "D", "D");
    locMgr.addDistance(0, "A", "D");
    locMgr.addDistance(0, "B", "D");
    locMgr.addDistance(0, "C", "D");
    locMgr.addDistance(0, "D", "C");
    locMgr.addDistance(0, "D", "B");
    locMgr.addDistance(0, "D", "A");

    locMgr.addDistance(2, "A", "B");
    locMgr.addDistance(2, "A", "C");
    locMgr.addDistance(3, "B", "A");
    locMgr.addDistance(3, "B", "C");
    locMgr.addDistance(2, "C", "A");
    locMgr.addDistance(4, "C", "B");

    ClusterTree<PropNode, DummyObserver<PropNode > > cluster1(&t1, observer, locMgr);

    /*tree 2*/

    Domain::ITree<PropNode> t2;
    PropNode* root2 = t2.getRoot();

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
    d1->setBranchLength(1);
    d4->setBranchLength(4);
    d12->setBranchLength(3);
    d111->setBranchLength(4);
    d112->setBranchLength(4);
    d11->setBranchLength(2);


    ClusterTree<PropNode, DummyObserver<PropNode > > cluster2(&t2, observer, locMgr);
    /*intersection*/

    cluster1.intersectWith(cluster2);

    Consensus::bitset b1(4);
    b1.set(0);

    Consensus::bitset b2(4);
    b2.set(1);

    Consensus::bitset b3(4);
    b3.set(2);

    Consensus::bitset b4(4);
    b4.set(3);

    Consensus::bitset b11(4);
    b11.set(0);
    b11.set(1);

    Consensus::bitset b12(4);
    b12.set(1);
    b12.set(2);

    Consensus::bitset b13(4);
    b13.set(0);
    b13.set(2);


    Consensus::bitset b03(4);
    b03.set(0);
    b03.set(3);


    Consensus::bitset b14(4);
    b14.set(1);
    b14.set(3);


    Consensus::bitset b24(4);
    b24.set(2);
    b24.set(3);

    Consensus::bitset b23(4);
    b23.set(1);
    b23.set(2);

    Consensus::bitset b33(4);
    b33.set(0);
    b33.set(1);
    b33.set(2);

    Consensus::bitset b34(4);
    b34.set(0);
    b34.set(1);
    b34.set(3);

    Consensus::bitset b123(4);
    b123.set(1);
    b123.set(2);
    b123.set(3);

    Consensus::bitset b023(4);
    b023.set(0);
    b023.set(2);
    b023.set(3);

    Consensus::bitset b1234(4);
    b1234.set(0);
    b1234.set(1);
    b1234.set(2);
    b1234.set(3);

    ASSERT_TRUE(cluster1.containsCluster(b1));
    ASSERT_TRUE(cluster1.containsCluster(b2));
    ASSERT_TRUE(cluster1.containsCluster(b3));
    ASSERT_TRUE(cluster1.containsCluster(b4));
    ASSERT_TRUE(cluster1.containsCluster(b1234));
    ASSERT_TRUE(cluster1.containsCluster(b33));


    ASSERT_FALSE(cluster1.containsCluster(b12));
    ASSERT_FALSE(cluster1.containsCluster(b11));
    ASSERT_FALSE(cluster1.containsCluster(b03));
    ASSERT_FALSE(cluster1.containsCluster(b23));
    ASSERT_FALSE(cluster1.containsCluster(b023));
    ASSERT_FALSE(cluster1.containsCluster(b123));
    ASSERT_FALSE(cluster1.containsCluster(b24));
    ASSERT_FALSE(cluster1.containsCluster(b14));

    locMgr.clear();
}

TEST_F(ClusterTreeTest, ToTreeTest)
{
    Locations::LocationManager locMgr;
    /*tree 1*/
    Domain::ITree<PropNode> t1;
    PropNode* root = t1.getRoot();
    DummyObserver<PropNode> observer;
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
    c1->setBranchLength(2);
    c11->setBranchLength(1);
    c12->setBranchLength(2);
    c111->setBranchLength(3);
    c112->setBranchLength(4);
    c4->setBranchLength(4);

    locMgr.addLocation("A", "A");
    locMgr.addLocation("B", "B");
    locMgr.addLocation("C", "C");
    locMgr.addLocation("D", "D");

    locMgr.addDistance(0, "A", "A");
    locMgr.addDistance(0, "B", "B");
    locMgr.addDistance(0, "C", "C");
    locMgr.addDistance(0, "D", "D");
    locMgr.addDistance(0, "A", "D");
    locMgr.addDistance(0, "B", "D");
    locMgr.addDistance(0, "C", "D");
    locMgr.addDistance(0, "D", "C");
    locMgr.addDistance(0, "D", "B");
    locMgr.addDistance(0, "D", "A");

    locMgr.addDistance(2, "A", "B");
    locMgr.addDistance(2, "A", "C");
    locMgr.addDistance(3, "B", "A");
    locMgr.addDistance(3, "B", "C");
    locMgr.addDistance(2, "C", "A");
    locMgr.addDistance(4, "C", "B");

    ClusterTree<PropNode, DummyObserver<PropNode > > cluster1(&t1, observer, locMgr);

    /*tree 2*/

    Domain::ITree<PropNode> t2;
    PropNode* root2 = t2.getRoot();

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
    d1->setBranchLength(1);
    d11->setBranchLength(2);
    d12->setBranchLength(2);
    d111->setBranchLength(4);
    d112->setBranchLength(4);
    d4->setBranchLength(4);


    ClusterTree<PropNode, DummyObserver<PropNode > > cluster2(&t2, observer, locMgr);
    /*intersection*/

    cluster1.intersectWith(cluster2);

    ITree<PropNode> * tree = cluster1.toTree();
    PropNode* rootTest = tree->getRoot();
    ListIterator<PropNode, Node> it = rootTest->getChildrenIterator<PropNode>();
    ASSERT_STREQ("", rootTest->getName().c_str());
    ASSERT_TRUE(rootTest->getBranchLength() == 0);
    ASSERT_TRUE(it.count() == 2);

    PropNode* d1_2 = it.get();
    it.next();
    PropNode* d4_2 = it.get();

    ASSERT_TRUE(d4_2->isLeaf());
    ASSERT_STREQ("D", d4_2->getName().c_str());
    ASSERT_TRUE(d4_2->getBranchLength() == 4);

    ListIterator<PropNode, Node> it2 = d1_2->getChildrenIterator<PropNode>();
    ASSERT_STREQ("", d1_2->getName().c_str());
    ASSERT_TRUE(d1_2->getBranchLength() == 1);
    ASSERT_TRUE(it2.count() == 3);
    PropNode* d12_2 = it2.get();
    it2.next();
    PropNode* d111_2 = it2.get();
    it2.next();
    PropNode* d112_2 = it2.get();

    ASSERT_TRUE(d12_2->isLeaf());
    ASSERT_STREQ("A", d12_2->getName().c_str());
    ASSERT_TRUE(d12_2->getBranchLength() == 2);

    ASSERT_TRUE(d111_2->isLeaf());
    ASSERT_STREQ("B", d111_2->getName().c_str());
    ASSERT_TRUE(d111_2->getBranchLength() == 4);

    ASSERT_TRUE(d112_2->isLeaf());
    ASSERT_STREQ("C", d112_2->getName().c_str());
    ASSERT_TRUE(d112_2->getBranchLength() == 2);

    delete tree;
    locMgr.clear();
}

TEST_F(ClusterTreeTest, ToTreeDiferentBranchLengthTest)
{
    Locations::LocationManager locMgr;
    /*tree 1*/
    Domain::ITree<PropNode> t1;
    PropNode* root = t1.getRoot();
    DummyObserver<PropNode> observer;
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
    c1->setBranchLength(2);
    c11->setBranchLength(2);
    c12->setBranchLength(2);
    c111->setBranchLength(3);
    c112->setBranchLength(4);
    c4->setBranchLength(4);

    locMgr.addLocation("A", "A");
    locMgr.addLocation("B", "B");
    locMgr.addLocation("C", "C");
    locMgr.addLocation("D", "D");

    locMgr.addDistance(0, "A", "A");
    locMgr.addDistance(0, "B", "B");
    locMgr.addDistance(0, "C", "C");
    locMgr.addDistance(0, "D", "D");
    locMgr.addDistance(0, "A", "D");
    locMgr.addDistance(0, "B", "D");
    locMgr.addDistance(0, "C", "D");
    locMgr.addDistance(0, "D", "C");
    locMgr.addDistance(0, "D", "B");
    locMgr.addDistance(0, "D", "A");

    locMgr.addDistance(2, "A", "B");
    locMgr.addDistance(2, "A", "C");
    locMgr.addDistance(3, "B", "A");
    locMgr.addDistance(3, "B", "C");
    locMgr.addDistance(2, "C", "A");
    locMgr.addDistance(4, "C", "B");

    ClusterTree<PropNode, DummyObserver<PropNode > > cluster1(&t1, observer, locMgr);

    /*tree 2*/

    Domain::ITree<PropNode> t2;
    PropNode* root2 = t2.getRoot();

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
    d1->setBranchLength(1);
    d11->setBranchLength(1);
    d12->setBranchLength(1);
    d111->setBranchLength(1);
    d112->setBranchLength(1);
    d4->setBranchLength(3);


    ClusterTree<PropNode, DummyObserver<PropNode > > cluster2(&t2, observer, locMgr);
    /*intersection*/

    cluster1.intersectWith(cluster2);

    ITree<PropNode> * tree = cluster1.toTree();
    PropNode* rootTest = tree->getRoot();
    ListIterator<PropNode, Node> it = rootTest->getChildrenIterator<PropNode>();
    ASSERT_STREQ("", rootTest->getName().c_str());
    ASSERT_TRUE(rootTest->getBranchLength() == 0);
    ASSERT_TRUE(it.count() == 2);

    PropNode* d1_2 = it.get();
    it.next();
    PropNode* d4_2 = it.get();

    ASSERT_TRUE(d4_2->isLeaf());
    ASSERT_STREQ("D", d4_2->getName().c_str());
    ASSERT_TRUE(d4_2->getBranchLength() == 3);

    ListIterator<PropNode, Node> it2 = d1_2->getChildrenIterator<PropNode>();
    ASSERT_STREQ("", d1_2->getName().c_str());
    ASSERT_TRUE(d1_2->getBranchLength() == 1);
    ASSERT_TRUE(it2.count() == 3);
    PropNode* d12_2 = it2.get();
    it2.next();
    PropNode* d111_2 = it2.get();
    it2.next();
    PropNode* d112_2 = it2.get();

    ASSERT_TRUE(d12_2->isLeaf());
    ASSERT_STREQ("A", d12_2->getName().c_str());
    ASSERT_TRUE(d12_2->getBranchLength() == 1);

    ASSERT_TRUE(d111_2->isLeaf());
    ASSERT_STREQ("B", d111_2->getName().c_str());
    ASSERT_TRUE(d111_2->getBranchLength() == 1);

    ASSERT_TRUE(d112_2->isLeaf());
    ASSERT_STREQ("C", d112_2->getName().c_str());
    ASSERT_TRUE(d112_2->getBranchLength() == 1);

    locMgr.clear();
    delete tree;
}

}
