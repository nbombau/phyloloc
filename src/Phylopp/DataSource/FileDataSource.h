#ifndef FILEDATASOURCE_H
#define FILEDATASOURCE_H

#include "IDataSourceStrategy.h"
#include "FilesInfo.h"
#include "../../Domain/ITreeCollection.h"
#include "../../Domain/ITree.h"
#include "../../Domain/ListIterator.h"
#include "Parser/newick_file.h"

namespace DataSource
{

    template <class T>        
    class FileDataSource : public IDataSourceStrategy<T, FilesInfo>
    {
    public:
        void load(FilesInfo& info,Domain::ITreeCollection<T>& trees)
        { 
            Parser::NewickParser<T> newick = Parser::NewickParser<T>();
            newick.loadNewickFile(info.getTreesFilePath(),trees.addTree());
        }
        
        void save(Domain::ITreeCollection<T>& trees, FilesInfo& info)
        {
            Parser::NewickParser<T> newick = Parser::NewickParser<T>();
            
            Domain::ListIterator< Domain::ITree<T> >* iter = trees.getIterator();
            
            while (!iter->end())
            {
                Domain::ITree<T> tree = iter->get();
                newick.saveNewickFile(info.getTreesFilePath(),&tree);                
                iter->next();
            }
            delete iter;
        }
    };
}

#endif