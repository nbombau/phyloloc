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
#include "DistancesParser.h"
#include "LocationsParser.h"
#include "TreeValidationPolicies.h"

namespace DataSource
{

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
    void load(const FilesInfo& info, Domain::ITreeCollection<T>& trees, Locations::LocationManager& locationManager, bool allowMissingData)
    {
        try
        {
            LocationsParser locationsParser;
            locationsParser.loadLocationsFile(info.getLocationsFilePath(), locationManager);

            DistancesParser distancesParser;
            distancesParser.loadDistancesFile(info.getDistancesFilePath(), locationManager);
        }
        catch(const LocationException& ex)
        {
            trees.clear();
            locationManager.clear();
            throw;
        }
        catch (const DistancesFileException& ex)
        {
            trees.clear();
            locationManager.clear();
            throw;
        }
        catch (const DataFileException& ex)
        {
            trees.clear();
            locationManager.clear();
            throw;
        }

        try
        {
            if (allowMissingData)
            {
                //map nameless nodes, to the common ? location
                locationManager.addLocation("?", "");

                NewickParser<T> newickParser;
                newickParser.loadNewickFile(info.getTreesFilePath(), locationManager, trees);
            }
            else
            {
                NewickParser<T, ForbidMissinbgDataPolicy> newickParser;
                newickParser.loadNewickFile(info.getTreesFilePath(), locationManager, trees);
            }
        }
        catch (const TreeFileException& ex)
        {
            trees.clear();
            locationManager.clear();
            throw;
        }
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

}; // End of class FileDataSource

} // End of namespace DataSource

#endif
