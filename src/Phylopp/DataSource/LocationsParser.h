#ifndef LOCATIONS_PARSER_H
#define LOCATIONS_PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include <mili/mili.h>
#include "Domain/INode.h"
#include "Domain/LocationAspect.h"

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

    void loadLocationsFile(const std::string& fname)
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

            addLocation(name, location);

            values.clear();
            currentLineNumber++;
        }
    }

private:

    void addLocation(const Domain::NodeName nodeName, const Location& location)
    {
        LocationAspect<Domain::Node>::addLocation(location, nodeName);
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
