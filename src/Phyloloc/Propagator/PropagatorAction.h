#ifndef PROPAGATOR_ACTION_H
#define PROPAGATOR_ACTION_H

#include "PropagatorAspect.h"
#include "Phylopp/Traversal/NodeVisitor.h"
#include "Phylopp/Traversal/Traverser.h"
#include "Domain/LocationManager.h"

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

    template <class T>
    class PropagateFromChildrenAction
    {
    public:
        PropagateFromChildrenAction(Domain::BranchLength blSum,
                                    const Locations::DistanceVector& dispersal,
                                    Weight geographic,
                                    Weight branch,
                                    Locations::LocationManager& manager)
            : 
            locationManager(manager),
            branchLengthSum(blSum),
            geographicFactorWeight(geographic),
            branchLenghtFactorWeight(branch),
            dispersalVector(dispersal)

        {}

        VisitAction visitNode(T* n)
        {
            n->propagateFromChildren(branchLengthSum, dispersalVector, geographicFactorWeight, branchLenghtFactorWeight, locationManager);

            return ContinueTraversing;
        }

    private:
        Locations::LocationManager& locationManager;
        Domain::BranchLength branchLengthSum;
        Weight geographicFactorWeight;
        Weight branchLenghtFactorWeight;
        const Locations::DistanceVector& dispersalVector;
        
    };

    template <class T>
    class PropagateFromParentAction
    {
    public:
        PropagateFromParentAction(Domain::BranchLength blSum,
                                const Locations::DistanceVector& dispersal,
                                Weight geographic,
                                Weight branch)
            : branchLengthSum(blSum),
            geographicFactorWeight(geographic),
            branchLenghtFactorWeight(branch),
            dispersalVector(dispersal)

        {}

        VisitAction visitNode(T* n)
        {
            n->propagateFromParent(branchLengthSum, dispersalVector, geographicFactorWeight, branchLenghtFactorWeight);

            return ContinueTraversing;
        }

    private:

        Domain::BranchLength branchLengthSum;
        Weight geographicFactorWeight;
        Weight branchLenghtFactorWeight;
        const Locations::DistanceVector& dispersalVector;
    };
    
    /*template <class T, class Observer>
    class ObservablePropagateFromParentAction : public PropagateFromParentAction
    {
        public:
            PropagateFromParentAction(Domain::BranchLength blSum,
                                      const Locations::DistanceVector& dispersal,
                                      Weight geographic,
                                      Weight branch,
                                      Observer& obs)
                                      : PropagateFromParentAction(blSum, dispersal, geographic, branch),
                                      observer(obs))
                                      
                                      {}
                                      
            VisitAction visitNode(T* n)
            {
                obs.beforePropagation(n);
                
                VisitAction v = PropagateFromParentAction::visitNode(n);
                
                obs.afterPropagation(n);
                
                return v;
            }
                                      
        private:
            
            Domain::BranchLength branchLengthSum;
            Weight geographicFactorWeight;
            Weight branchLenghtFactorWeight;
            const Locations::DistanceVector& dispersalVector;
    };*/
}


#endif
