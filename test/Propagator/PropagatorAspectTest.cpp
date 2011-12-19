#include <gtest/gtest.h>

#include "../../src/Phyloloc/Propagator/PropagatorAspect.h"
#include "../../src/Domain/INode.h"
#include "../../src/Domain/LocationAspect.h"

namespace
{
using namespace std;
using namespace Propagation;
using ::testing::Test;
using namespace Locations;
using namespace Domain;

class PropagatorAspectTest : public Test
{
protected:

    PropagatorAspectTest() { }

    virtual ~PropagatorAspectTest() { }


    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {

    }
};

typedef Propagation::PropagatorAspect<Locations::LocationAspect<Domain::Node> > PropNode;

TEST_F(PropagatorAspectTest, propagateFromChildrenUnweightedTest)
{
    const float epsilon = 0.001f;
    Locations::LocationManager locationManager;


    PropNode root;

    PropNode* c1 = root.addChild<PropNode>();
    PropNode* c2 = root.addChild<PropNode>();
    PropNode* c3 = root.addChild<PropNode>();
    PropNode* c4 = root.addChild<PropNode>();

    c1->setName("A");
    c2->setName("A");
    c3->setName("B");
    c4->setName("C");

    root.setBranchLength(0);
    c1->setBranchLength(1);
    c2->setBranchLength(2);
    c3->setBranchLength(3);
    c4->setBranchLength(4);

    locationManager.addLocation("A", "A");
    locationManager.addLocation("B", "B");
    locationManager.addLocation("C", "C");

    locationManager.addDistance(0, "A", "A");
    locationManager.addDistance(0, "B", "B");
    locationManager.addDistance(0, "C", "C");

    locationManager.addDistance(2, "A", "B");
    locationManager.addDistance(2, "A", "C");
    locationManager.addDistance(3, "B", "A");
    locationManager.addDistance(3, "B", "C");
    locationManager.addDistance(2, "C", "A");
    locationManager.addDistance(4, "C", "B");

    const std::vector<float>& dispersalVector = locationManager.getDispersionVector();

    c1->propagateFromChildren(10, dispersalVector, 0, 0, locationManager);
    c2->propagateFromChildren(10, dispersalVector, 0, 0, locationManager);
    c3->propagateFromChildren(10, dispersalVector, 0, 0, locationManager);
    c4->propagateFromChildren(10, dispersalVector, 0, 0, locationManager);
    root.propagateFromChildren(10, dispersalVector, 0, 0, locationManager);
    ASSERT_TRUE(fabs(root.probabilities[0] - 0.5) < epsilon);
    ASSERT_TRUE(fabs(root.probabilities[1] - 0.25) < epsilon);
    ASSERT_TRUE(fabs(root.probabilities[2] - 0.25) < epsilon);

    c1->propagateFromParent(10, dispersalVector, 0, 0);;

    ASSERT_TRUE(fabs(c1->probabilities[0] - 0.75) < epsilon);
    ASSERT_TRUE(fabs(c1->probabilities[1] - 0.125) < epsilon);
    ASSERT_TRUE(fabs(c1->probabilities[2] - 0.125) < epsilon);
    c2->propagateFromParent(10, dispersalVector, 0, 0);;

    ASSERT_TRUE(fabs(c2->probabilities[0] - 0.75) < epsilon);
    ASSERT_TRUE(fabs(c2->probabilities[1] - 0.125) < epsilon);
    ASSERT_TRUE(fabs(c2->probabilities[2] - 0.125) < epsilon);
    c3->propagateFromParent(10, dispersalVector, 0, 0);;

    ASSERT_TRUE(fabs(c3->probabilities[0] - 0.25) < epsilon);
    ASSERT_TRUE(fabs(c3->probabilities[1] - 0.625) < epsilon);
    ASSERT_TRUE(fabs(c3->probabilities[2] - 0.125) < epsilon);

    c4->propagateFromParent(10, dispersalVector, 0, 0);;

    ASSERT_TRUE(fabs(c4->probabilities[0] - 0.25) < epsilon);
    ASSERT_TRUE(fabs(c4->probabilities[1] - 0.125) < epsilon);
    ASSERT_TRUE(fabs(c4->probabilities[2] - 0.625) < epsilon);

    delete c1;
    delete c2;
    delete c3;
    delete c4;
}

TEST_F(PropagatorAspectTest, propagateFromChildrenWeightedTest)
{

    /*           R
     * A         B           C         D
     * branchLenghtFactorWeight 0.400000
     * g eographicFactorWeight 0.400000   *
     * dispersalVector[i] [0.5 0.25 0.25]
     * BCLF = [0.9 0.8 0.7 0.6]
     */

    const float epsilon = 0.001f;
    Locations::LocationManager locationManager;

    PropNode root;

    PropNode* c1 = root.addChild<PropNode>();
    PropNode* c2 = root.addChild<PropNode>();
    PropNode* c3 = root.addChild<PropNode>();
    PropNode* c4 = root.addChild<PropNode>();

    c1->setName("A");
    c2->setName("A");
    c3->setName("B");
    c4->setName("C");

    c1->setBranchLength(1);
    c2->setBranchLength(2);
    c3->setBranchLength(3);
    c4->setBranchLength(4);

    locationManager.addLocation("A", "A");
    locationManager.addLocation("B", "B");
    locationManager.addLocation("C", "C");

    locationManager.addDistance(0, "A", "A");
    locationManager.addDistance(0, "B", "B");
    locationManager.addDistance(0, "C", "C");

    locationManager.addDistance(2, "A", "B");
    locationManager.addDistance(2, "A", "C");
    locationManager.addDistance(3, "B", "A");
    locationManager.addDistance(3, "B", "C");
    locationManager.addDistance(2, "C", "A");
    locationManager.addDistance(4, "C", "B");

    const std::vector<float>& dispersalVector = locationManager.getDispersionVector();

    c1->propagateFromChildren(10, dispersalVector, 0.4, 0.4, locationManager);
    c2->propagateFromChildren(10, dispersalVector, 0.4, 0.4, locationManager);
    c3->propagateFromChildren(10, dispersalVector, 0.4, 0.4, locationManager);
    c4->propagateFromChildren(10, dispersalVector, 0.4, 0.4, locationManager);
    root.propagateFromChildren(10, dispersalVector, 0.4, 0.4, locationManager);
    
    ASSERT_TRUE(fabs(root.probabilities[0] - 0.513386) < epsilon);
    ASSERT_TRUE(fabs(root.probabilities[1] - 0.243307) < epsilon);
    ASSERT_TRUE(fabs(root.probabilities[2] - 0.243307) < epsilon);

    c1->propagateFromParent(10, dispersalVector, 0.4, 0.4);
    
    ASSERT_TRUE(fabs(c1->probabilities[0] - 0.767550) < epsilon);
    ASSERT_TRUE(fabs(c1->probabilities[1] - 0.116225) < epsilon);
    ASSERT_TRUE(fabs(c1->probabilities[2] - 0.116225) < epsilon);
    c2->propagateFromParent(10, dispersalVector, 0.4, 0.4);
    
    ASSERT_TRUE(fabs(c2->probabilities[0] - 0.76809) < epsilon);
    ASSERT_TRUE(fabs(c2->probabilities[1] - 0.11596) < epsilon);
    ASSERT_TRUE(fabs(c2->probabilities[2] - 0.11596) < epsilon);
    c3->propagateFromParent(10, dispersalVector, 0.4, 0.4);

    ASSERT_TRUE(fabs(c3->probabilities[0] - 0.269536) < epsilon);
    ASSERT_TRUE(fabs(c3->probabilities[1] - 0.610913) < epsilon);
    ASSERT_TRUE(fabs(c3->probabilities[2] - 0.11955) < epsilon);
    c4->propagateFromParent(10, dispersalVector, 0.4, 0.4);
    
    ASSERT_TRUE(fabs(c4->probabilities[0] - 0.270266) < epsilon);
    ASSERT_TRUE(fabs(c4->probabilities[1] - 0.11943) < epsilon);
    ASSERT_TRUE(fabs(c4->probabilities[2] - 0.61030) < epsilon);

    delete c1;
    delete c2;
    delete c3;
    delete c4;
}


}

