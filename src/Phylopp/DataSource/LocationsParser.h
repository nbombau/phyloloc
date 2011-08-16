/*
LocationsParser: a class for parsing locations from a file

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


#ifndef LOCATIONS_PARSER_H
#define LOCATIONS_PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include <mili/mili.h>
#include "Domain/INode.h"
#include "Domain/LocationManager.h"

using namespace Locations;

class DataFileExceptionHierarchy {};

typedef GenericException<DataFileExceptionHierarchy> DataFileException;

/**
* MalformedFile
* --------------------
* Description: Exception used when the file input its not correctly formed.
* Example: when a node has no locations associated.
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(MalformedFile,
                               DataFileExceptionHierarchy,
                               "Error when parsing the input data file");

/**
* DataFileNotFound
* --------------------
* Description: Exception used when the input file is missing.
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(DataFileNotFound,
                               DataFileExceptionHierarchy,
                               "The input data file does not exist.");

class LocationsParser
{
public:

    void loadLocationsFile(const std::string& fname, Locations::LocationManager& locationManager)
    {
        std::ifstream f(fname.c_str());

        if (!f)
            throw DataFileNotFound();

        currentLineNumber = 1;

        std::vector<std::string> values;

        while (f >> Separator(values, ','))
        {
            if (values.size() != 2)
                throw MalformedFile(getLineNumberText());

            Domain::NodeName name = trim(values[0]);
            Location location = trim(values[1]);

            addLocation(name, location, locationManager);

            values.clear();
            currentLineNumber++;
        }
    }

private:

    void addLocation(const Domain::NodeName nodeName, const Location& location, Locations::LocationManager& locationManager)
    {
        locationManager.addLocation(location, nodeName);
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
