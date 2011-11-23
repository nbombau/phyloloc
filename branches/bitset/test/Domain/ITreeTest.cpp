
#include <gtest/gtest.h>
#include <gmock/gmock.h> 

#include "../../src/Domain/ITree.h"
#include "MockNode.h"

namespace {
    
    using namespace Domain;
    using ::testing::Test;
        
    typedef MockNode<Domain::Node> TestNode;
    
    
    class ITreeTest : public Test 
    {
    protected:
        
        TestNode n;
        
        ITreeTest() { }
        
        virtual ~ITreeTest() { }
        
        
        virtual void SetUp() 
        {
        }
        
        virtual void TearDown() 
        {
            
        }        
    };
    
    //Single node, should be root and leaf
    TEST_F(ITreeTest, TreeCreationTest) 
    {        
        ITree<TestNode> t;
        TestNode* n = t.getRoot();
        
        ASSERT_FALSE(n == NULL);        
    }
}
