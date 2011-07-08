#ifndef LOCATION_H
#define LOCATION_H

#include <vector>
#include <mili/mili.h>
#include "INode.h"

namespace Locations
{
using namespace Domain;

static const unsigned int LOCATION_NOT_FOUND = 0;

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
                               "The location is not defined");

template <class T>
class LocationAspect : public T
{
public:

    static void clear()
    {
        locationManager.clear();
    }

    /**
     * Method: addLocation
     * ----------------------
     * Description: Add a new location and node mapping
     */
    static void addLocation(const Location& location, const NodeName& nodeName)
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
        const Location& locationTo)
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

            for (unsigned int i = 0; i < locationsDistances.size(); i++)
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
        void addLocation(const Location& location, const NodeName& name)
        {
            const LocationId id = getLocationId(location);

            size_t generatedId = (id == LOCATION_NOT_FOUND) ? getLocationsCount() + 1 : id;
            //consistent if location already exists

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

            bool ret = nodeLocationSet.get_element<Location>(name, location, std::nothrow);

            if (!ret)
                location.clear();

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
            const Location& locationTo)
        {
            const LocationId idFrom = getLocationId(locationFrom);
            const LocationId idTo = getLocationId(locationTo);

            checkLocations(idFrom, idTo);

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
            const LocationAspect<T>* nodeTo) const
        {
            LocationId idFrom = getLocationId(nodeFrom);
            LocationId idTo = getLocationId(nodeTo);

            //TODO: Check if locationsDistances is initialized
            checkLocations(idFrom, idTo);

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
                id = LOCATION_NOT_FOUND;
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
        LocationId getNameLocationId(const NodeName& name) const
        {
            Location location = getLocation(name);
            return getLocationId(location);
        }

        /**
         * Method: getLocationsCount
         * ----------------------
         * Returns: The number of locations stored
         */
        size_t getLocationsCount() const
        {
            return locationIdSet.size();
        }
    protected:
        bool isValid() const
        {
            return validateNodes() && validateDistances();
        }
    private:

        VariantsSet nodeLocationSet;
        VariantsSet locationIdSet;
        std::vector<std::vector<Distance> > locationsDistances;
        DistanceVector dispersionVector;

        static void checkLocations(const LocationId idFrom, const LocationId idTo)
        {
            if (idFrom == LOCATION_NOT_FOUND || idTo == LOCATION_NOT_FOUND)
            {
                throw InvalidLocation();
            }
        }

        //check that every node != "" has a location
        bool validateNodes() const
        {
            bool valid = true;

            VariantsSet::iterator it = nodeLocationSet.begin();

            while (valid && it != nodeLocationSet.end())
            {
                valid = implies(!it->first.empty(), !it->second.empty());

                it++;
            }
            return valid;
        }

        //check thay every location has a distance to every location
        bool validateDistances() const
        {
            bool valid = true;

            size_t locationsCount = getLocationsCount();

            unsigned int i = 0;
            while (valid && i < locationsCount)
            {
                unsigned int j = 0;
                while (valid && j < locationsCount)
                {
                    valid = implies(i != j, locationsDistances[i][j] != 0.0f);
                    j++;
                }
                i++;
            }
            return valid;
        }

        /**
         * Method: InitializeDistancesMatrix
         * ----------------------
         * Description: Reserve locations in the matrix
         */
        void initializeDistancesMatrix(size_t locationsCount)
        {
            locationsDistances.resize(locationsCount);
            for (unsigned int i = 0; i < locationsCount; i++)
            {
                locationsDistances[i].resize(locationsCount, 0);
            }
        }

        /**
         * Method: CalculateDispersionVector
         * ----------------------
         * Description: calculates de vector of dispersion factors
         */
        void calculateDispersionVector()
        {
            size_t locationsCount = getLocationsCount();

            if (locationsCount > 0)
            {
                dispersionVector.clear();
                dispersionVector.resize(locationsCount, 0);
                Distance distancesSum = 0.0f;

                for (unsigned int i = 0; i < locationsCount; i++)
                {
                    Distance locationDistancesSum = 0.0f;

                    for (unsigned int j = 0; j < locationsCount; j++)
                    {
                        locationDistancesSum += locationsDistances[i][j];
                    }
                    dispersionVector[i] = locationDistancesSum / Distance(locationsCount);
                    distancesSum += locationDistancesSum;
                }

                //As we added the whole distance matrix, to get the average distance
                // we must divide by twice the locationsCount, because the matrix
                //is assymetrical, so we are summing each distance twice.
                const Distance distancesAverage = distancesSum / (2.0f * Distance(locationsCount));
                for (unsigned int i = 0; i < locationsCount; i++)
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
