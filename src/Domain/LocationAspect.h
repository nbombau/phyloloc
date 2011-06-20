#ifndef LOCATION_H
#define LOCATION_H

#include <vector>
#include <mili/mili.h>
#include "INode.h"

namespace Locations
{
    using namespace Domain;
    
    class LocationExceptionHierarchy {};

    typedef GenericException<LocationExceptionHierarchy> LocationException;     
    typedef float Distance;
    typedef std::vector<Distance> DistanceVector;
    typedef std::string Location;
    typedef unsigned int LocationId;

    /**
    * InvalidNodeName
    * --------------------
    * Description: Exception when it not exists a node with a node name passed
    * as a parameter.
    */
    DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidNodeName,
                                   LocationExceptionHierarchy,
                                   "The node name is not valid for any node");

    /**
    * InvalidLocation
    * --------------------
    * Description: Exception used a location passed as parameter was not 
    * previously initilized as an existing location.
    */
    DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidLocation,
                                   LocationExceptionHierarchy,
                                   "The location its not defined");

    template <class T>
    class LocationAspect : public T
    {
    public:        

        static void Clear()
        {
            locationManager.clear();
        }            

        /**
         * Method: addLocation
         * ----------------------
         * Description: Add a new location and node mapping
         */
        static void addLocation( const Location& location, const NodeName& nodeName )
        {
            locationManager.addLocation(location, nodeName);                      
        }
        
        /**
         * Method: addDistances
         * ----------------------
         * Description: Add a new distance from one location to another
         * The distance is not bidirectional
         */
        static void addDistance( 
        const Distance distance, 
        const Location& locationFrom, 
        const Location& locationTo )
        {
            locationManager.addDistance(distance, locationFrom, locationTo);        
        }
        
        /**
         * Method: getDispersionVector
         * ----------------------
         * Returns: The dispersion vector of the locations
         * holded by locationManager
         */
        static const DistanceVector& getDispersionVector()
        {
            return locationManager.getDispersionVector();
        }
        
        /**
         * Method: getLocation
         * ---------------
         * Description: Gets the location associated to the node
         * @return the node's location
         */
        Location getLocation() const
        {             
            NodeName name = this->getName();
            return locationManager.getLocation(name);
        }
        
        /**
         * Method: distanceTo
         * ----------------------
         * Returns: The distance to a node
         */
        Distance distanceTo(const LocationAspect<T>* node) const
        {
            return locationManager.distance(this, node);                      
        }  
        
    protected:
        /**
         * Class: LocationManager
         * ----------------------
         * Description: Class that contains data structures associated with
         * locations and distances
         */                  
        class LocationManager
        {
            
        public:
            
            void clear()
            {
                nodeLocationSet.clear();
                locationIdSet.clear();               
                for(unsigned int i = 0; i < locationsDistances.size(); i++) 
                {
                    locationsDistances[i].clear();
                }   
                locationsDistances.clear();
            }

            /**
             * Method: addLocation
             * ----------------------
             * Description: Add a new location and node mapping
             */
            void addLocation(const Location& location, const NodeName& name )
            {
                size_t generatedId = getLocationsCount() + 1;
                nodeLocationSet.insert(name, location);                
                locationIdSet.insert(location, generatedId);
            }
            
            /**
             * Method: getLocation
             * ----------------------
             * Returns: The location of the node or empty if no location
             * is set for that node
             */
            Location getLocation(const NodeName& name) const
            { 
                Location location; 
                try
                {
                    location = nodeLocationSet.get_element<Location>(name);
                }
                catch(const BadElementName&)
                {
                    location = "";
                }
                return location;
            }                
            
            /**
             * Method: addDistance
             * ----------------------
             * Description: Add a new distance from one location to another
             * The distance is not bidirectional
             */
            void addDistance( 
            const Distance distance, 
            const Location& locationFrom, 
            const Location& locationTo )
            {
                LocationId idFrom = getLocationId(locationFrom);
                LocationId idTo = getLocationId(locationTo);
                
                if (idFrom <= 0 || idTo <= 0)
                {
                    throw InvalidLocation();
                }                
                
                if (locationsDistances.empty())
                {
                    size_t locationsCount = getLocationsCount();
                    initializeDistancesMatrix(locationsCount);
                }                
                
                locationsDistances[idFrom - 1][idTo - 1] = distance;
            }
            
            /**
             * Method: distance
             * ----------------------
             * Returns: The distance from one node to another
             */
            Distance distance( 
            const LocationAspect<T>* nodeFrom, 
            const LocationAspect<T>* nodeTo ) const
            {
                LocationId idFrom = getLocationId(nodeFrom);
                LocationId idTo = getLocationId(nodeTo);
                
                //TODO: Check if locationsDistances is initialized
                if (idFrom <= 0 || idTo <= 0)
                {
                    throw InvalidNodeName();
                }
                
                return locationsDistances[idFrom - 1][idTo - 1];                                    
            }            
            
            /**
             * Method: getDispersionVector
             * ----------------------
             * Returns: The dispersion vector of the locations
             * holded by locationManager
             */
            const DistanceVector& getDispersionVector()
            {
                calculateDispersionVector();
                return dispersionVector;
            }
            
            //TODO: Make these private, first resolve propagator initialization
            /**
             * Method: getLocationId
             * ----------------------
             * Description: Look for the id mapped to a location
             * Returns: Cero if the id is not defined. 
             */
            LocationId getLocationId(const Location& location) const
            {
                LocationId id;
                try
                {
                    id = locationIdSet.get_element<LocationId>(location);
                }
                catch (const BadElementName&)
                {
                    id = 0;
                }
                return id;
            }
            
            /**
             * Method: getLocationId
             * ----------------------
             * Description: Look for the id mapped to a location
             * Returns: Cero if the id is not defined. 
             */
            LocationId getLocationId(const LocationAspect<T>* node) const
            {
                return getNameLocationId(node->getName());                
            }
            
            /**
             * Method: getLocationId
             * ----------------------
             * Description: Look for the id mapped to a location
             * Returns: Cero if the id is not defined. 
             */
            LocationId getNameLocationId(const NodeName& name)
            {
                Location location = getLocation(name);
                return getLocationId(location);
            }
            
            /**
             * Method: getLocationsCount
             * ----------------------
             * Returns: The number of locations stored
             */
            size_t getLocationsCount()
            {
                return nodeLocationSet.size();
            }
            
        private:
            
            VariantsSet nodeLocationSet;
            VariantsSet locationIdSet;
            std::vector<std::vector<Distance> > locationsDistances;
            DistanceVector dispersionVector;
            
            /**
             * Method: InitializeDistancesMatrix
             * ----------------------
             * Description: Reserve locations in the matrix
             */
            void initializeDistancesMatrix(size_t locationsNumber)
            {
                locationsDistances.resize(locationsNumber);                
                for(unsigned int i = 0; i < locationsNumber; i++) 
                {
                    locationsDistances[i].resize(locationsNumber, 0);
                } 
            }
            
            /**
             * Method: CalculateDispersionVector
             * ----------------------
             * Description: calculates de vector of dispersion factors
             */
            void calculateDispersionVector()
            {
                size_t locationsNumber = getLocationsCount();
                
                if(locationsNumber > 0)
                {
                    dispersionVector.clear();
                    dispersionVector.resize(locationsNumber, 0);
                    Distance distancesSum = 0.0f;
                    
                    for(unsigned int i = 0; i < locationsNumber; i++)
                    {
                        Distance locationDistancesSum = 0.0f;
                        
                        for(unsigned int j = 0; j < locationsNumber; j++)
                        {
                            locationDistancesSum += locationsDistances[i][j];
                        }
                        dispersionVector[i] = locationDistancesSum / Distance(locationsNumber);
                        distancesSum += locationDistancesSum;
                    }
                    
                    //As we added the whole distance matrix, to get the average distance
                    // we must divide by twice the locationsNumber, because the matrix
                    //is assymetrical, so we are summing each distance twice.
                    Distance distancesAverage = distancesSum / (2.0f * Distance(locationsNumber));
                    for(unsigned int i = 0; i < locationsNumber; i++)
                    {
                        Distance locationAverage = dispersionVector[i];
                        dispersionVector[i] = 1.0f - locationAverage / distancesAverage;
                    }
                }
            }

            
        }; // End of Class LocationManager

        // Used for identify locations and distances between locations 
        static LocationManager locationManager;
        
    };
    
    template <class T> typename 
    LocationAspect<T>::LocationManager LocationAspect<T>::locationManager;
    
} // End of Namespace Location

#endif
