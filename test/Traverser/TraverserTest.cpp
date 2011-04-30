
#include <gtest/gtest.h>
#include <gmock/gmock.h> 

#include "../../src/Domain/INode.h"
#include "../../src/Phylopp/Traversal/Traverser.h"
#include "../../src/Phylopp/Traversal/INodeVisitor.h"
#include "../../src/Domain/ITreeCollection.h"
#include "../../src/Domain/ITree.h"
#include "../Domain/MockNode.h"

namespace {
    
    using namespace Domain;
    using namespace Traversal;
    using ::testing::Test;
    
    typedef MockNode<Domain::BaseAspect> TestNode;
    
    
    class TraverserTest : public Test 
    {
    protected:
        
        TestNode n;
        
        TraverserTest() { }
        
        virtual ~TraverserTest() { }
        
        
        virtual void SetUp() 
        {
            
        }
        
        virtual void TearDown() 
        {
            
        }        
    };
    
    class TagVisitor : public INodeVisitor<TestNode>
    {
    public:
        void visit(TestNode& n)
        {
            n.visited = true;
        }
    };
    
    /**
    *  Traverse Down Tests
    */
    
    //traverse  Down a tree that has only the root
    TEST_F(TraverserTest, TreaverseOnlyRootTest) 
    {        
        ITree<TestNode> itree;
        Domain::ITree<TestNode>& t = itree;
        TestNode* n = t.getRoot();
        
        Traverser<TestNode, TagVisitor> traverser;
        TagVisitor v;
        traverser.traverseDown(t, v);
        
        //all nodes should have been visited
        ASSERT_TRUE(n->visited);
    }
    
    //traverse Down a tree passing the tree itself
    TEST_F(TraverserTest, TraverseTreeDownTest) 
    {        
        ITree<TestNode> itree;
        Domain::ITree<TestNode>& t = itree;
        TestNode* n = t.getRoot();
        
        //build a three levels tree
        TestNode* c1 = n->addChild();
        TestNode* c2 = n->addChild();
        TestNode* c3 = n->addChild();
        TestNode* c4 = n->addChild();
        TestNode* c5 = n->addChild();
        
        TestNode* c1c1 = c1->addChild();
        TestNode* c1c2 = c1->addChild();
        TestNode* c1c3 = c1->addChild();
        TestNode* c1c4 = c1->addChild();
        
        TestNode* c2c1 = c1->addChild();
        TestNode* c2c2 = c1->addChild();
        
        Traverser<TestNode, TagVisitor> traverser;
        TagVisitor v;
        traverser.traverseDown(t, v);
        
        //all nodes should have been visited
        ASSERT_TRUE(n->visited);
        ASSERT_TRUE(c1->visited);
        ASSERT_TRUE(c2->visited);
        ASSERT_TRUE(c3->visited);
        ASSERT_TRUE(c4->visited);
        ASSERT_TRUE(c5->visited);
        
        ASSERT_TRUE(c1c1->visited);
        ASSERT_TRUE(c1c2->visited);
        ASSERT_TRUE(c1c3->visited);
        ASSERT_TRUE(c1c4->visited);
        
        ASSERT_TRUE(c2c1->visited);
        ASSERT_TRUE(c2c2->visited);
    }
    
    //traverse Down a tree passing the root node.
    TEST_F(TraverserTest, TraverseRootNodeDownTest) 
    {        
        ITree<TestNode> itree;
        Domain::ITree<TestNode>& t = itree;
        TestNode* n = t.getRoot();
        
        TestNode* c1 = n->addChild();
        TestNode* c2 = n->addChild();
        TestNode* c3 = n->addChild();
        TestNode* c4 = n->addChild();
        TestNode* c5 = n->addChild();
        
        TestNode* c1c1 = c1->addChild();
        TestNode* c1c2 = c1->addChild();
        TestNode* c1c3 = c1->addChild();
        TestNode* c1c4 = c1->addChild();
        
        TestNode* c2c1 = c1->addChild();
        TestNode* c2c2 = c1->addChild();
        
        Traverser<TestNode, TagVisitor> traverser;
        TagVisitor v;
        traverser.traverseDown(*n, v);
        
        //all nodes should have been visited
        ASSERT_TRUE(n->visited);
        ASSERT_TRUE(c1->visited);
        ASSERT_TRUE(c2->visited);
        ASSERT_TRUE(c3->visited);
        ASSERT_TRUE(c4->visited);
        ASSERT_TRUE(c5->visited);
        
        ASSERT_TRUE(c1c1->visited);
        ASSERT_TRUE(c1c2->visited);
        ASSERT_TRUE(c1c3->visited);
        ASSERT_TRUE(c1c4->visited);
        
        ASSERT_TRUE(c2c1->visited);
        ASSERT_TRUE(c2c2->visited);
    }
    
    //traverse Down a tree passing a non-root and non-leaf node
    TEST_F(TraverserTest, TraverseMiddleNodeDownTest) 
    {        
        ITree<TestNode> itree;
        Domain::ITree<TestNode>& t = itree;
        TestNode* n = t.getRoot();
        
        TestNode* c1 = n->addChild();
        TestNode* c2 = n->addChild();
        TestNode* c3 = n->addChild();
        TestNode* c4 = n->addChild();
        TestNode* c5 = n->addChild();
        
        TestNode* c1c1 = c1->addChild();
        TestNode* c1c2 = c1->addChild();
        TestNode* c1c3 = c1->addChild();
        TestNode* c1c4 = c1->addChild();
        
        TestNode* c2c1 = c2->addChild();
        TestNode* c2c2 = c2->addChild();
        
        Traverser<TestNode, TagVisitor> traverser;
        TagVisitor v;
        traverser.traverseDown(*c2, v);
        
        ASSERT_FALSE(n->visited);
        ASSERT_FALSE(c1->visited);
        ASSERT_TRUE(c2->visited);
        ASSERT_FALSE(c3->visited);
        ASSERT_FALSE(c4->visited);
        ASSERT_FALSE(c5->visited);
        
        ASSERT_FALSE(c1c1->visited);
        ASSERT_FALSE(c1c2->visited);
        ASSERT_FALSE(c1c3->visited);
        ASSERT_FALSE(c1c4->visited);
        
        ASSERT_TRUE(c2c1->visited);
        ASSERT_TRUE(c2c2->visited);
    }
    
    //traverse Down a tree passing a leaf node
    TEST_F(TraverserTest, TraverseLeafNodeDownTest) 
    {        
        ITree<TestNode> itree;
        Domain::ITree<TestNode>& t = itree;
        TestNode* n = t.getRoot();
        
        TestNode* c1 = n->addChild();
        TestNode* c2 = n->addChild();
        TestNode* c3 = n->addChild();
        TestNode* c4 = n->addChild();
        TestNode* c5 = n->addChild();
        
        TestNode* c1c1 = c1->addChild();
        TestNode* c1c2 = c1->addChild();
        TestNode* c1c3 = c1->addChild();
        TestNode* c1c4 = c1->addChild();
        
        TestNode* c2c1 = c2->addChild();
        TestNode* c2c2 = c2->addChild();
        
        Traverser<TestNode, TagVisitor> traverser;
        TagVisitor v;
        traverser.traverseDown(*c1c2, v);
        
        ASSERT_FALSE(n->visited);
        ASSERT_FALSE(c1->visited);
        ASSERT_FALSE(c2->visited);
        ASSERT_FALSE(c3->visited);
        ASSERT_FALSE(c4->visited);
        ASSERT_FALSE(c5->visited);
        
        ASSERT_FALSE(c1c1->visited);
        ASSERT_TRUE(c1c2->visited);
        ASSERT_FALSE(c1c3->visited);
        ASSERT_FALSE(c1c4->visited);
        
        ASSERT_FALSE(c2c1->visited);
        ASSERT_FALSE(c2c2->visited);
    }
    
    /**
    *  Traverse Up Tests
    */
    
    //traverse up a tree passing a leaf node
    TEST_F(TraverserTest, TraverseLeafUpTest) 
    {        
        ITree<TestNode> itree;
        Domain::ITree<TestNode>& t = itree;
        TestNode* n = t.getRoot();
        
        TestNode* c1 = n->addChild();
        TestNode* c2 = n->addChild();
        TestNode* c3 = n->addChild();
        TestNode* c4 = n->addChild();
        TestNode* c5 = n->addChild();
        
        TestNode* c1c1 = c1->addChild();
        TestNode* c1c2 = c1->addChild();
        TestNode* c1c3 = c1->addChild();
        TestNode* c1c4 = c1->addChild();
        
        TestNode* c2c1 = c2->addChild();
        TestNode* c2c2 = c2->addChild();
        
        Traverser<TestNode, TagVisitor> traverser;
        TagVisitor v;
        traverser.traverseUp(*c1c2, v);
        
        ASSERT_TRUE(n->visited);
        ASSERT_TRUE(c1->visited);
        ASSERT_FALSE(c2->visited);
        ASSERT_FALSE(c3->visited);
        ASSERT_FALSE(c4->visited);
        ASSERT_FALSE(c5->visited);
        
        ASSERT_FALSE(c1c1->visited);
        ASSERT_TRUE(c1c2->visited);
        ASSERT_FALSE(c1c3->visited);
        ASSERT_FALSE(c1c4->visited);
        
        ASSERT_FALSE(c2c1->visited);
        ASSERT_FALSE(c2c2->visited);
    }
    
    //traverse up a tree passing a middle node
    TEST_F(TraverserTest, TraverseMiddleNodeUpTest) 
    {        
        ITree<TestNode> itree;
        Domain::ITree<TestNode>& t = itree;
        TestNode* n = t.getRoot();
        
        TestNode* c1 = n->addChild();
        TestNode* c2 = n->addChild();
        TestNode* c3 = n->addChild();
        TestNode* c4 = n->addChild();
        TestNode* c5 = n->addChild();
        
        TestNode* c1c1 = c1->addChild();
        TestNode* c1c2 = c1->addChild();
        TestNode* c1c3 = c1->addChild();
        TestNode* c1c4 = c1->addChild();
        
        TestNode* c2c1 = c2->addChild();
        TestNode* c2c2 = c2->addChild();
        
        Traverser<TestNode, TagVisitor> traverser;
        TagVisitor v;
        traverser.traverseUp(*c1, v);
        
        //all nodes should have been visited
        ASSERT_TRUE(n->visited);
        ASSERT_TRUE(c1->visited);
        ASSERT_FALSE(c2->visited);
        ASSERT_FALSE(c3->visited);
        ASSERT_FALSE(c4->visited);
        ASSERT_FALSE(c5->visited);
        
        ASSERT_FALSE(c1c1->visited);
        ASSERT_FALSE(c1c2->visited);
        ASSERT_FALSE(c1c3->visited);
        ASSERT_FALSE(c1c4->visited);
        
        ASSERT_FALSE(c2c1->visited);
        ASSERT_FALSE(c2c2->visited);
    }
    
    //traverse up a tree passing a root node
    TEST_F(TraverserTest, TraverseRootUpTest) 
    {        
        ITree<TestNode> itree;
        Domain::ITree<TestNode>& t = itree;
        TestNode* n = t.getRoot();
        
        TestNode* c1 = n->addChild();
        TestNode* c2 = n->addChild();
        TestNode* c3 = n->addChild();
        TestNode* c4 = n->addChild();
        TestNode* c5 = n->addChild();
        
        TestNode* c1c1 = c1->addChild();
        TestNode* c1c2 = c1->addChild();
        TestNode* c1c3 = c1->addChild();
        TestNode* c1c4 = c1->addChild();
        
        TestNode* c2c1 = c2->addChild();
        TestNode* c2c2 = c2->addChild();
        
        Traverser<TestNode, TagVisitor> traverser;
        TagVisitor v;
        traverser.traverseUp(*n, v);
        
        //all nodes should have been visited
        ASSERT_TRUE(n->visited);
        ASSERT_FALSE(c1->visited);
        ASSERT_FALSE(c2->visited);
        ASSERT_FALSE(c3->visited);
        ASSERT_FALSE(c4->visited);
        ASSERT_FALSE(c5->visited);
        
        ASSERT_FALSE(c1c1->visited);
        ASSERT_FALSE(c1c2->visited);
        ASSERT_FALSE(c1c3->visited);
        ASSERT_FALSE(c1c4->visited);
        
        ASSERT_FALSE(c2c1->visited);
        ASSERT_FALSE(c2c2->visited);
    }
}
