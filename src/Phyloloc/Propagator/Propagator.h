#ifndef PROPAGATOR_H
#define PROPAGATOR_H

#include "Domain/ITree.h"
#include "Domain/LocationAspect.h"
#include "PropagatorAspect.h"
#include "PropagatorAction.h"
#include "Phylopp/Traversal/Traverser.h"

namespace Propagation
{
    typedef std::vector<Domain::BranchLength> BranchLengthVector; 
    
    template <class T>
    class Propagator
    {
    public:
        Propagator() {}
        
        //TODO: Dummy implementation with two passes, 
        //passes number should be parametrized.
        
        static void propagate(Domain::ITree<T>* tree, 
                              unsigned int passesCount,
                              Weight geographicFactorWeight,
                              Weight branchLengthFactorWeight
                             )
        {
            BranchLength branchLenghtSum = calculateBranchLengthSum(tree);
            Traverser<T, PropagateFromChildrenAction<T>, AlwaysTruePredicate<T> > t;
            PropagateFromChildrenAction<T> a(branchLenghtSum, 
                                             getDispersionVector(), 
                                             geographicFactorWeight, 
                                             branchLengthFactorWeight);
            
            t.traversePostOrder(tree, a);
            
            Traverser<T, PropagateFromParentAction<T>, AlwaysTruePredicate<T> > t;
            PropagateFromParentAction<T> a(branchLenghtSum, 
                                           getDispersionVector(), 
                                           geographicFactorWeight, 
                                           branchLengthFactorWeight);
            
            t.traverseDescendants(tree, a);
        }
        
    private:
        
        static const Locations::DistanceVector& getDispersionVector()
        {
            return LocationAspect<T>::getDispersionVector();
        }
        
        static Domain::BranchLength getBranchLengthSum(Domain::ITree<T>* tree)
        {
            Domain::BranchLength branchLengthSum = calculateBranchLengthSum(tree->getRoot());
        }
        
        static Domain::BranchLength calculateBranchLengthSum(T* node)
        {
            Domain::BranchLength ret = 0f;
            
            ret = node->getBranchLength();
            
            if(!node->isLeaf())
            {
                ListIterator<T> it = node->getChildrenIterator();
                for( ; !it.end(); it.next())
                {
                    ret += calculateBranchLengthSum(it.get());
                }
            }
            return ret;
        }
        
        
    }
}

#endif
