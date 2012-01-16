/*
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

#ifndef STRICT_CONSENSOR_H
#define STRICT_CONSENSOR_H

#include <mili/mili.h>
#include "ClusterTree.h"

class StrictConsensorExceptionHierarchy {};
typedef mili::GenericException<StrictConsensorExceptionHierarchy> StrictConsensorException;


/**
* StrictConsensorException
* ------------------------
* Description: Exception thrown when no trees exist for consensus
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(EmptyTreeCollectionException,
                               StrictConsensorExceptionHierarchy,
                               "No trees were supplied");


namespace Consensus
{
template <class Node2, class Observer>
class StrictConsensor
{
public:

    Domain::ITree<Node2> *consensus(Domain::ITreeCollection<Node2>& trees,
                                    Observer& observer,
                                    Locations::LocationManager& locManager)
    {
        unsigned int i = 0;
        observer.onStart(trees);
        Domain::ListIterator<Domain::ITree<Node2> > it = trees.getIterator();

        if (it.count() == 0)
            throw EmptyTreeCollectionException();

        ClusterTree<Node2, Observer> first(trees.elementAt(i), observer, locManager);

        ClusterTree<Node2, Observer> consensusCluster(first, observer, locManager);

        if (it.count() > 1)
        {
            it.next();
            i++;
            for (; i < it.count() && !it.end(); ++i, it.next())
            {
                ClusterTree<Node2, Observer> current(trees.elementAt(i), observer, locManager);
                consensusCluster.intersectWith(current);
            }
        }

        Domain::ITree<Node2> * consensedTree = consensusCluster.toTree();
        observer.onEnd(consensedTree);

        return consensedTree;
    }
};

}


#endif
