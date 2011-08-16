/*
NewickWriter: a class for saving trees in a file, in newick format

    Copyright (C) 2011 Emmanuel Teisaire, Nicolás Bombau, Carlos Castro, Damián Domé, FuDePAN

    This file is part of the Phyloloc project.

    Phyloloc is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Phyloloc is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Phyloloc.  If not, see <http://www.gnu.org/licenses/>.
*/


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

        for (typename TreeCollection::iterator iter = trees.getIterator(); !iter.end(); iter.next())
        {
            Domain::ITree<T>* tree = iter.get();
            saveTree(tree->getRoot(), os);
            os << ";\n";
        }
    }

private:

    typedef Domain::ITreeCollection<T> TreeCollection;
    typedef Domain::ListIterator<T, Domain::Node> NodeIterator;

    static void saveTree(const T* node, std::ostream& os)
    {

        if (!node->isLeaf())
        {
            os << '(';
            NodeIterator iter = node->template getChildrenIterator<T>();

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
