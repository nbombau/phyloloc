#ifndef NEWICK_WRITER_H
#define NEWICK_WRITER_H

#include <iostream>
#include <fstream>
#include "Domain/ITree.h"
#include "Domain/ListIterator.h"



template <class T>
class NewickWriter
{
public:

    void saveNewickFile(const std::string& fname, const Domain::ITreeCollection<T>& trees)
    {
        std::ofstream os(fname.c_str());

        typename TreeCollection::iterator iter = trees.getIterator();
        for (; !iter.end(); iter.next())
        {
            Domain::ITree<T>* tree = iter.get();
            saveTree(tree->getRoot(), os);
            os << ";\n";
        }
    }

private:

    typedef Domain::ITreeCollection<T> TreeCollection;

    static void saveTree(const T* node, std::ostream& os)
    {

        if (!node->isLeaf())
        {
            os << '(';
            Domain::ListIterator<T, Domain::Node> iter = node->template getChildrenIterator<T>();

            //the first node does not have to be preceded by ','
            if (!iter.end())
            {
                saveTree(iter.get(), os);
                iter.next();
            }

            for (; !iter.end(); iter.next())
            {
                os << ',';
                saveTree(iter.get(), os);
            }
            os << ')';

        }
        os << node->getName() << ':' << node->getBranchLength();
    }
};

#endif
