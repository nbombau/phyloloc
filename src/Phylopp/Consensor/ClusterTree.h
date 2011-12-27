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
        buildCluster(tree->getRoot(), b);
    }

public:
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
        //store the pair Node, Bitset, so that they are used when the consensus tree is build
        NodeCluster<Node> clust(nodeCluster, node);
        clusters.push_back(clust);
        set = bitset(nodeCluster);
        return set;
    }

    void buildLeafCluster(const Node* const leaf, bitset& b) const
    {
        b.reset();
        b.set(locationManager.getNodeNameId(leaf->getName()) - 1);
    }

    bitset getConsensedRoot() const
    {
        bitset aux(locationManager.getNodeNameCount());

        for (ClusterConstIterator it = clusters.begin(); it != clusters.end(); ++it)
            aux |= it->cluster;

        return aux;
    }

    //returns true if the trees represented by the clusters to be consensed are disjoint
    bool treesAreDisjoint() const
    {
        //get the root that results on or-ing all clusters
        const bitset root = getConsensedRoot();

        //if the roots don't match, the clusters are disjoint, cant create consensus tree
        return root != clusters.front().cluster;
    }

    static bool areParentAndChild(NodeCluster<Node>& parent, NodeCluster<Node>& child)
    {
        return (parent.cluster & child.cluster) == child.cluster;
    }

    static Node* nodeFromCluster(const NodeCluster<Node>& n, Node* parent)
    {
        Node* child = parent->template addChild<Node>();
        child->setName(n.node->getName());
        child->setBranchLength(n.node->getBranchLength());
        child->cluster = n.cluster;
        return child;
    }

    Node* bindClusterToConsensus(ClusterIterator current, std::vector<Node*>& nodes, unsigned int nextChildIndex) const
    {
        ClusterIterator parentSearchIter = current;
        bool foundParent = false;
        bool canContinue = true;
        //as parents are in the right of the vector, index 0 corresponds to the root.
        //as root has no parents we return null if nextChildIndex = 0
        if (nextChildIndex == 0) return NULL;

        unsigned int parentIndex = nextChildIndex - 1;
        Node* nodeToBind = NULL;

        //start searching the parent backwards through the iterator
        --parentSearchIter;

        do
        {
            //the parent is the ancestor that is closer in the nodes vector
            if (areParentAndChild(*parentSearchIter, *current))
            {
                foundParent = true;
            }
            //if we didn't find the parent yet, keep looking backwards
            else if(parentIndex == 0)
            {
                canContinue = false;
            }
            else
            {
                --parentIndex;
                --parentSearchIter;
            }
        }
        while (!foundParent && canContinue);

        if (foundParent)
            nodeToBind = nodeFromCluster(*current, nodes[parentIndex]);

        return nodeToBind;
    }

    class BitsetComparator
    {
    public:
        bool operator()(NodeCluster<Node>& node1, NodeCluster<Node>& node2) const
        {
            return countTrueBits(node1.cluster) > countTrueBits(node2.cluster);
        }

        static size_t countTrueBits(Consensus::bitset& bs)
        {
            size_t count = 0;
            //TODO: use std::count_if, but before shouldn't bitset provide bit iterator?
            for (unsigned int i = 0; i < bs.size(); ++i)
                count += (bs[i] == bitset::bit::true_bit) ? 1 : 0;
            return count;
        }
    };



    ClusterTree(Domain::ITree<Node>* t, Observer& observer, Locations::LocationManager& locMgr)
        : obs(observer), isConsensusTree(false), locationManager(locMgr)
    {
        calculateClusters(t);
    }

    ClusterTree(const ClusterTree<Node, Observer>& other, Observer& observer, Locations::LocationManager& locMgr)
        : obs(observer), isConsensusTree(true), locationManager(locMgr)
    {
        ClusterConstIterator it = other.getClusterIterator();

        for (; it != other.clusters.end(); ++it)
        {
            bitset newCluster(it->cluster);
            NodeCluster<Node> n(newCluster, it->node);
            clusters.push_back(n);
            obs.onInclude(it->node, newCluster);
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
            ++it;
        }

        return contains;
    }

    void intersectWith(const ClusterTree<Node, Observer >& other)
    {
        ClusterIterator itLocal = clusters.begin();

        ClusterConstIterator itExtern = other.getClusterIterator();
        bool isPresent = false;
        for (; itLocal != clusters.end(); ++itLocal, isPresent = false)
        {

            itExtern = other.getClusterIterator();
            for (; itExtern != other.clusters.end() && !isPresent; ++itExtern)
            {
                if (itLocal->cluster == itExtern->cluster)
                {
                    isPresent = true;
                }
            }
            --itExtern;
            if (isPresent)
            {
                obs.onInclude(itExtern->node, itLocal->cluster);
                if (itLocal->node->getBranchLength() > itExtern->node->getBranchLength())
                {
                    itLocal->node = itExtern->node;
                }
                //else not needed
            }
            else
            {
                obs.onExclude(itExtern->node, itLocal->cluster);
                itLocal = clusters.erase(itLocal);
                --itLocal;
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

        //If the trees have disjoint terminals, we can't create consensus tree
        if (treesAreDisjoint())
            throw DisjointTerminalsException();

        Domain::ITree<Node>* const tree = new Domain::ITree<Node>();

        //special case for the root
        nodes[0] = tree->getRoot();
        nodes[0]->cluster = clusters.front().cluster;

        if (clusters.size() == 1) return tree;

        it = clusters.begin();
        ++it;

        //iterate forward through the clusters.
        for (unsigned int nextChildIndex = 1; it != clusters.end(); ++it, ++nextChildIndex)
        {
            //find the ancestors of the current cluster, and build the node associated
            //to the closest ancestor
            nodes[nextChildIndex] = bindClusterToConsensus(it, nodes, nextChildIndex);
        }

        return tree;
    }

};
}

#endif
