#ifndef PROPAGATOR_H
#define PROPAGATOR_H

#include "Domain/ITree.h"
#include "Domain/LocationAspect.h"
#include "PropagatorAspect.h"
#include "PropagatorAction.h"
#include "Phylopp/Traversal/Traverser.h"

namespace Propagation
{
    using namespace Domain;
    using namespace Traversal;
    using namespace Locations;
    
    typedef std::vector<Domain::BranchLength> BranchLengthVector; 

    template <class T>
    class Propagator
    {
    public:
        Propagator() {}
        
        static void propagate(Domain::ITree<T>* tree, 
                              unsigned int passesCount,
                              Weight geographicFactorWeight,
                              Weight branchLengthFactorWeight
                             )
        {
            BranchLength branchLenghtSum = getBranchLengthSum(tree);
            
            const DistanceVector& dispersalVector = getDispersionVector();
            
            PropagateFromChildrenAction<T> childrenAction(branchLenghtSum, 
                                             dispersalVector, 
                                             geographicFactorWeight, 
                                             branchLengthFactorWeight);
            PropagateFromParentAction<T> parentAction(branchLenghtSum, 
                                           dispersalVector, 
                                           geographicFactorWeight, 
                                           branchLengthFactorWeight);
            for(unsigned int i = 0; i < passesCount; i++)
            {
                if(isUpPass(i))                
                {
                    Traverser<T, PropagateFromChildrenAction<T>, AlwaysTruePredicate<T> >
                        ::traversePostOrder(tree, childrenAction);                    
                }
                else
                {
                    Traverser<T, PropagateFromParentAction<T>, AlwaysTruePredicate<T> >
                        ::traverseDescendants(tree, parentAction);        
                }
            } 
        }
        
    private:
        
        static bool isUpPass(unsigned int i)
        {
            //even passes are up
            return i % 2 == 0;
        }
        
        static const Locations::DistanceVector& getDispersionVector()
        {
            return T::getDispersionVector();
        }
        
        static BranchLength getBranchLengthSum(Domain::ITree<T>* tree)
        {
            return calculateBranchLengthSum(tree->getRoot());
        }
        
        static BranchLength calculateBranchLengthSum(T* node)
        {
            BranchLength ret = 0.0f;
            
            ret = node->getBranchLength();
            
            if(!node->isLeaf())
            {
                ListIterator<T, Node> it = node->template getChildrenIterator<T>();
                for( ; !it.end(); it.next())
                {
                    ret += calculateBranchLengthSum(it.get());
                }
            }
            return ret;
        }
        
        
    };
}

#endif
