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
#include "Domain/ListIterator.h"
#include "Domain/ITreeCollection.h"
#include "Phylopp/Traversal/NodeVisitor.h"
#include "Phylopp/Traversal/Traverser.h"

class StrictConsensorExceptionHierarchy {};
typedef mili::GenericException<StrictConsensorExceptionHierarchy> StrictConsensorException;


/**
* EmptyTreeCollectionException
* ------------------------
* Description: Exception thrown when no trees exist for consensus
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(EmptyTreeCollectionException,
                               StrictConsensorExceptionHierarchy,
                               "No trees were supplied");


/**
* DuplicateNameException
* ------------------------
* Description: Exception thrown when some of the trees have terminals with
* duplicate nodename. In that case, consensus is not possible.
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(DuplicateNameException,
                               StrictConsensorExceptionHierarchy,
                               "Can't generate consensus when trees have duplicate node names");

namespace Consensus
{

template <class T>
struct IsLeafPredicate
{
    bool operator()(T* node) const
    {
        return node->isLeaf();
    }
};

template <class Node>
class DuplicateNameAction
{
public:

    DuplicateNameAction() : hasDuplicateNames(false) {}

    VisitAction visitNode(Node* n)
    {
        VisitAction ret = ContinueTraversing;
        if (mili::contains(nodeNames, n->getName()))
        {
            ret = StopTraversing;
            hasDuplicateNames = true;
        }
        else
            nodeNames.insert(n->getName());

        return ret;
    }

    bool foundDuplicateName() const
    {
        return hasDuplicateNames;
    }

private:

    typedef std::set<Domain::NodeName> NodeNameSet;
    NodeNameSet nodeNames;
    bool hasDuplicateNames;
};

template <class Node2, class Observer>
class StrictConsensor
{
public:

    Domain::ITree<Node2>* consensus(Domain::ITreeCollection<Node2>& trees,
                                    Observer& observer,
                                    Locations::LocationManager& locManager)
    {
        unsigned int i = 0;
        observer.onStart(trees);
        Domain::ListIterator<Domain::ITree<Node2> > it = trees.getIterator();

        validateCollection(trees);

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

        Domain::ITree<Node2>* consensedTree = consensusCluster.toTree();
        observer.onEnd(consensedTree);

        return consensedTree;
    }

private:

    static void validateCollection(const Domain::ITreeCollection<Node2>& trees)
    {
        Domain::ListIterator<Domain::ITree<Node2> > treesIter = trees.getIterator();

        if (treesIter.count() == 0)
            throw EmptyTreeCollectionException();

        for (; !treesIter.end(); treesIter.next())
            validateTree(treesIter.get());
    }

    static void validateTree(Domain::ITree<Node2>* tree)
    {
        DuplicateNameAction<Node2> action;
        Traversal::Traverser<Node2, DuplicateNameAction<Node2>, IsLeafPredicate<Node2> > traverser;
        traverser.traversePostOrder(tree, action);

        if (action.foundDuplicateName())
            throw DuplicateNameException();
    }
};

}


#endif
