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
        * Method: createDataSource
        * ------------------------
        * Description: Creates a dataSource instance
        * @return datasource object
        */
        virtual IDataSourceStrategy<T,K>* createDataSource() = 0;

        /**
        * Method: createDataSourceInfo
        * ----------------------------
        * Description: Creates a dataSourceInfo instance
        * @return datasourceInfo object
        */
        virtual IDataSourceInfo<K>* createDataSourceInfo(K* info) = 0;
    };
}

#endif