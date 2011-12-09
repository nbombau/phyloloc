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
