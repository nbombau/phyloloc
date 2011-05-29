#ifndef PROPAGATOR_ACTION_H
#define PROPAGATOR_ACTION_H

#include "PropagatorAspect.h"
#include "Phylopp/Traversal/NodeVisitor.h"
#include "Phylopp/Traversal/Traverser.h"

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
        bool operator()(T* node) const
        {
            return true;
        }
    };
    
    template <class T>
    class PropagateFromChildrenAction
    {
    public:
        PropagateFromChildrenAction() {}
        
        VisitAction visitNode(T* n)
        {
            n->propagateFromChildren();
            
            return ContinueTraversing;
        }
    };
    
    template <class T>
    class PropagateFromParentAction
    {
    public:
        PropagateFromParentAction() {}
        
        VisitAction visitNode(T* n)
        {
            n->propagateFromParent();
            
            return ContinueTraversing;
        }
    };
    
}


#endif