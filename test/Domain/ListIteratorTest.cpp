
#include <stddef.h>
#include <gtest/gtest.h>

#include "../../src/Domain/ListIterator.h"


namespace {

using namespace Domain;
using ::testing::Test;  
    
    class DummyClass
    {
    public:      
        DummyClass(int n): num(n) {}
        
        int getNum() const
        {
            return num;
        }
    private: 
        int num;
    };

    class ListIteratorTest : public Test 
    {
    protected:

        
        ListIteratorTest() { }

        virtual ~ListIteratorTest() { }

        std::list<DummyClass*> list;
        
        virtual void SetUp() 
        {
            
            
            DummyClass* dummy1 = new DummyClass(1);
            DummyClass* dummy2 = new DummyClass(2);
            DummyClass* dummy3 = new DummyClass(3);
            DummyClass* dummy4 = new DummyClass(4);
            DummyClass* dummy5 = new DummyClass(5);
            
            list.push_back(dummy1);
            list.push_back(dummy2);
            list.push_back(dummy3);
            list.push_back(dummy4);
            list.push_back(dummy5);
        }

        virtual void TearDown() 
        {
        
        }        
    };
    
    // Check the getters work properly
    TEST_F(ListIteratorTest, IterationTest) 
    {
        ListIterator<DummyClass> it = ListIterator<DummyClass>(list);
        
        EXPECT_EQ(it.count(), 5);
        
        int i = 1;
        while(!it.end())
        {
            DummyClass c = it.get();
            EXPECT_EQ(i, c.getNum());
            i++;
            it.next();
        }        
    }
}
