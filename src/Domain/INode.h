#ifndef INODE_H
#define INODE_H

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <mili/mili.h>

#include "ListIterator.h"



namespace Domain
{

    typedef float BranchLength;
    typedef std::string NodeName;
    /**
    * Class: Node
    * -----------
    * Description: Base phylogenetic node implementation
    */
    class Node
    {
    public:

        /**
        * Method: isRoot
        * ---------------
        * Description: Informs whether the node is the root of a tree.
        * @return true if the node is root, false otherwise
        */
        bool isRoot() const
        {
            return parent == NULL;
        }


        /**
        * Method: isLeaf
        * ---------------
        * Description: Informs whether the node is a Leaf
        * @return true if the node is leaf
        */
        bool isLeaf() const
        {
            return children.empty();
        }


        /**
        * Method: getParent
        * -----------------
        * Description: Allows the client to get the parent of the node.
        * @return if the node is not root, the parent of the node; and
        * null otherwise
        */
        template <class T>
        T* getParent() const
        {
            return static_cast<T*>(parent);
        }


        /**
        * Method: getChildrenIterator
        * ---------------------------
        * Description: Returns a ListIterator object that allows the
        * client to iterate through the node's children.
        * @returns ListIterator to iterate through the node's children
        */
        template <class T>
        ListIterator<T, Node> getChildrenIterator() const
        {
            ListIterator<T, Node> iter(children);
            return iter;
        }

        /**
        * Method: addChild
        * ----------------
        * Description: Adds a child to the node, and returns it being
        * already topologically binded to the tree.
        * @return Node already binded to the current node.
        */
        template <class T>
        T* addChild()
        {
            T* child = new T();
            child->parent = this;
            children.push_back(child);
            return child;
        }

        /**
        * Method: getName
        * ---------------
        * Description: Gets the name associated to the node
        * @return the node's name
        */
        NodeName getName() const
        {
            return name;
        }

        /**
        * Method: setName
        * ---------------
        * Description: Sets the name associated to the node
        */
        void setName(const NodeName& n)
        {
            name = n;
        }

        /**
        * Method: getBranchLength
        * ---------------
        * Description: Gets the branch length associated to the node
        * @return the node's branch length
        */
        BranchLength getBranchLength() const
        {
            return branchLength;
        }

        /**
        * Method: setBranchLength
        * ---------------
        * Description: Sets the name associated to the node
        */
        void setBranchLength(const BranchLength n)
        {
            branchLength = n;
        }

        Node() : parent(NULL) { }

        ~Node()
        {
            //Call to MiLi's delete_container
            //delete_container(children);
        }
        
    protected:

        Node* parent;
        std::list<Node*> children;
        
        NodeName name;
        BranchLength branchLength;


    };
}

#endif
