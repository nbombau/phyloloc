#ifndef IDATASOURCESTRATEGY_H
#define IDATASOURCESTRATEGY_H

#include "../../Domain/ITree.h"
#include "../../Domain/ITreeCollection.h"
#include "../../Domain/INode.h"
#include "IDataSourceInfo.h"

namespace DataSource
{
    using namespace Domain;

    /**
    * Interface: IDataSourceStrategy
    * ----------------------
    * Description: Interface that allows the client to load or save
    * trees from and to a particular datasource
    * Type Parameter T: T is the underlying node class 
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
        * @return loaded tree collection
        */
        virtual ITreeCollection<T>* load(IDataSourceInfo<K>* info) = 0;

        /**
        * Method: load
        * ---------------
        * Description: Loads a tree collection to a particular data source
        * @param trees treeCollection to be saved
        * @param info information to access the datasource
        */
        virtual void save(ITreeCollection<T>* trees, IDataSourceInfo<K>* info) = 0;
    };
}

#endif