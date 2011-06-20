
#include <gtest/gtest.h>

#include "../../src/Domain/LocationAspect.h"

namespace {

    using namespace Locations;
    using ::testing::Test;

    typedef LocationAspect<Domain::Node> TestNode;
    
    
    class LocationAspectTest : public Test 
    {
    protected:

        LocationAspectTest() { }

        virtual ~LocationAspectTest() { }

        virtual void SetUp() 
        {

        }

        virtual void TearDown() 
        {
        
        }        
    };

    // Check locations setting
    TEST_F(LocationAspectTest, LocationsTest) 
    {
        Location location1 = "Bs As";
        NodeName name1 = "B";
        Location location2 = "Santa Fe";
        NodeName name2 = "S";
        Location location3 = "Cordoba";
        NodeName name3 = "C";
        Location location4 = "Mendoza";
        NodeName name4 = "M";

        TestNode::addLocation(location1, name1);
        TestNode::addLocation(location2, name2);
        TestNode::addLocation(location3, name3);
        TestNode::addLocation(location4, name4);
       
        TestNode nodeB;
        nodeB.setName(name1);
        TestNode nodeS;
        nodeS.setName(name2);
        TestNode nodeC;
        nodeC.setName(name3);
        TestNode nodeM;
        nodeM.setName(name4);

        Location locationTest1 = nodeB.getLocation();
        EXPECT_TRUE(locationTest1.compare(location1) == 0);
        Location locationTest2 = nodeS.getLocation();
        EXPECT_TRUE(locationTest2.compare(location2) == 0);
        Location locationTest3 = nodeC.getLocation();
        EXPECT_TRUE(locationTest3.compare(location3) == 0);
        Location locationTest4 = nodeM.getLocation();
        EXPECT_TRUE(locationTest4.compare(location4) == 0);        
    }
    
    // Check distances setting
    TEST_F(LocationAspectTest, DistancesTest) 
    {
        Location location1 = "Bs As";
        NodeName name1 = "B";
        Location location2 = "Santa Fe";
        NodeName name2 = "S";
        Location location3 = "Cordoba";
        NodeName name3 = "C";
        Location location4 = "Mendoza";
        NodeName name4 = "M";

        TestNode::addLocation(location1, name1);
        TestNode::addLocation(location2, name2);
        TestNode::addLocation(location3, name3);
        TestNode::addLocation(location4, name4);
        
        TestNode::addDistance(10, location1, location2);
        TestNode::addDistance(5, location2, location1);
        TestNode::addDistance(20, location3, location4);

        TestNode nodeB;
        nodeB.setName(name1);
        TestNode nodeS;
        nodeS.setName(name2);
        TestNode nodeC;
        nodeC.setName(name3);
        TestNode nodeM;
        nodeM.setName(name4);

        //EXPECT_TRUE(nodeB.distanceTo(&nodeS) == 10);
        //EXPECT_TRUE(nodeS.distanceTo(&nodeB) == 5);
        //EXPECT_TRUE(nodeC.distanceTo(&nodeM) == 5);
    }   
}
