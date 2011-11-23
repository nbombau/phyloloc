/*
IDataSourceStrategy: Interface for loading and saving trees from and to a particular
DataSource
              
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


#ifndef IDATASOURCESTRATEGY_H
#define IDATASOURCESTRATEGY_H

#include "Domain/ITree.h"
#include "Domain/ITreeCollection.h"
#include "Domain/INode.h"
#include "IDataSourceInfo.h"
#include "Domain/LocationManager.h"

namespace DataSource
{
/**
* Interface: IDataSourceStrategy
* ----------------------
* Description: Interface that allows the client to load or save
* trees from and to a particular datasource
* Type Parameter T: T is the underlying node class
* Type Parameter K: K is the class that provides info about how
* to access data from the datasouce, for instance if the datasource is
* a database, K shall provide server address, credentials, etc.
*/
template <class T, class K>
class IDataSourceStrategy
{
public:
    /**
    * Loads a tree collection from a particular data source
    * @param info information to access the datasource
    * @param trees treeCollection to be filled
    * @param locationManager Manager of locations and distances between locations
    * @param allowMissingData true if nameless nodes are allowed
    */
    virtual void load(const K& info, Domain::ITreeCollection<T>& trees, Locations::LocationManager& locationManager, bool allowMissingData) = 0;

    /**
    * Loads a tree collection to a particular data source
    * @param trees treeCollection to be saved
    * @param info information to access the datasource
    */
    virtual void save(const Domain::ITreeCollection<T>& trees, const K& info) = 0;
};
}

#endif
