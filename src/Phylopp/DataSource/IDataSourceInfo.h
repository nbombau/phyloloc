#ifndef IDATASOURCEINFO_H
#define IDATASOURCEINFO_H

namespace DataSource
{
/**
* Interface: IDataSourceInfo
* ----------------------
* Description: Class that holds information about a particular datasource.
* The information it helds should be enough to access the datasource.
* Type Parameter K: K is the type where the info is held
*/
template <class K>
class IDataSourceInfo
{
public:

    virtual K* getInfo() = 0;
};
}

#endif