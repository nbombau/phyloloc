#ifndef PROPAGATOR_H
#define PROPAGATOR_H

#include "Domain/ITree.h"
#include "PropagatorAspect.h"
#include "PropagatorAction.h"
#include "Phylopp/Traversal/Traverser.h"

namespace Propagation
{
    class Propagator
    {
    public:
        Propagator() {}
        
        //TODO: Dummy implementation with two passes, 
        //passes number should be parametrized.
        template <class T>
        static void propagate(Domain::ITree<T>* tree)
        {
            Traverser<T, PropagateFromChildrenAction<T>, AlwaysTruePredicate<T> > t;
            PropagateFromChildrenAction<T> a;
            
            t.traversePostOrder(tree, a);
            
            Traverser<T, PropagateFromParentAction<T>, AlwaysTruePredicate<T> > t;
            PropagateFromParentAction<T> a;
            
            t.traverseDescendants(tree, a);
        }
    }
}

#endif
