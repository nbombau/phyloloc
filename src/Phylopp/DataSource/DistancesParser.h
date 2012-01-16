/*
    DistancesParser: A parser for loading location distances from a file

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


#ifndef DISTANCES_PARSER_H
#define DISTANCES_PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include <mili/mili.h>
#include "Domain/INode.h"
#include "Domain/LocationManager.h"

using namespace Locations;

class DistancesFileExceptionHierarchy {};

typedef mili::GenericException<DistancesFileExceptionHierarchy> DistancesFileException;


/**
* DistancesFileNotFound
* --------------------
* Description: Exception used when the input file is missing.
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(DistancesFileNotFound,
                               DistancesFileExceptionHierarchy,
                               "The input distances file does not exist.");

/**
* MalformedDistancesFile
* --------------------
* Description: Exception used when the input file is not correctly formed.
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(MalformedDistancesFile,
                               DistancesFileExceptionHierarchy,
                               "The input is not correctly formed");

class DistancesParser
{
public:

    /**
     * Loads distences information from a file
     *
     * @param fname File name
     * @param locationManager Manager of locations and distances between locations
     */
    void loadDistancesFile(const std::string& fname, Locations::LocationManager& locationManager)
    {
        std::ifstream f(fname.c_str());

        if (!f)
            throw DistancesFileNotFound();

        currentLineNumber = 1;

        std::vector<std::string> values;

        while (f >> mili::Separator(values, ','))
        {
            if (values.size() != 3)
                throw MalformedDistancesFile(getLineNumberText());

            Location location1 = mili::trim(values[0]);
            Location location2 = mili::trim(values[1]);

            float distance;
            if (!mili::from_string(values[2], distance))
                throw MalformedDistancesFile(getLineNumberText());

            addDistance(distance, location1, location2, locationManager);

            values.clear();

            currentLineNumber++;
        }
    }

private:

    /**
     * Adds to the location manager the distance between location1 and location2
     *
     * @param distance Distance between locations
     * @param location1 First location
     * @param location2 Second location
     * @param locationManager Manager of locations and distances between locations
     */
    void addDistance(const float distance, const Location& location1, const Location& location2, Locations::LocationManager& locationManager)
    {
        try
        {
            locationManager.addDistance(distance, location1, location2);
        }
        catch (const InvalidLocation& ex)
        {
            throw InvalidLocation(getLineNumberText());
        }
    }

    /****************************************************
     ** This variable and method will no longer be
     ** needed when mili generic exceptions is updated.
     *********       mili issue 35              ********/

    unsigned int currentLineNumber;

    std::string getLineNumberText() const
    {
        std:: stringstream s;
        s << "Line: " << currentLineNumber;
        return s.str();
    }
    /****************************************************/

};

#endif
