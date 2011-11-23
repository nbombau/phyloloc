
#include <gtest/gtest.h>


namespace 
{
    int main(int argc, char **argv) 
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::GTEST_FLAG(throw_on_failure) = true;
        return RUN_ALL_TESTS();
    }   
}