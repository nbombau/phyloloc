#ifndef SEARCHNODE_H
#define SEARCHNODE_H

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
    SelectNodeAction(const std::string& searchString)
    {
        regExp = searchString;
    }

    VisitAction visitNode(T* n)
    {
        if (n->getLocation().find(regExp, 0) != std::string::npos)
        {
            n->setSelected(true);
            n->update();
        }
        return ContinueTraversing;
    }
private:
    std::string regExp;
};


template <class T>
class SearchNode : public T
{
public:
    void setRoot(T* root)
    {
        node = root;
    }

    void search(const std::string& expression)
    {
        Traverser<T, SelectNodeAction<T> , IsLeafPredicate<T> > t;
        SelectNodeAction<T> a(expression);

        t.traverseDescendants(node, a);
    }
private:
    T* node;
};

}

#endif
