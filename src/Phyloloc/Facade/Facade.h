#ifndef FACADE_H
#define FACADE_H

#include "../../Domain/INode.h"
#include "../../Domain/ITree.h"
#include "../../Domain/ITreeCollection.h"
//TODO: This references shall be replaced by the interface. The client
//shall specify which concrete class the factory method shall create.
#include "../../Phylopp/DataSource/FileDataSource.h"
#include "../../Phylopp/DataSource/FilesInfo.h"
#include "../../Phylopp/DataSource/ITreeCollection.h"


namespace PhylolocFacade
{
    template <class T, class V, class K>
    class Facade
    {
    public:

        void load(K& info,Domain::ITreeCollection<T>& trees)
        {
            dataSource.load(info, trees);
        }

        void save(Domain::ITreeCollection<T>& trees, K& info)
        {
            dataSource.save(trees, info);
        }

        void traverseDown(Domain::ITree<T>& t, V& v)
        {
            traverser.traverseDown(t, v);
        }

        void traverseDown(T& t, V& v)
        {
            traverser.traverseDown(t, v);
        }

        void traverseUp(T& t, V& v)
        {
            traverser.traverseDown(t, v);
        }

    private:
        Traversal::Traverser<T,V> traverser;
        //TODO: temporary. the datasource shall be created by IDataSourceFactory
        FileDataSource<T,K> dataSource;
    };
}

#endif