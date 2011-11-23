#include <gtest/gtest.h>
#include "../../src/Phylopp/Consensor/bitset.h"

namespace {
   
    using ::testing::Test;
    using namespace Consensus;
    
    class bitsetTest : public Test 
    {
    protected:
        
        bitsetTest() { }
        
        virtual ~bitsetTest() { }
        
        virtual void SetUp() 
        {
            
        }
        
        virtual void TearDown() 
        {
            
        }        
    };
    
    TEST_F(bitsetTest, sizeTest) 
    {
        bitset b(5);
        
        EXPECT_EQ(b.size(), 5);
        
        bitset a(b);
        
        EXPECT_EQ(a.size(), 5);
    }
    
    TEST_F(bitsetTest, clearEmptyTest) 
    {
        bitset b(5);
        
        EXPECT_FALSE(b.empty());
        
        b.clear();
        
        EXPECT_TRUE(b.empty());
    }
    
    TEST_F(bitsetTest, flipTest) 
    {
        bitset b(5);
        
        b.set(1);
        b.set(3);
        
        b.flip();
        
        EXPECT_EQ(b[0], true);
        EXPECT_EQ(b[1], false);
        EXPECT_EQ(b[2], true);
        EXPECT_EQ(b[3], false);
        EXPECT_EQ(b[4], true);
        
    }
  
    TEST_F(bitsetTest, setResetTest) 
    {
        bitset b(5);
        
        b.set(1);
        b.set(2, bitset::bit::false_bit);
        EXPECT_EQ(b[1], true);
        EXPECT_EQ(b[2], false);
        b.reset(1);
        EXPECT_EQ(b[1], false);
        EXPECT_EQ(b[2], false);
        
        b.set();
        EXPECT_EQ(b[0], true);
        EXPECT_EQ(b[1], true);
        EXPECT_EQ(b[2], true);
        EXPECT_EQ(b[3], true);
        EXPECT_EQ(b[4], true);
        
        b.reset();
        
        EXPECT_EQ(b[0], false);
        EXPECT_EQ(b[1], false);
        EXPECT_EQ(b[2], false);
        EXPECT_EQ(b[3], false);
        EXPECT_EQ(b[4], false);
    }
    
    TEST_F(bitsetTest, booleanOpTests) 
    {
        bitset b(5);
        b.set(1);
        b.set(2);
        
        bitset a(5);             

        a.set(4);
        
        //or
        b |= a;
        EXPECT_EQ(b[0], false);
        EXPECT_EQ(b[1], true);
        EXPECT_EQ(b[2], true);
        EXPECT_EQ(b[3], false);
        EXPECT_EQ(b[4], true);
        
        //and
        b &= a;
        
        EXPECT_EQ(b[0], false);
        EXPECT_EQ(b[1], false);
        EXPECT_EQ(b[2], false);
        EXPECT_EQ(b[3], false);
        EXPECT_EQ(b[4], true);
        
        //not
        
        bitset c = ~b;
        EXPECT_EQ(c[0], true);
        EXPECT_EQ(c[1], true);
        EXPECT_EQ(c[2], true);
        EXPECT_EQ(c[3], true);
        EXPECT_EQ(c[4], false);
        
        //conditional not
        b ^= c;
        
        EXPECT_EQ(b[0], true);
        EXPECT_EQ(b[1], true);
        EXPECT_EQ(b[2], true);
        EXPECT_EQ(b[3], true);
        EXPECT_EQ(b[4], true);
        
        //shift
        
        b <<= 2;
        
        EXPECT_EQ(b[0], true);
        EXPECT_EQ(b[1], true);
        EXPECT_EQ(b[2], true);
        EXPECT_EQ(b[3], false);
        EXPECT_EQ(b[4], false);
        
        b >>=1;
        
        EXPECT_EQ(b[0], false);
        EXPECT_EQ(b[1], true);
        EXPECT_EQ(b[2], true);
        EXPECT_EQ(b[3], true);
        EXPECT_EQ(b[4], false);
        
        b >>=1;
        
        EXPECT_EQ(b[0], false);
        EXPECT_EQ(b[1], false);
        EXPECT_EQ(b[2], true);
        EXPECT_EQ(b[3], true);
        EXPECT_EQ(b[4], true);
        
        b <<=1;
        
        EXPECT_EQ(b[0], false);
        EXPECT_EQ(b[1], true);
        EXPECT_EQ(b[2], true);
        EXPECT_EQ(b[3], true);
        EXPECT_EQ(b[4], false);
        
        bitset d = b >> 2;
        
        EXPECT_EQ(d[0], false);
        EXPECT_EQ(d[1], false);
        EXPECT_EQ(d[2], false);
        EXPECT_EQ(d[3], true);
        EXPECT_EQ(d[4], true);
    }
    
    TEST_F(bitsetTest, classBooleanOpTests) 
    {
        bitset b(5);
        b.set(1);
        b.set(2);
        
        bitset a(5);             
        
        a.set(4);
        
        
        EXPECT_TRUE(a != b);
        EXPECT_FALSE(a == b);
        
        bitset d(b);
        EXPECT_TRUE(b == d);
        EXPECT_FALSE(b != d);
        EXPECT_TRUE(b == b);
        EXPECT_FALSE(b != b);
    }
    
    
}