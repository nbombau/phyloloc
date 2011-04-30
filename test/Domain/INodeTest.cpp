
#include <gtest/gtest.h>

#include "../../src/Domain/INode.h"

namespace {

using namespace Domain;
using ::testing::Test;


    template <class T>
    class DummyNode : public Domain::Node<DummyNode<T> >    
    {
    
    };

    typedef DummyNode<Domain::BaseAspect> TestNode;
    
    
    class INodeTest : public Test 
    {
    protected:

        TestNode n;
        BranchLength epsilon;
        
        INodeTest() { }

        virtual ~INodeTest() { }


        virtual void SetUp() 
        {
            epsilon = 0.0001;
        }

        virtual void TearDown() 
        {
        
        }        
    };

    // Check the getters work properly
    TEST_F(INodeTest, GettersTest) 
    {
        n.setLocation("LocationA");
        n.setName("A");
        n.setBranchLength(0.1);
        
        EXPECT_EQ(n.getLocation(), "LocationA");
        EXPECT_EQ(n.getName(), "A");
        ASSERT_TRUE( (n.getBranchLength() - BranchLength(0.1)) < epsilon );
    }
    
    //Single node, should be root and leaf
    TEST_F(INodeTest, SingleNodeTopologyTest) 
    {
        ASSERT_TRUE( n.isRoot() );
        ASSERT_TRUE( n.isLeaf() );
    }
    
    //Add child, and check bindings
   TEST_F(INodeTest, AddChildTest) 
    {
        TestNode* child1 = n.addChild();
        
        //check child's parent is n
        EXPECT_EQ( child1->getParent(), &n );
        
        ListIterator<TestNode>* it = n.getChildrenIterator();
        
        //check child1 is n's descendant
        TestNode* aux = &(it->get());
        ASSERT_FALSE(aux == NULL);
        EXPECT_EQ(aux, child1);
        
        delete it;
        
        //n should be root, but not leaf anymore
        ASSERT_FALSE(n.isLeaf());
        ASSERT_TRUE(n.isRoot());
        
        //aux should be leaf, but not root
        ASSERT_TRUE(aux->isLeaf());
        ASSERT_FALSE(aux->isRoot());
        
        //check several childs can be added
        TestNode* child2 = n.addChild();
        TestNode* child3 = n.addChild();
        TestNode* child4 = n.addChild();
        TestNode* child5 = n.addChild();
        
        child1->setName("c1");
        child2->setName("c2");
        child3->setName("c3");
        child4->setName("c4");
        child5->setName("c5");
        
        //Check iteration
        ListIterator<TestNode>* iter = n.getChildrenIterator();
        
        EXPECT_EQ(iter->count(), 5); //5 childs have been added
                
        delete iter;
    }    
}
