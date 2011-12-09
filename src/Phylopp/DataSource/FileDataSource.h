/*
    FileDataSource: a class for loading trees, distances and locations from a file,
    and also for saving trees to a file.

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
    * Load multiples tree structures, along with location and distances from texts files
    *
    * @param info File paths information
    * @param trees Collection of trees to be filled
    * @param locationManager Manager of locations and distances between locations
    * @param allowMissingData Whether missing data in trees is allowed
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
        catch (const LocationException& ex)
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
    * Saves multiples tree structures to the file system.
    *
    * @param trees Trees to be saved
    * @param info File paths information
    */
    void save(const Domain::ITreeCollection<T>& trees, const FilesInfo& info)
    {
        NewickWriter<T> newickWriter;
        newickWriter.saveNewickFile(info.getTreesFilePath(), trees);
    }

}; // End of class FileDataSource

} // End of namespace DataSource

#endif
