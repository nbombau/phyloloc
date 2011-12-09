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

#ifndef TRAVERSER_H
#define TRAVERSER_H

#include <list>
#include <stdlib.h>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <queue>

#include "NodeVisitor.h"
#include "Domain/ITree.h"
#include "Domain/INode.h"
#include "Domain/ListIterator.h"

namespace Traversal
{

/**
* Class: Traverser
* ----------------
* Description: Allows the client to easily traverse a phylogenetic tree
* Type Parameter T: T is the node type.
* Type Parameter Action: action is the visitor action type.
* Type Parameter Predicate: Predicate that indicates whether to keep
* or stop Traversing
*/
template <class T, class Action, class Predicate>
class Traverser
{
    //TODO: Method implementation should be in traverser.cpp.
public:
    /**
    * Method: traverseDescendants
    * --------------------
    * Description: Traverses all nodes from the root to the
    * tips, applying the supplied visitor v to each node.
    * @param t a phylogenetic tree
    * @param v a visitor action to be applied on the tree's nodes
    */
    static void traverseDescendants(Domain::ITree<T>* t, Action& a)
    {
        traverseDescendants(t->getRoot(), a);
    }

    /**
    * Method: traverseDescendants
    * --------------------
    * Description: Traverses all nodes from the passed node to the
    * tips, applying the supplied visitor v to each node.
    * @param t a starting node
    * @param v a visitor action to be applied on the starting node's
    * descendants
    */
    static void traverseDescendants(T* t, Action& a)
    {
        NodeVisitor<Action, Predicate, T> v = NodeVisitor<Action, Predicate, T>(a);

        VisitAction act = ContinueTraversing;
        //A queue shall be used to avoid recursion
        std::queue<T*, std::list<T*> > queue;

        //Push the root
        queue.push(t);

        while (!queue.empty() && act == ContinueTraversing)
        {
            T* node = queue.front();

            queue.pop();

            //Visit the node that is on top of the queue
            act = v.visit(node);

            if (act == ContinueTraversing)
            {
                Domain::ListIterator<T, Domain::Node> it = node->template getChildrenIterator<T>();

                //And add the node's children to the queue
                for (; !it.end(); it.next())
                {
                    node = it.get();
                    queue.push(node);
                }
            }
        }
    }

    /**
    * Method: traverseAncestors
    * ------------------
    * Description: Traverses all nodes from the passed node tothe root,
    * applying the supplied visitor v to each node in the way.
    * @param t a starting node
    * @param v a visitor action to be applied on each ancestor of the
    * starting node
    */
    static void traverseAncestors(T* t, Action& a)
    {
        NodeVisitor<Action, Predicate, T> v = NodeVisitor<Action, Predicate, T>(a);

        VisitAction act = ContinueTraversing;
        T* node = t;

        //go up the tree
        while (act == ContinueTraversing)
        {
            act = v.visit(node);

            if (act == ContinueTraversing)
            {
                //get the parent
                if (!node->isRoot())
                    node = node->template getParent<T>();
                else
                    act = StopTraversing;
            }
        }
    }

    /**
     * Method: traversePostOrder
     * ------------------------
     * Description: Traverses all nodes from the passed node tothe root,
     * applying the supplied visitor v to each node in the way.
     * @param t a starting node
     * @param v a visitor action to be applied on each ancestor of the
     * starting node
     */
    static void traversePostOrder(Domain::ITree<T>* t, Action& a)
    {
        NodeVisitor<Action, Predicate, T> v = NodeVisitor<Action, Predicate, T>(a);
        traversePostOrderRecursive(t->getRoot(), v);
    }

private:

    static VisitAction traversePostOrderRecursive(T* node, NodeVisitor<Action, Predicate, T>& v)
    {
        if (!node->isLeaf())
        {
            Domain::ListIterator<T, Domain::Node> it = node->template getChildrenIterator<T>();

            for (; !it.end(); it.next())
            {
                T* child = it.get();
                traversePostOrderRecursive(child, v);
            }
        }
        return v.visit(node);
    }
};
}

#endif
