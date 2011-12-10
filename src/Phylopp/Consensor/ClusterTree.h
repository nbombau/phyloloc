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

#ifndef CLUSTER_TREE_H
#define CLUSTER_TREE_H

#include <list>
#include <stdio.h>
#include "bitset.h"
#include "Domain/INode.h"
#include "Domain/LocationAspect.h"
#include "Domain/ITree.h"

class ConsensorExceptionHierarchy {};
typedef GenericException<ConsensorExceptionHierarchy> ConsensorException;


/**
* DisjointTerminalsException
* --------------------
* Description: Exception used when the trees to be consensed have disjoint terminal nodenames
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(DisjointTerminalsException,
ConsensorExceptionHierarchy,
"Tree collection is not valid for consensus for having disjoint terminal nodes.");
namespace Consensus
{
    template <class Node>
    struct NodeCluster
    {
        bitset cluster;
        //TODO: const correctness
        Node* node;
        
        NodeCluster(bitset b, Node* n)
        : cluster(b), node(n) {}
        NodeCluster(bitset b) : cluster(b), node(NULL) {}
    };
    
    
    template <class Node, class Observer>
    class ClusterTree
    {
        
        typedef typename std::list<NodeCluster<Node> > ClusterList;
        typedef typename std::list<NodeCluster<Node> >::iterator ClusterIterator;
        typedef typename std::list<NodeCluster<Node> >::const_iterator ClusterConstIterator;
        
        
        private:
            
            Observer& obs;
            ClusterList clusters;
            bool isConsensusTree;
            Locations::LocationManager& locationManager;
            
            void calculateClusters(Domain::ITree<Node>* tree)
            {
                bitset b(locationManager.getNodeNameCount());
                b = buildCluster(tree->getRoot(), b);
                
            }
            
            
            bitset& buildCluster(Node* node, bitset& set)
            {
                bitset nodeCluster(locationManager.getNodeNameCount());
                if (!node->isLeaf())
                {
                    Domain::ListIterator<Node, Domain::Node> it = node->template getChildrenIterator<Node>();
                    for (; !it.end(); it.next())
                    {
                        nodeCluster |= buildCluster(it.get(), set);
                    }
                }
                else
                {
                    buildLeafCluster(node, nodeCluster);
                }
                NodeCluster<Node> clust(nodeCluster, node);
                clusters.push_back(clust);
                set = bitset(nodeCluster);
                return set;
            }
            
            void buildLeafCluster(Node* leaf, bitset& b)
            {
                b.reset();
                b.set(locationManager.getNodeNameId(leaf->getName()) - 1);
            }
            
            bitset getConsensedRoot() const
            {
                bitset aux(locationManager.getNodeNameCount());
                
                for (ClusterConstIterator it = clusters.begin(); it != clusters.end(); it++)
                    aux |= (*it).cluster;
                
                return aux;
            }
            
        public:
            
            ClusterTree(Domain::ITree<Node>* t, Observer& observer, Locations::LocationManager& locMgr)
            : obs(observer), isConsensusTree(false), locationManager(locMgr)
            {
                calculateClusters(t);
            }
            
            ClusterTree(const ClusterTree<Node, Observer>& other, Observer& observer, Locations::LocationManager& locMgr)
            : obs(observer), isConsensusTree(true), locationManager(locMgr)
            {
                ClusterConstIterator it = other.getClusterIterator();
                
                for (; it != other.clusters.end(); it++)
                {
                    bitset newCluster((*it).cluster);
                    NodeCluster<Node> n(newCluster, (*it).node);
                    clusters.push_back(n);
                    obs.onInclude((*it).node, newCluster);
                }
            }
            
            ClusterConstIterator getClusterIterator() const
            {
                ClusterConstIterator it = clusters.begin();
                return it;
            }
            
            bool containsCluster(const bitset& bits) const
            {
                ClusterConstIterator it = clusters.begin();
                bool contains = false;
                
                while (it != clusters.end() && !contains)
                {
                    contains = it->cluster == bits;
                    it++;
                }
                
                return contains;
            }
            
            void intersectWith(const ClusterTree<Node, Observer >& other)
            {
                ClusterIterator itLocal = clusters.begin();
                
                ClusterConstIterator itExtern = other.getClusterIterator();
                bool isPresent = false;
                for (; itLocal != clusters.end(); itLocal++, isPresent = false)
                {
                    
                    itExtern = other.getClusterIterator();
                    for (; itExtern != other.clusters.end() && !isPresent; itExtern++)
                    {
                        if ((*itLocal).cluster == (*itExtern).cluster)
                        {
                            isPresent = true;
                        }
                    }
                    itExtern--;
                    if (isPresent)
                    {
                        obs.onInclude((*itExtern).node, (*itLocal).cluster);
                        if ((*itLocal).node->getBranchLength() > (*(itExtern)).node->getBranchLength())
                        {
                            (*itLocal).node = (*itExtern).node;
                        }
                        //else not needed
                    }
                    else
                    {
                        obs.onExclude((*itExtern).node, (*itLocal).cluster);
                        itLocal = clusters.erase(itLocal);
                        itLocal--;
                    }
                }
            }
            
            Domain::ITree<Node>* toTree()
            {
                std::vector<Node*> nodes(clusters.size(), NULL);
                ClusterIterator it;
                
                //Sort the clusters in descending order, so that the root cluster is first, and
                //the leaves at the end
                clusters.sort(BitsetComparator());
                
                //Get the root that comes from or-ing all the clusters to check disjoint clusters
                //between trees
                bitset root = getConsensedRoot();
                
                //if the roots don't match, the clusters are disjoint, cant create consensus tree
                if (root != clusters.front().cluster)
                    throw DisjointTerminalsException();
                
                Domain::ITree<Node> * tree = new Domain::ITree<Node>();
                
                unsigned int nextChildIndex = 1; 
                bool first = true;
                //iterate forward through the clusters. 
                for(it = clusters.begin(); it != clusters.end(); it++)
                {
                    //special case for the root
                    if(it == clusters.begin())
                    {
                        nodes[0] = tree->getRoot();
                        nodes[0]->cluster = clusters.front().cluster;
                    }
                    else
                    {
                        //find the ancestors of the current cluster, and build the node associated
                        //to the closest ancestor
                        nodes[nextChildIndex] = bindClusterToConsensus(it, nodes, nextChildIndex);
                        nextChildIndex++;
                    }
                    
                }
                
                return tree;
            }
            
            Node* bindClusterToConsensus(ClusterIterator current, std::vector<Node*>& nodes, unsigned int nextChildIndex) const
            {
                ClusterIterator parentSearchIter = current;
                bool foundParent = false;
                unsigned int parentIndex = nextChildIndex - 1;
                Node* nodeToBind = NULL;
                
                //start searching the parent backwards through the iterator
                parentSearchIter--;
                
                while(!foundParent)
                {
                    //the parent is the ancestor that is closer in the nodes vector
                    if(areParentAndChild(*parentSearchIter, *current))
                    {
                        nodeToBind = nodeFromCluster(*current, nodes[parentIndex]);
                        foundParent = true;
                    }
                    //if no more clusters to the left, we found the parent, it's the root!
                    else if(parentSearchIter == clusters.begin())
                    {
                        foundParent = true;
                    }
                    //if we didn't find the parent yet, keep looking backwards
                    else
                    {
                        parentIndex--;
                        parentSearchIter--;
                    }
                }
                return nodeToBind;
            }
            
            bool areParentAndChild(NodeCluster<Node>& parent, NodeCluster<Node>& child) const
            {
                return (((parent.cluster) & (child.cluster)) == (child.cluster));
            }
            
            Node* nodeFromCluster(const NodeCluster<Node>& n, Node* parent) const
            {
                Node* child = parent->template addChild<Node>();
                child->setName(n.node->getName());
                child->setBranchLength(n.node->getBranchLength());
                child->cluster = n.cluster;
                return child;
            }
            
            class BitsetComparator
            {
                public:
                    bool operator()(NodeCluster<Node>& node1, NodeCluster<Node>& node2)
                    {
                        bool ret = false;
                        if (countTrueBits(node1.cluster) > countTrueBits(node2.cluster))
                            ret = true;
                        return ret;
                    }
                    
                    static size_t countTrueBits(Consensus::bitset& bs)
                    {
                        size_t cant = 0;
                        for (unsigned int i = 0; i < bs.size(); ++i)
                            cant += (bs[i] == bitset::bit::true_bit) ? 1 : 0;
                        return cant;
                    }
            };
    };
}

#endif
