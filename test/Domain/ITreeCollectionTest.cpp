
#include <gtest/gtest.h>
#include <gmock/gmock.h> 

#include "../../src/Domain/ITreeCollection.h"
#include "MockNode.h"

namespace {
    
    using namespace Domain;
    using ::testing::Test;
    
    
    class ITreeCollectionTest : public Test 
    {
    protected:
        
        TestNode n;
        
        ITreeCollectionTest() { }
        
        virtual ~ITreeCollectionTest() { }
        
        
        virtual void SetUp() 
        {
        }
        
        virtual void TearDown() 
        {
            
        }        
    };
    
    //adding trees to collections, and iterating through the collection
    TEST_F(ITreeCollectionTest, AddTreeTest) 
    {               
        ITreeCollection<TestNode> col;
        ITree<TestNode>* t1 = col.addTree();
        
        //recently added tree shouldn't be null
        ASSERT_FALSE(t1 == NULL);        
        
        ListIterator<ITree<TestNode> >* it = col.getIterator();
        
        ITree<TestNode>* tAux = it-> get();
        
        //if we iterate through the trees of the collection, there it shouldn
        //be only one, and particularly the one added previously
        EXPECT_EQ(t1, tAux);
        EXPECT_EQ(it->count(), 1);
        
        delete it;
        
        ITree<TestNode>* t2 = col.addTree();
        ITree<TestNode>* t3 = col.addTree();
        ITree<TestNode>* t4 = col.addTree();
        ITree<TestNode>* t5 = col.addTree();
        ITree<TestNode>* t6 = col.addTree();
        
        ListIterator<ITree<TestNode> >* it2 = col.getIterator();
        
        EXPECT_EQ(it2->count(), 6);
        
        //TODO: iterate!
        
        delete it2;
    }
}
