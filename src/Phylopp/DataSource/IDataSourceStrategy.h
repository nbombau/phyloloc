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
    * Method: load
    * ---------------
    * Description: Loads a tree collection from a particular data source
    * @param info information to access the datasource
    * @param allowMissingData true if nameless nodes are allowed
    * @return loaded tree collection
    */
    virtual void load(const K& info, Domain::ITreeCollection<T>& trees, Locations::LocationManager& locationManager, bool allowMissingData) = 0;

    /**
    * Method: load
    * ---------------
    * Description: Loads a tree collection to a particular data source
    * @param trees treeCollection to be saved
    * @param info information to access the datasource
    */
    virtual void save(const Domain::ITreeCollection<T>& trees, const K& info) = 0;
};
}

#endif
