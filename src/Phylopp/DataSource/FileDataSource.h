#ifndef FILEDATASOURCE_H
#define FILEDATASOURCE_H

#include "IDataSourceStrategy.h"
#include "FilesInfo.h"
#include "Parser/newick_file.hh"

namespace DataSource
{
    using namespace Parser;
    
    template <class T>        
    class FileDataSource : public IDataSourceStrategy<T, FilesInfo>
    {
    public:
        void load(FilesInfo& info,ITreeCollection<T>& trees)
        { 
            parse_newick_file(info.getTreesFilePath().c_str(),trees.addTree());
        }
        
        void save(ITreeCollection<T>* trees, FilesInfo& info)
        {
            
        }
    };
}

#endif