#ifndef NEWICK_WRITER_H
#define NEWICK_WRITER_H

#include <iostream>
#include <fstream>
#include "Domain/ITree.h"
#include "Domain/ListIterator.h"

typedef std::string NodeName;

template <class T>
class NewickWriter
{
public:

    void saveNewickFile(const std::string& fname, const Domain::ITreeCollection<T>& trees)
    {
        Domain::ListIterator< Domain::ITree<T> >* iter = trees.getIterator();

        std::ofstream os(fname.c_str());

        while (!iter->end())
        {
            Domain::ITree<T>* tree = iter->get();
            saveTree(tree->getRoot(), os);
            os << ";\n";
            iter->next();
        }
        delete iter;
    }

private:

    static void saveTree(const T* node, std::ostream& os)
    {

        if (!node->isLeaf())
        {
            os << '(';
            Domain::ListIterator<T>* iter = node->getChildrenIterator();

            while (!iter->end())
            {
                saveTree(iter->get(), os);

                iter->next();

                if (!iter->end())
                {
                    os << ',';
                }
            }
            delete iter;
            os << ')';

        }
        os << node->getName() << ':' << node->getBranchLength();
    }
};

#endif
