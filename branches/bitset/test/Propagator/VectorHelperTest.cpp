
#include <gtest/gtest.h>
#include <gmock/gmock.h> 
#include "../../src/Phyloloc/Propagator/VectorHelper.h"


namespace {
    
    using namespace Propagation;
    using ::testing::Test;
       
    class VectorHelperTest : public Test 
    {
    protected:

        VectorHelperTest() { }
        
        virtual ~VectorHelperTest() { }
        
        
        virtual void SetUp() 
        {
            
        }
        
        virtual void TearDown() 
        {
            
        }        
    };
    
    

    TEST_F(VectorHelperTest, vectorialOperationTest) 
    {        
        std::vector<int> vec1;
        std::vector<int> vec2;
        
        vec1.push_back(1);
        vec1.push_back(2);
        vec1.push_back(3);
        
        vec2.push_back(4);
        vec2.push_back(5);
        vec2.push_back(6);
        
        std::vector<int> r(3,0);
        
        VectorHelper::vectorialOperation<int, std::plus<int> >(vec1, vec2, r);
        
        ASSERT_TRUE(r[0] == 5);
        ASSERT_TRUE(r[1] == 7);
        ASSERT_TRUE(r[2] == 9);
        
    }
    
    TEST_F(VectorHelperTest, scalarOperationTest) 
    {        
        const float epsilon = 0.001f;
        std::vector<float> vec1;
        std::vector<float> vec2;
        
        vec1.push_back(1.0f);
        vec1.push_back(2.0f);
        vec1.push_back(3.0f);
        
       
        VectorHelper::scalarOperation<float, std::multiplies<float> >(vec1, 2.0f);
        ASSERT_TRUE(abs(vec1[0] - 2.0f) < epsilon);
        ASSERT_TRUE(abs(vec1[1] - 4.0f) < epsilon);
        ASSERT_TRUE(abs(vec1[2] - 6.0f) < epsilon);
        

        VectorHelper::scalarOperation<float, std::multiplies<float> >(vec1, 0.5f);
        
        ASSERT_TRUE(abs(vec1[0] - 1.0f) < epsilon);
        ASSERT_TRUE(abs(vec1[1] - 2.0f) < epsilon);
        ASSERT_TRUE(abs(vec1[2] - 3.0f) < epsilon);
    }
}
