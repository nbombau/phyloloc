/*
    IDataSourceFactory: class for creating dataSource objects

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


#ifndef IDATASOURCE_H
#define IDATASOURCE_H

#include "IDataSourceInfo.h"
#include "IDataSourceStrategy.h"


namespace DataSource
{
/**
* Interface: IDataSourceFactory
* -----------------------------
* Description: Interface for data source factories.
* Type Parameter T: T is the underlying node class
* Type Parameter K: K is the dataSourceInfo underlying class,
* that shall hold information enough to access a data source
*/
template <class T, class K>
class IDataSourceFactory
{
public:
    /**
    * Creates a dataSource instance
    * @return datasource object
    */
    virtual IDataSourceStrategy<T, K>* createDataSource() = 0;
};
}

#endif
