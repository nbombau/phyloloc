#ifndef FILEDATASOURCE_H
#define FILEDATASOURCE_H

#include "IDataSourceStrategy.h"
#include "FilesInfo.h"
#include "../../Domain/ITreeCollection.h"
#include "Parser/newick_file.h"

namespace DataSource
{

    template <class T>        
    class FileDataSource : public IDataSourceStrategy<T, FilesInfo>
    {
    public:
        void load(FilesInfo& info,Domain::ITreeCollection<T>& trees)
        { 
            BiRC::treelib::NewickParser<T> newick = BiRC::treelib::NewickParser<T>();
            newick.parse_newick_file(info.getTreesFilePath().c_str(),((Domain::ITree<T>*)trees.addTree()));
        }
        
        void save(Domain::ITreeCollection<T>& trees, FilesInfo& info)
        {
            
        }
    };
}

#endif