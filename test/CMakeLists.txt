cmake_minimum_required(VERSION 2.8)

set(test_src TestMain.cpp 
             Domain/INodeTest.cpp 
             Domain/ListIteratorTest.cpp 
             Domain/ITreeTest.cpp
             Domain/ITreeCollectionTest.cpp
             Traverser/TraverserTest.cpp
             DataSource/FileDataSourceTest.cpp
)

INCLUDE_DIRECTORIES(../src)

add_executable(tests ${test_src})
target_link_libraries (tests gtest_main pthread gmock)

