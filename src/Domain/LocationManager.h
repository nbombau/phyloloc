/*
Copyright (C) 2011 Emmanuel Teisaire, Nicolás Bombau, Carlos Castro, Damián Domé, FuDePAN

This file is part of the Phyloloc project.

Phyloloc is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Phyloloc is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Phyloloc.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef LOCATION_MANAGER_H
#define LOCATION_MANAGER_H

#include <vector>
#include <mili/mili.h>
#include "INode.h"
#include "ListIterator.h"

namespace Locations
{

static const unsigned int LOCATION_NOT_FOUND = 0;
static const unsigned int NODENAME_NOT_FOUND = 0;
static const unsigned int ID_INCREMENT = 1;

class LocationExceptionHierarchy {};

typedef mili::GenericException<LocationExceptionHierarchy> LocationException;
typedef float Distance;
typedef std::vector<Distance> DistanceVector;
typedef std::string Location;
typedef unsigned int LocationId;
typedef unsigned int NodeNameId;

/**
* InvalidLocation
* --------------------
* Description: Exception used a location passed as parameter was not
* previously initilized as an existing location.
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidLocation,
                               LocationExceptionHierarchy,
                               "The location is not defined");
/**
* Class: LocationManager
* ----------------------
* Description: Class that contains data structures associated with
* locations and distances
*/
class LocationManager
{

public:

    mili::VariantsSet::iterator getLocations()
    {
        return locationIdSet.begin();
    }

    void clear()
    {
        nodeLocationSet.clear();
        locationIdSet.clear();
        nodeNameIdSet.clear();

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
    void addLocation(const Location& location, const Domain::NodeName& name)
    {
        const LocationId id = getLocationId(location);
        const NodeNameId nameId = getNodeNameId(name);

        //TODO: generate Id in private method
        size_t generatedId = (id == LOCATION_NOT_FOUND) ? getLocationsCount() + ID_INCREMENT : id;
        size_t generatedNodeNameId = (nameId == NODENAME_NOT_FOUND) ? getNodeNameCount() + ID_INCREMENT : nameId;

        //consistent if location already exists
        nodeLocationSet.insert(name, location);
        locationIdSet.insert(location, generatedId);
        nodeNameIdSet.insert(name, generatedNodeNameId);
    }

    /**
    * Method: getLocation
    * ----------------------
    * Returns: The location of the node or empty if no location
    * is set for that node
    */
    Location getLocation(const Domain::NodeName& name) const
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

        const size_t locationsCount = getLocationsCount();

        if (locationsDistances.size() < locationsCount)
        {
            resizeDistancesMatrix(locationsCount);
        }
        //else not needed

        locationsDistances[idFrom - 1][idTo - 1] = distance;
    }

    /**
    * Method: distance
    * ----------------------
    * Returns: The distance from one node to another
    */
    Distance distance(
        const Domain::Node* nodeFrom,
        const Domain::Node* nodeTo) const
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

    /**
    * Method: getLocationId
    * ----------------------
    * Description: Look for the id mapped to a location
    * Returns: Zero if the id is not defined.
    */
    LocationId getLocationId(const Location& location) const
    {
        LocationId id;
        try
        {
            id = locationIdSet.get_element<LocationId>(location);
        }
        catch (const mili::BadElementName&)
        {
            id = LOCATION_NOT_FOUND;
        }
        return id;
    }

    /**
    * Method: getNodeNameId
    * ----------------------
    * Description: Look for the id mapped to a NodeName
    * Returns: Cero if the id is not defined.
    */
    NodeNameId getNodeNameId(const Domain::NodeName& name) const
    {
        NodeNameId id;
        try
        {
            id = nodeNameIdSet.get_element<NodeNameId>(name);
        }
        catch (const mili::BadElementName&)
        {
            id = NODENAME_NOT_FOUND;
        }
        return id;
    }

    /**
    * Method: getLocationId
    * ----------------------
    * Description: Look for the id mapped to a location
    * Returns: Cero if the id is not defined.
    */
    LocationId getLocationId(const Domain::Node* node) const
    {
        return getNameLocationId(node->getName());
    }

    /**
    * Method: getLocationId
    * ----------------------
    * Description: Look for the id mapped to a location
    * Returns: Cero if the id is not defined.
    */
    LocationId getNameLocationId(const Domain::NodeName& name) const
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

    /**
    * Method: getNodeNameCount
    * ----------------------
    * Returns: The number of node names stored
    */
    size_t getNodeNameCount() const
    {
        return nodeNameIdSet.size();
    }

    bool isValid() const
    {
        return validateNodes() && validateDistances();
    }

    /**
    * Check if this locationManager object is empty.
    *
    * @return true if it is empty, false otherwise
    */
    bool isEmpty() const
    {
        return nodeLocationSet.empty() && locationIdSet.empty() && locationsDistances.empty();
    }

private:

    mili::VariantsSet nodeLocationSet;
    mili::VariantsSet locationIdSet;
    mili::VariantsSet nodeNameIdSet;
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

        mili::VariantsSet::const_iterator it = nodeLocationSet.begin();

        while (valid && it != nodeLocationSet.end())
        {
            valid = mili::implies(!it->first.empty(), !it->second.empty());

            it++;
        }
        return valid;
    }

    //check thay every location has a distance to every location
    bool validateDistances() const
    {
        bool valid = true;

        const size_t locationsCount = getLocationsCount();

        unsigned int i = 0;
        while (valid && i < locationsCount)
        {
            unsigned int j = 0;
            while (valid && j < locationsCount)
            {
                valid = mili::implies(i != j, locationsDistances[i][j] != 0.0f);
                j++;
            }
            i++;
        }
        return valid;
    }

    /**
    * Method: resizeDistancesMatrix
    * ----------------------
    * Description: Reserve locations in the matrix
    */
    void resizeDistancesMatrix(size_t locationsCount)
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
        const size_t locationsCount = getLocationsCount();

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
                //the sum to all OTHER locations
                dispersionVector[i] = locationDistancesSum;
                //update the sum between all locations
                distancesSum += locationDistancesSum;
            }

            for (unsigned int i = 0; i < locationsCount; i++)
            {
                dispersionVector[i] = 1.0f - dispersionVector[i] / distancesSum;
            }
        }
    }
}; // End of Class LocationManager

} // End of Namespace Location

#endif
