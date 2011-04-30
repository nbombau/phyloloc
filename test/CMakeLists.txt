set(test_src TestMain.cpp 
             Domain/INodeTest.cpp 
             Domain/ListIteratorTest.cpp 
             Domain/ITreeTest.cpp
             Domain/ITreeCollectionTest.cpp
             Traverser/TraverserTest.cpp
)

add_executable(tests ${test_src})
target_link_libraries (tests gtest_main pthread gmock)

