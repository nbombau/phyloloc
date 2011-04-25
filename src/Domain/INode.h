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
                return parent->self();
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
                static_cast<Node<T>*>(child)->parent = self();
                children.push_back(child);
                return child;
            }

            /**
            * Method: getName
            * ---------------
            * Description: Gets the name associated to the node
            * @return the node's name
            */
            std::string getName() const 
            {
                return name;
            }

            /**
            * Method: setName
            * ---------------
            * Description: Sets the name associated to the node
            */
            void setName(const std::string& n)
            {
                name = n;
            }

            /**
            * Method: getLocation
            * ---------------
            * Description: Gets the location associated to the node
            * @return the node's location
            */
            std::string getLocation() const
            {
                return location;
            }

            /**
            * Method: setLocation
            * ---------------
            * Description: Sets the name associated to the node
            */
            void setLocation(const std::string& n)
            {
                location = n;
            }

            /**
            * Method: getBranchLength
            * ---------------
            * Description: Gets the branch length associated to the node
            * @return the node's branch length
            */
            float getBranchLength() const
            {
                return branchLength;
            }

            /**
            * Method: setBranchLength
            * ---------------
            * Description: Sets the name associated to the node
            */
            void setBranchLength(const float n)
            {
                branchLength = n;
            }

            Node() { }


        protected:

            T* parent;
            std::list<T*> children;
            std::string name;
            std::string location;
            float branchLength;

            /**
            * Method: self
            * ------------
            * Description: Obtain the underlying node implementation (CRTP)
            */
            T* self() { return static_cast<T*>(this); }
            const T* self() const { return static_cast<const T*>(this); }

           // ~Node()
           // {
                //TODO: free resources
           // }
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
