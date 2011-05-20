
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

        DummyClass* dummy1;
        DummyClass* dummy2;
        DummyClass* dummy3;
        DummyClass* dummy4;
        DummyClass* dummy5;
        
        ListIteratorTest() { }

        virtual ~ListIteratorTest() { }

        std::list<DummyClass*> list;
        
        virtual void SetUp() 
        {
            
            
            dummy1 = new DummyClass(1);
            dummy2 = new DummyClass(2);
            dummy3 = new DummyClass(3);
            dummy4 = new DummyClass(4);
            dummy5 = new DummyClass(5);
            
            list.push_back(dummy1);
            list.push_back(dummy2);
            list.push_back(dummy3);
            list.push_back(dummy4);
            list.push_back(dummy5);
        }

        virtual void TearDown() 
        {
            delete dummy1;
            delete dummy2;
            delete dummy3;
            delete dummy4;
            delete dummy5;          
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
            DummyClass* c = it.get();
            EXPECT_EQ(i, c->getNum());
            i++;
            it.next();
        }        
    }
}
