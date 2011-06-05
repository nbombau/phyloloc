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
#include "Parser/newick_file.h"

using namespace std;

namespace DataSource
{

template <class T>
class FileDataSource : public IDataSourceStrategy<T, FilesInfo>
{

public:
     /**
     * Class: MalformedFile
     * --------------------
     * Description: Exception used when the file input its not correctly formed.
     * Example: when a node has no locations associated.
     */
    class MalformedFile : public exception 
    {
        virtual const char* what() const throw()
        {
            return "Error when parsing the input data file";
        }
    };

     /**
     * Class: DataFileNotFound
     * --------------------
     * Description: Exception used when the input file is missing.
     */   
    class DataFileNotFound : public exception 
    { 
        virtual const char* what() const throw()
        {
            return "The input data file does not exists";
        }
    };  

     /**
     * Method: load
     * --------------------
     * Description: Load multiples tree structures from a text file 
     * an associate each node with a location.
     */
    void load(FilesInfo& info, Domain::ITreeCollection<T>& trees)
    {
        VariantsSet set;
        loadData(info.getLocationsFilePath(), set);
        NewickParser<T> newick;
        newick.loadNewickFile(info.getTreesFilePath(), trees, set);
    }

     /**
     * Method: save
     * --------------------
     * Description: Saves multiples tree structures to the file system.
     */
    void save(Domain::ITreeCollection<T>& trees, FilesInfo& info)
    {
        NewickParser<T> newick;
        newick.saveNewickFile(info.getTreesFilePath(), trees);
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
                if (values.size() == 1)
                {
                    throw MalformedFile();
                }
                else if (values.size() > 1)
                {
                    vector<string>::const_iterator it = values.begin();
                    string name = trim(*it);

                    string ss;
                    for(++it; it != values.end(); ++it)
                        ss += *it;

                    set.insert(name, ss);
                    values.clear();
                }
            }
        }
        else
        {
            throw DataFileNotFound();
        }
        return;
    }

}; // End of class FileDataSource

} // End of namespace DataSource

#endif
