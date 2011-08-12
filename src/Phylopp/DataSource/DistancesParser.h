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

typedef GenericException<DistancesFileExceptionHierarchy> DistancesFileException;


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

    void loadDistancesFile(const std::string& fname, Locations::LocationManager& locationManager)
    {
        std::ifstream f(fname.c_str());

        if (!f)
            throw DistancesFileNotFound();

        currentLineNumber = 1;

        std::vector<std::string> values;

        while (f >> Separator(values, ','))
        {
            if (values.size() != 3)
                throw MalformedDistancesFile(getLineNumberText());

            Location location1 = trim(values[0]);
            Location location2 = trim(values[1]);

            float distance;
            if (!from_string(values[2], distance))
                throw MalformedDistancesFile(getLineNumberText());

            addDistance(distance, location1, location2, locationManager);

            values.clear();

            currentLineNumber++;
        }
    }

private:

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
