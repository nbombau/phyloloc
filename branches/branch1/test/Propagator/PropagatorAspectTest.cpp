
#include <gtest/gtest.h>
#include <gmock/gmock.h> 
#include "../../src/Phyloloc/Propagator/PropagatorAspect.h"
#include "../../src/Domain/INode.h"
#include "../../src/Domain/LocationAspect.h"

namespace {
    
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
        
        PropNode::addLocation("A", "A");
        PropNode::addLocation("B", "B");
        PropNode::addLocation("C", "C");
        
        PropNode::addDistance(0, "A", "A");
        PropNode::addDistance(0, "B", "B");
        PropNode::addDistance(0, "C", "C");
        
        PropNode::addDistance(2, "A", "B");
        PropNode::addDistance(2, "A", "C");
        PropNode::addDistance(3, "B", "A");
        PropNode::addDistance(3, "B", "C");
        PropNode::addDistance(2, "C", "A");
        PropNode::addDistance(4, "C", "B");
        
        const std::vector<float>& dispersalVector = PropNode::getDispersionVector();
        
        c1->propagateFromChildren(10, dispersalVector, 0, 0);
        c2->propagateFromChildren(10, dispersalVector, 0, 0);
        c3->propagateFromChildren(10, dispersalVector, 0, 0);
        c4->propagateFromChildren(10, dispersalVector, 0, 0);
        root.propagateFromChildren(10, dispersalVector, 0, 0);
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
        
        PropNode::clear();
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
        
        PropNode::addLocation("A", "A");
        PropNode::addLocation("B", "B");
        PropNode::addLocation("C", "C");
        
        PropNode::addDistance(0, "A", "A");
        PropNode::addDistance(0, "B", "B");
        PropNode::addDistance(0, "C", "C");
        
        PropNode::addDistance(2, "A", "B");
        PropNode::addDistance(2, "A", "C");
        PropNode::addDistance(3, "B", "A");
        PropNode::addDistance(3, "B", "C");
        PropNode::addDistance(2, "C", "A");
        PropNode::addDistance(4, "C", "B");
        
        const std::vector<float>& dispersalVector = PropNode::getDispersionVector();
        
        c1->propagateFromChildren(10, dispersalVector, 0.4, 0.4);
        c2->propagateFromChildren(10, dispersalVector, 0.4, 0.4);
        c3->propagateFromChildren(10, dispersalVector, 0.4, 0.4);
        c4->propagateFromChildren(10, dispersalVector, 0.4, 0.4);
        root.propagateFromChildren(10, dispersalVector, 0.4, 0.4);
        
        ASSERT_TRUE(fabs(root.probabilities[0] - 0.533) < epsilon);
        ASSERT_TRUE(fabs(root.probabilities[1] - 0.233) < epsilon);
        ASSERT_TRUE(fabs(root.probabilities[2] - 0.233) < epsilon);
        
        c1->propagateFromParent(10, dispersalVector, 0.4, 0.4);
        
        ASSERT_TRUE(fabs(c1->probabilities[0] - 0.790950) < epsilon);
        ASSERT_TRUE(fabs(c1->probabilities[1] - 0.104525) < epsilon);
        ASSERT_TRUE(fabs(c1->probabilities[2] - 0.104525) < epsilon);
        c2->propagateFromParent(10, dispersalVector, 0.4, 0.4);
        ASSERT_TRUE(fabs(c2->probabilities[0] - 0.792344) < epsilon);
        ASSERT_TRUE(fabs(c2->probabilities[1] - 0.103828) < epsilon);
        ASSERT_TRUE(fabs(c2->probabilities[2] - 0.103828) < epsilon); 
        c3->propagateFromParent(10, dispersalVector, 0.4, 0.4);        
        ASSERT_TRUE(fabs(c3->probabilities[0] - 0.298901) < epsilon);
        ASSERT_TRUE(fabs(c3->probabilities[1] - 0.589561) < epsilon);
        ASSERT_TRUE(fabs(c3->probabilities[2] - 0.111538) < epsilon);
        c4->propagateFromParent(10, dispersalVector, 0.4, 0.4);
        ASSERT_TRUE(fabs(c4->probabilities[0] - 0.301176) < epsilon);
        ASSERT_TRUE(fabs(c4->probabilities[1] - 0.111176) < epsilon);
        ASSERT_TRUE(fabs(c4->probabilities[2] - 0.587647) < epsilon);

        delete c1;
        delete c2;
        delete c3;
        delete c4;
        
        PropNode::clear();
    }    
    
    
}
