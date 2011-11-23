cmake_minimum_required(VERSION 2.8)

set(test_src TestMain.cpp 
             bitsetTest.cpp
            ../src/bitset.cpp
)





add_executable(tests ${test_src})
target_link_libraries (tests gtest_main pthread)
