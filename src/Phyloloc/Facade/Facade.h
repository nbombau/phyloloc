/*
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

#ifndef FACADE_H
#define FACADE_H

#include "Domain/INode.h"
#include "Domain/ITree.h"
#include "Domain/ITreeCollection.h"
//TODO: This references shall be replaced by the interface. The client
//shall specify which concrete class the factory method shall create.
#include "Phylopp/DataSource/FileDataSource.h"
#include "Phylopp/DataSource/FilesInfo.h"
#include "Phylopp/Traversal/Traverser.h"
#include "Phylopp/Traversal/INodeVisitor.h"


namespace PhylolocFacade
{
template <class T, class V, class K>
class Facade
{
public:
    Facade()
    {}

    Facade(Traversal::Traverser<T, V>& t, DataSource::FileDataSource<T>& d) :
        traverser(t), 
        dataSource(d)
    {}

    void load(const K& info, Domain::ITreeCollection<T>& trees) const
    {
        dataSource.load(info, trees);
    }

    void save(Domain::ITreeCollection<T>& trees, const K& info) const
    {
        dataSource.save(trees, info);
    }

    void traverseDown(Domain::ITree<T>& t, V& v) const
    {
        traverser.traverseDown(t, v);
    }

    void traverseDown(T& t, V& v) const
    {
        traverser.traverseDown(t, v);
    }

    void traverseUp(T& t, V& v) const
    {
        traverser.traverseDown(t, v);
    }

private:
    Traversal::Traverser<T, V> traverser;
    //TODO: temporary. the datasource shall be created by IDataSourceFactory
    DataSource::FileDataSource<T> dataSource;

};
}

#endif
