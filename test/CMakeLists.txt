cmake_minimum_required(VERSION 2.8)

set(test_src TestMain.cpp 
             Domain/INodeTest.cpp 
             Domain/ListIteratorTest.cpp 
             Domain/ITreeTest.cpp
             Domain/ITreeCollectionTest.cpp
             Domain/LocationAspectTest.cpp
             Traverser/TraverserTest.cpp
             DataSource/FileDataSourceTest.cpp
             Propagator/VectorHelperTest.cpp
             Propagator/PropagatorAspectTest.cpp
             Propagator/PropagatorTest.cpp
	     Consensor/ClusterTreeTest.cpp
             ../src/Phylopp/Consensor/bitset.cpp
             Propagator/StatisticCollectorTest.cpp
            Consensor/bitsetTest.cpp
)

INCLUDE_DIRECTORIES(../src)

add_executable(tests ${test_src})

add_definitions(-fprofile-arcs -ftest-coverage)

target_link_libraries (tests gtest_main pthread gmock -fprofile-arcs)

