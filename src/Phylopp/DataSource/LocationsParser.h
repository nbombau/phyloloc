#ifndef LOCATIONS_PARSER_H
#define LOCATIONS_PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include <mili/mili.h>

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

    void loadLocationsFile(const std::string& fname,VariantsSet& set)
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

            const std::string name = trim(values[0]);
            const std::string location = trim(values[1]);

            set.insert(name, location);

            values.clear();

            currentLineNumber++;
        }
    }

private:

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
