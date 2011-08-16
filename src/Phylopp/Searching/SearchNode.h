#ifndef SEARCHNODE_H
#define SEARCHNODE_H

#include "Domain/LocationManager.h"
#include "Phylopp/Traversal/Traverser.h"
#include "Phylopp/Traversal/NodeVisitor.h"


using namespace Traversal;

namespace Searching
{
template <class T>
struct IsLeafPredicate
{
    bool operator()(T* node) const
    {
        return node->isLeaf();
    }
};

template <class T>
class SelectNodeAction
{
public:
    SelectNodeAction(const std::string& searchString, const Locations::LocationManager locationManager)
    {
        regExp = searchString;
        this->locationManager = locationManager;
    }

    VisitAction visitNode(T* n)
    {
        Location location = locationManager.getLocation(n->getName());
        if (!location.empty() && location.find(regExp, 0) != std::string::npos)
        {
            n->setSelected(true);
            n->update();
        }
        return ContinueTraversing;
    }
private:
    std::string regExp;
    Locations::LocationManager locationManager;
};


template <class T>
class SearchNode : public T
{
public:
    void setRoot(T* root)
    {
        node = root;
    }

    void search(const std::string& expression, Locations::LocationManager locationManager)
    {
        Traverser<T, SelectNodeAction<T> , IsLeafPredicate<T> > t;
        SelectNodeAction<T> a(expression, locationManager);

        t.traverseDescendants(node, a);
    }
private:
    T* node;
};

}

#endif
