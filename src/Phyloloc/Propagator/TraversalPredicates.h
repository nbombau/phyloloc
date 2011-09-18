#ifndef TRAVERSAL_PREDICATES_H
#define TRAVERSAL_PREDICATES_H

namespace Propagation
{
template <class T>
struct IsNotRootPredicate
{
    bool operator()(T* node) const
    {
        return !node->isRoot();
    }
};

template <class T>
struct IsNotLeafPredicate
{
    bool operator()(T* node) const
    {
        return !node->isLeaf();
    }
};

template <class T>
struct AlwaysTruePredicate
{
    bool operator()(T* /*node*/) const
    {
        return true;
    }
};
}

#endif