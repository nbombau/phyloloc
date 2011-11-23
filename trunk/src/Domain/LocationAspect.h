#ifndef LOCATION_H
#define LOCATION_H

#include "LocationManager.h"

namespace Locations
{

template <class T>
class LocationAspect : public T
{
public:

    /**
     * Method: setLocationId
     * ---------------
     * Description: Sets the location id which identifies the location
     * associated to the node
     */
    void setLocationId(LocationId locationId)
    {
        this->locationId = locationId;
    }    
    
    /**
     * Method: getLocationId
     * ---------------
     * Description: Gets the location id which identifies the location
     * associated to the node
     * @return the node's location
     */
    LocationId getLocationId() const
    {
        return locationId;
    }

private:
    LocationId locationId;

};

} // End of Namespace Location

#endif
