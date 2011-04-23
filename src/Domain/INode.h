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

    using namespace std;

    /**
    * Interface: INode
    * ----------------------
    * Description: Interface that defines the basic operation of a node of
    * a phylogenetic tree
    * Type Parameter T: T is the underlying node class (CRTP) 
    */
    template <class T>
	class INode
	{
	public:
        /**
        * Method: isRoot
        * ---------------
        * Description: Informs whether the node is the root of a tree.
        * @return true if the node is root, false otherwise
        */
        virtual bool isRoot() const = 0;

        /**
        * Method: isLeaf
        * ---------------
        * Description: Informs whether the node is a Leaf
        * @return true if the node is leaf
        */
        virtual bool isLeaf() const = 0;

        /**
        * Method: getParent
        * -----------------
        * Description: Allows the client to get the parent of the node.
        * @return if the node is not root, the parent of the node; and 
        * null otherwise
        */
        virtual T* getParent() const = 0;

        /**
        * Method: getChildrenIterator
        * ---------------------------
        * Description: Returns a ListIterator object that allows the 
        * client to iterate through the node's children.
        * @returns ListIterator to iterate through the node's children
        */
        virtual ListIterator<T>* getChildrenIterator() = 0;

        /**
        * Method: addChild
        * ----------------
        * Description: Adds a child to the node, and returns it being
        * already topologically binded to the tree.
        * @return Node already binded to the current node.
        */
		virtual T* addChild() = 0;

        /**
        * Method: getName
        * ---------------
        * Description: Gets the name associated to the node
        * @return the node's name
        */
		virtual string getName() const = 0;

        /**
        * Method: getLocation
        * ---------------
        * Description: Gets the location associated to the node
        * @return the node's location
        */
        virtual string getLocation() const = 0;

        /**
        * Method: getBranchLength
        * ---------------
        * Description: Gets the branch length associated to the node
        * @return the node's branch length
        */
        virtual float getBranchLength() const = 0;

        /**
        * Method: setName
        * ---------------
        * Description: Sets the name associated to the node
        */
        virtual void setName(const string& n) = 0;

        /**
        * Method: setLocation
        * ---------------
        * Description: Sets the name associated to the node
        */
        virtual void setLocation(const string& n) = 0;

        /**
        * Method: setBranchLength
        * ---------------
        * Description: Sets the name associated to the node
        */
        virtual void setBranchLength(const float n) = 0;


	};

    /**
    * Class: Node
    * -----------
    * Description: Base phylogenetic node implementation
    * Type Parameter T: T is the underlying node class (CRTP) 
    */
    template <class T>
    class Node : public INode<T>
    {
        public:

            virtual bool isRoot() const { return parent == NULL; }

            virtual bool isLeaf() const { return children.empty(); }

            virtual T* getParent() const 
            {
                return parent->self();
            }

            virtual ListIterator<T>* getChildrenIterator()
            {
                return new ListIterator<T>(children);
            }

            virtual T* addChild()
            {
                T* child = new T();
                static_cast<Node<T>*>(child)->parent = self();
                children.push_back(child);
                return child;
            }

            virtual string getName() const 
            {
                return name;
            }

            virtual void setName(const string& n)
            {
                name = n;
            }

            virtual string getLocation() const
            {
                return location;
            }

            virtual void setLocation(const string& n)
            {
                location = n;
            }

            virtual float getBranchLength() const
            {
                return branchLength;
            }

            virtual void setBranchLength(const float n)
            {
                branchLength = n;
            }

            Node() { }


        protected:

            T* parent;
            list<T*> children;
            string name;
            string location;
            float branchLength;

            /**
            * Method: self
            * ------------
            * Description: Obtain the underlying node implementation (CRTP)
            */
            T* self() { return static_cast<T*>(this); }
            const T* self() const { return static_cast<const T*>(this); }

            ~Node()
            {
                //TODO: free resources
            }
    };

    /**
    * Class: PlacesNode
    * -----------------
    * Description: Base underlying node class for the Node template
    */
    class PlacesNode : public Node<PlacesNode>
    {
    public:
        PlacesNode()
        {}
    protected:
        ~PlacesNode()
        {
            //TODO: Free resources
            //delete_container(children);
        }
    };
}

#endif
