#ifndef FILEDATASOURCE_H
#define FILEDATASOURCE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <map>
#include <mili/mili.h>

#include "IDataSourceStrategy.h"
#include "FilesInfo.h"
#include "Domain/ITreeCollection.h"
#include "Domain/ITree.h"
#include "Domain/ListIterator.h"
#include "NewickParser.h"
#include "NewickWriter.h"

using namespace std;

namespace DataSource
{

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
                               "Error when parsing the input data file.");

/**
* DataFileNotFound
* --------------------
* Description: Exception used when the input file is missing.
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(DataFileNotFound,
                               DataFileExceptionHierarchy,
                               "The input data file does not exist.");


template <class T>
class FileDataSource : public IDataSourceStrategy<T, FilesInfo>
{
public:

    /**
    * Method: load
    * --------------------
    * Description: Load multiples tree structures from a text file
    * an associate each node with a location.
    */
    void load(const FilesInfo& info, Domain::ITreeCollection<T>& trees)
    {
        VariantsSet set;
        loadData(info.getLocationsFilePath(), set);
        NewickParser<T> newickParser;
        newickParser.loadNewickFile(info.getTreesFilePath(), trees, set);
    }

    /**
    * Method: save
    * --------------------
    * Description: Saves multiples tree structures to the file system.
    */
    void save(const Domain::ITreeCollection<T>& trees, const FilesInfo& info)
    {
        NewickWriter<T> newickWriter;
        newickWriter.saveNewickFile(info.getTreesFilePath(), trees);
    }

private:
    /**
     * Method: loadData
     * --------------------
     * Description: Loads a set of informations associated with
     * nodes into a map from a file.
     * @param file the name of the file to parse
     * @param bag a map with node names as keys and string as values
     */
    void loadData(const string& file, VariantsSet& set)
    {
        ifstream f(file.c_str());
        vector<string> values;

        if (f)
        {
            while (f >> Separator(values, ','))
            {
                if (values.size() <= 1)
                {
                    throw MalformedFile();
                }
                else
                {
                    vector<string>::const_iterator it = values.begin();
                    string name = trim(*it);

                    string location;
                    for (++it; it != values.end(); ++it)
                        location += *it;

                    if (location.empty())
                        throw MalformedFile();

                    set.insert(name, location);
                    values.clear();
                }
            }
        }
        else
        {
            throw DataFileNotFound();
        }
    }

}; // End of class FileDataSource

} // End of namespace DataSource

#endif
