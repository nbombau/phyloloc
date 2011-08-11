
#include <gtest/gtest.h>

#include "../../src/Domain/LocationAspect.h"

namespace {

    using namespace Locations;
    using ::testing::Test;
    typedef std::string NodeName;

    typedef LocationAspect<Domain::Node> TestNode;
    typedef std::string NodeName;
    
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
        LocationManager locationManager;

        Location location1 = "Bs As";
        NodeName name1 = "B";
        Location location2 = "Santa Fe";
        NodeName name2 = "S";
        Location location3 = "Cordoba";
        NodeName name3 = "C";
        Location location4 = "Mendoza";
        NodeName name4 = "M";

        locationManager.addLocation(location1, name1);
        locationManager.addLocation(location2, name2);
        locationManager.addLocation(location3, name3);
        locationManager.addLocation(location4, name4);
      
        Location locationTest1 = locationManager.getLocation(name1);
        EXPECT_TRUE(locationTest1.compare(location1) == 0);
        Location locationTest2 = locationManager.getLocation(name2);
        EXPECT_TRUE(locationTest2.compare(location2) == 0);
        Location locationTest3 = locationManager.getLocation(name3);
        EXPECT_TRUE(locationTest3.compare(location3) == 0);
        Location locationTest4 = locationManager.getLocation(name4);
        EXPECT_TRUE(locationTest4.compare(location4) == 0);        
    }
    
    // Check distances setting
    TEST_F(LocationAspectTest, DistancesTest) 
    {
        LocationManager locationManager;        

        Location location1 = "Bs As";
        NodeName name1 = "B";
        Location location2 = "Santa Fe";
        NodeName name2 = "S";
        Location location3 = "Cordoba";
        NodeName name3 = "C";
        Location location4 = "Mendoza";
        NodeName name4 = "M";

        locationManager.addLocation(location1, name1);
        locationManager.addLocation(location2, name2);
        locationManager.addLocation(location3, name3);
        locationManager.addLocation(location4, name4);
        
        locationManager.addDistance(10, location1, location2);
        locationManager.addDistance(5, location2, location1);
        locationManager.addDistance(20, location3, location4);

        TestNode nodeB;
        nodeB.setName(name1);
        nodeB.setLocationId(locationManager.getNameLocationId(name1));
        TestNode nodeS;
        nodeS.setName(name2);
        nodeS.setLocationId(locationManager.getNameLocationId(name2));
        TestNode nodeC;
        nodeC.setName(name3);
        nodeC.setLocationId(locationManager.getNameLocationId(name3));
        TestNode nodeM;
        nodeM.setName(name4);
        nodeM.setLocationId(locationManager.getNameLocationId(name4));

        //EXPECT_TRUE(nodeB.distanceTo(&nodeS) == 10);
        //EXPECT_TRUE(nodeS.distanceTo(&nodeB) == 5);
        //EXPECT_TRUE(nodeC.distanceTo(&nodeM) == 5);
    }   
}
