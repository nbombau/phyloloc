#ifndef CLUSTER_TREE_H
#define CLUSTER_TREE_H

#include <list>
#include "bitset.h"
#include "Domain/INode.h"
#include "Domain/LocationAspect.h"
#include "Domain/ITree.h"

namespace Consensus
{
template <class Node2>
struct NodeCluster
{
    bitset cluster;
    //TODO: const correctness
    Node2 * node;

    NodeCluster(bitset b, Node2 * n)
        : cluster(b), node(n) {}
    NodeCluster(bitset b) : cluster(b), node(NULL) {}
};


template <class Node2, class Observer>
class ClusterTree
{
    Observer& obs;
    typedef typename std::list<NodeCluster<Node2> > ClusterList;
    typedef typename std::list<NodeCluster<Node2> >::iterator ClusterIterator;
    typedef typename std::list<NodeCluster<Node2> >::const_iterator ClusterConstIterator;


private:



    //Node::LocationManager& locationManager;
    //TODO: try to remove this and uset just to set values initially
    Domain::ITree<Node2>* tree;
    ClusterList clusters;
    bool isConsensusTree;
    Locations::LocationManager& locationManager;

    void calculateClusters()
    {
        bitset b(locationManager.getNodeNameCount());
        b = buildCluster(tree->getRoot(), b);

    }


    bitset& buildCluster(Node2* node, bitset& set)
    {
        bitset nodeCluster(locationManager.getNodeNameCount());
        if(!node->isLeaf())
        {
            Domain::ListIterator<Node2, Domain::Node> it = node->template getChildrenIterator<Node2>();
            for(; !it.end(); it.next())
            {
                nodeCluster |= buildCluster(it.get(), set);
            }
        }
        else
        {
            buildLeafCluster(node, nodeCluster);
        }
        NodeCluster<Node2> clust(nodeCluster, node);
        clusters.push_back(clust);
        set = bitset(nodeCluster);
        return set;
    }

    void buildLeafCluster(Node2 * leaf, bitset& b)
    {
        b.reset();
        b.set(locationManager.getNodeNameId(leaf->getName()) - 1);
    }

    bitset getConsensedRoot() const
    {
        bitset aux(locationManager.getNodeNameCount());
     
        for(ClusterConstIterator it = clusters.begin(); it!=clusters.end(); it++)
            aux|=(*it).cluster;

        return aux;
    }

public:

    ClusterTree(Domain::ITree<Node2>* t, Observer& observer, Locations::LocationManager& locMgr)
        : obs(observer), tree(t), isConsensusTree(false), locationManager(locMgr)
    {
        calculateClusters();
    }

    ClusterTree(const ClusterTree<Node2,Observer>& other, Observer& observer, Locations::LocationManager& locMgr)
        : obs(observer), isConsensusTree(true), locationManager(locMgr)
    {
        ClusterConstIterator it = other.getClusterIterator();
        
        for(; it != other.clusters.end(); it++)
        {
            bitset newCluster((*it).cluster);
            NodeCluster<Node2> n(newCluster, (*it).node);
            clusters.push_back(n);
            obs.onInclude(n.node, n.cluster);
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
        
        while(it != clusters.end() && !contains)
        {
            contains = it->cluster == bits;
            it++;
        }
        
        return contains;
    }

    void intersectWith(const ClusterTree<Node2, Observer >& other)
    {
        ClusterIterator itLocal = clusters.begin();

        ClusterConstIterator itExtern = other.getClusterIterator();
        bool isPresent = false;
        for(; itLocal != clusters.end(); itLocal++,isPresent=false)
        {

            itExtern=other.getClusterIterator();
            for(; itExtern!=other.clusters.end() && !isPresent; itExtern++)
            {
                if( (*itLocal).cluster == (*itExtern).cluster )
                {
                    isPresent=true;
                }
            }
            itExtern--;
            if(isPresent)
            {
                obs.onInclude((*itExtern).node, (*itExtern).cluster);
                if((*itLocal).node->getBranchLength()>(*(itExtern)).node->getBranchLength())
                {
                    (*itLocal).node=(*itExtern).node;
                }
                //else not needed
            }
            else
            {
                obs.onExclude((*itExtern).node,(*itLocal).cluster);
                itLocal=clusters.erase(itLocal);
                itLocal--;
            }
        }
    }

    Domain::ITree<Node2>* toTree()
    {
        ClusterIterator it;
        ClusterIterator itAux;
        unsigned int j,aux;
        bool quit;
        Domain::ITree<Node2> * tree = new Domain::ITree<Node2>();
        std::vector<Node2 *> nodes(clusters.size(), NULL);
        clusters.sort(BitsetComparator());

        nodes[0]=tree->getRoot();
        bitset root = getConsensedRoot();

        if(root!=clusters.front().cluster)
        {
            NodeCluster<Node2> clust(root, nodes[0]);
            nodes[0]->cluster = root;
            clusters.push_front(clust);
        }
        else
            nodes[0]->cluster = clusters.front().cluster;

        it = clusters.begin();

        //TODO for should be while
        for(j=1,it++; it!=clusters.end(); ++j,it++,quit=false)
        {
            itAux=it;
            aux=j;
            for(--j,it--,quit=false; !quit; --j,it--)
            {
                if( (((*it).cluster) & ((*itAux).cluster)) == ((*itAux).cluster) )
                {
                    nodes[aux] = nodes[j]->template addChild<Node2>();
                    nodes[aux]->template setName(itAux->node->template getName());
                    nodes[aux]->template setBranchLength(itAux->node->template getBranchLength());
                    nodes[aux]->cluster = (*itAux).cluster;
                    quit=true;
                    
                    nodes[aux]->cluster.print();
                    
                }
                if(it==clusters.begin())
                    quit=true;
            }
            j=aux;
            it=itAux;
        }
        return tree;
    }
    
    class BitsetComparator
    {
    public:
        bool operator() (NodeCluster<Node2> & node1,NodeCluster<Node2> & node2)
        {
            bool ret=false;
            if(countTrueBits(node1.cluster)>countTrueBits(node2.cluster))
                ret=true;
            return ret;
        }
        //TODO add to bitset implementation?
        static size_t countTrueBits(Consensus::bitset & bs)
        {
            size_t cant=0;
            for(unsigned int i=0; i<bs.size(); ++i)
                cant += (bs[i]==bitset::bit::true_bit)?1:0;
            return cant;
        }
    };
};
}

#endif
