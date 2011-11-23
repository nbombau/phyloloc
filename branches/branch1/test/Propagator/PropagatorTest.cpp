
#include <gtest/gtest.h>
#include <gmock/gmock.h> 
#include "../../src/Phyloloc/Propagator/Propagator.h"
#include "../../src/Domain/INode.h"
#include "../../src/Domain/ITree.h"
#include "../../src/Domain/LocationAspect.h"

namespace {
    
    using namespace Propagation;
    using ::testing::Test;
    using namespace Locations;
    using namespace Domain;
    
    class PropagatorTest : public Test 
    {
    protected:
        
        PropagatorTest() { }
        
        virtual ~PropagatorTest() { }
        
        
        virtual void SetUp() 
        {
            
        }
        
        virtual void TearDown() 
        {
            
        }        
    };
    
    typedef Propagation::PropagatorAspect<Locations::LocationAspect<Domain::Node> > PropNode;
    
    
    TEST_F(PropagatorTest, TwoPassPropagatorTest) 
    {        
        
        /*           R
         * A         B           C         D 
         * branchLenghtFactorWeight 0.400000
         * g eographicFactorWeight 0.400000   *
         * dispersalVector[i] [0.5 0.25 0.25]
         * BCLF = [0.9 0.8 0.7 0.6]
         */
        
        const float epsilon = 0.001f;
        
        ITree<PropNode> t;
        
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
        
        
        
        Propagator<PropNode>::propagate(&t, 2, 0.4, 0.4);

        
        
        ASSERT_TRUE(fabs(root->probabilities[0] - 0.533) < epsilon);
        ASSERT_TRUE(fabs(root->probabilities[1] - 0.233) < epsilon);
        ASSERT_TRUE(fabs(root->probabilities[2] - 0.233) < epsilon);
        
        ASSERT_TRUE(fabs(c1->probabilities[0] - 0.790950) < epsilon);
        ASSERT_TRUE(fabs(c1->probabilities[1] - 0.104525) < epsilon);
        ASSERT_TRUE(fabs(c1->probabilities[2] - 0.104525) < epsilon);

        ASSERT_TRUE(fabs(c2->probabilities[0] - 0.792344) < epsilon);
        ASSERT_TRUE(fabs(c2->probabilities[1] - 0.103828) < epsilon);
        ASSERT_TRUE(fabs(c2->probabilities[2] - 0.103828) < epsilon);   

        ASSERT_TRUE(fabs(c3->probabilities[0] - 0.298901) < epsilon);
        ASSERT_TRUE(fabs(c3->probabilities[1] - 0.589561) < epsilon);
        ASSERT_TRUE(fabs(c3->probabilities[2] - 0.111538) < epsilon);

        ASSERT_TRUE(fabs(c4->probabilities[0] - 0.301176) < epsilon);
        ASSERT_TRUE(fabs(c4->probabilities[1] - 0.111176) < epsilon);
        ASSERT_TRUE(fabs(c4->probabilities[2] - 0.587647) < epsilon);

        
        PropNode::clear();
    }    
    
    
}
