
#include <gtest/gtest.h>
#include <gmock/gmock.h> 
#include "../../src/Phyloloc/Propagator/PropagatorAspect.h"
#include "../../src/Domain/INode.h"
#include "../../src/Domain/LocationAspect.h"

namespace {
    
    using namespace Propagation;
    using ::testing::Test;
    using namespace Locations;
    
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
        const float epsilon = 0.0001f;
         
        PropNode root;
        std::vector<float> vRoot;
        vRoot.push_back(0.0);
        vRoot.push_back(0.0);
        vRoot.push_back(0.0);
        root.probabilities = vRoot;
        PropNode* c1 = root.addChild<PropNode>();
        PropNode* c2 = root.addChild<PropNode>();
        PropNode* c3 = root.addChild<PropNode>();
        PropNode* c4 = root.addChild<PropNode>();
                
        std::vector<float> v1;
        v1.push_back(1.0);
        v1.push_back(0.0);
        v1.push_back(0.0);
        c1->probabilities = v1;
        std::vector<float> v2;
        v2.push_back(1.0);
        v2.push_back(0.0);
        v2.push_back(0.0);
        c2->probabilities = v2;
        std::vector<float> v3;
        v3.push_back(0.0);
        v3.push_back(1.0);
        v3.push_back(0.0);
        c3->probabilities = v3;
        std::vector<float> v4;
        v4.push_back(0.0);
        v4.push_back(0.0);
        v4.push_back(1.0);
        c4->probabilities = v4;
        
        std::vector<float> dispersalVector;
        dispersalVector.resize(3, 0);
        
        
        //root.propagateFromChildren(0, dispersalVector, 0, 0);
        ASSERT_TRUE(abs(root.probabilities[0] - 0.5) < epsilon);
        ASSERT_TRUE(abs(root.probabilities[1] - 0.25) < epsilon);
        ASSERT_TRUE(abs(root.probabilities[2] - 0.25) < epsilon);
        
        c1->propagateFromParent(0, dispersalVector, 0, 0);;
        ASSERT_TRUE(abs(c1->probabilities[0] - 0.75) < epsilon);
        ASSERT_TRUE(abs(c1->probabilities[1] - 0.125) < epsilon);
        ASSERT_TRUE(abs(c1->probabilities[2] - 0.125) < epsilon);
        c2->propagateFromParent(0, dispersalVector, 0, 0);;
        ASSERT_TRUE(abs(c2->probabilities[0] - 0.75) < epsilon);
        ASSERT_TRUE(abs(c2->probabilities[1] - 0.125) < epsilon);
        ASSERT_TRUE(abs(c2->probabilities[2] - 0.125) < epsilon);
        c3->propagateFromParent(0, dispersalVector, 0, 0);;
        ASSERT_TRUE(abs(c3->probabilities[0] - 0.25) < epsilon);
        ASSERT_TRUE(abs(c3->probabilities[1] - 0.625) < epsilon);
        ASSERT_TRUE(abs(c3->probabilities[2] - 0.125) < epsilon);
        c4->propagateFromParent(0, dispersalVector, 0, 0);;
        ASSERT_TRUE(abs(c4->probabilities[0] - 0.25) < epsilon);
        ASSERT_TRUE(abs(c4->probabilities[1] - 0.125) < epsilon);
        ASSERT_TRUE(abs(c4->probabilities[2] - 0.625) < epsilon);

        delete c1;
        delete c2;
        delete c3;
        delete c4;
    }    
    
    
}
