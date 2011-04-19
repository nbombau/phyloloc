#ifndef TRAVERSER_H
#define TRAVERSER_H

#include "INodeVisitor.h"
#include "../../Domain/ITree.h"
#include "../../Domain/INode.h"
#include "../../Domain/ListIterator.h"

#include <list>
#include <stdlib.h>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <queue>

namespace Traversal
{
    using namespace std;
    using namespace Domain;

    /**
    * Class: Traverser
    * ----------------
    * Description: Allows the client to easily traverse a phylogenetic tree
    * Type Parameter T: T is the node type. Hence, T should implement INode
    * Type Parameter V: V is the visitor type. The visitor shall visit each node
    * during the traversal of the tree.
    */
    template <class T, class V>
    class Traverser
    {
    //TODO: Method implementation should be in traverser.cpp.
    public:
        /**
        * Method: traverseDown
        * --------------------
        * Description: Traverses all nodes from the root to the
        * tips, applying the supplied visitor v to each node.
        * @param t a phylogenetic tree
        * @param v a visitor to be applied on the tree's nodes
        */
        void traverseDown(Domain::ITree<T>* t, INodeVisitor<T>* v)
        {
            traverseDown(t->getRoot(), v);
        }

        /**
        * Method: traverseDown
        * --------------------
        * Description: Traverses all nodes from the passed node to the 
        * tips, applying the supplied visitor v to each node.
        * @param t a starting node
        * @param v a visitor to be applied on the starting node's 
        * descendants
        */
        void traverseDown(T* t, V* v)
        {
            //A queue shall be used to avoid recursion
            std::queue<T*, list<T*>> queue;

            //Push the root        
            queue.push(t);

            while (!queue.empty())
            {
                T* node = queue.front();
                queue.pop();

                //Visit the node that is on top of the queue
                v->visit(node);

                ListIterator<T>* it = node->getChildrenIterator();
            
                //And add the node's children to the queue
                while(!it->end())
                {
                    node = &(it->get());
                    queue.push(node);
                    it->next();
                }
            }
        }

        /**
        * Method: traverseUp
        * ------------------
        * Description: Traverses all nodes from the passed node tothe root,
        * applying the supplied visitor v to each node in the way.
        * @param t a starting node
        * @param v a visitor to be applied on each ancestor of the 
        * starting node
        */
        void traverseUp(T* t, V* v)
        {
            T* node = t;
            while(!node->isRoot())
            {
                v->visit(node);
                node = node->parent();
            }
        }
    };
}

#endif