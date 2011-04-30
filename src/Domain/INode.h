#ifndef INODE_H
#define INODE_H

#include <stdlib.h>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "ListIterator.h"

typedef float BranchLength;
typedef std::string Location;
typedef std::string NodeName;

namespace Domain
{

    /**
    * Class: Node
    * -----------
    * Description: Base phylogenetic node implementation
    * Type Parameter T: T is the underlying node class (CRTP) 
    */
    template <class T>
    class Node
    {
        public:

            /**
            * Method: isRoot
            * ---------------
            * Description: Informs whether the node is the root of a tree.
            * @return true if the node is root, false otherwise
            */
            bool isRoot() const { return parent == NULL; }


            /**
            * Method: isLeaf
            * ---------------
            * Description: Informs whether the node is a Leaf
            * @return true if the node is leaf
            */
            bool isLeaf() const { return children.empty(); }


            /**
            * Method: getParent
            * -----------------
            * Description: Allows the client to get the parent of the node.
            * @return if the node is not root, the parent of the node; and 
            * null otherwise
            */
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
            ListIterator<T>* getChildrenIterator() const
            {
                return new ListIterator<T>(children);
            }

            /**
            * Method: addChild
            * ----------------
            * Description: Adds a child to the node, and returns it being
            * already topologically binded to the tree.
            * @return Node already binded to the current node.
            */
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
            * Method: getLocation
            * ---------------
            * Description: Gets the location associated to the node
            * @return the node's location
            */
            Location getLocation() const
            {
                return location;
            }

            /**
            * Method: setLocation
            * ---------------
            * Description: Sets the name associated to the node
            */
            void setLocation(const Location& n)
            {
                location = n;
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

            Node() { }


        protected:

            Node<T>* parent;
            std::list<T*> children;
            NodeName name;
            Location location;
            BranchLength branchLength;

            ~Node()
            {
                //TODO: free resources
            }
    };

    /**
    * Class: BaseAspect
    * -----------------
    * Description: Base underlying node aspect for the Node template
    */
    class BaseAspect
    {

    };
}

#endif
