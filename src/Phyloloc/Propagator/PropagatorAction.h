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

#ifndef PROPAGATOR_ACTION_H
#define PROPAGATOR_ACTION_H

#include "PropagatorAspect.h"
#include "Propagator.h"
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

template <class T, class Observer>
class PropagateFromChildrenAction
{
public:
    PropagateFromChildrenAction(Domain::BranchLength blSum,
                                const Locations::DistanceVector& dispersal,
                                Weight geographic,
                                Weight branch,
                                Locations::LocationManager& manager,
                                Observer* obs) :
        locationManager(manager),
        branchLengthSum(blSum),
        geographicFactorWeight(geographic),
        branchLenghtFactorWeight(branch),
        dispersalVector(dispersal),
        observer(obs)
    {}

    VisitAction visitNode(T* n)
    {
        n->propagateFromChildren(branchLengthSum, dispersalVector, geographicFactorWeight, branchLenghtFactorWeight, locationManager);
        observer->onNodePropagated(n);
        return ContinueTraversing;
    }

private:
    Locations::LocationManager& locationManager;
    Domain::BranchLength branchLengthSum;
    Weight geographicFactorWeight;
    Weight branchLenghtFactorWeight;
    const Locations::DistanceVector& dispersalVector;
    Observer* observer;

};

template <class T, class Observer>
class PropagateFromParentAction
{
public:
    PropagateFromParentAction(Domain::BranchLength blSum,
                              const Locations::DistanceVector& dispersal,
                              Weight geographic,
                              Weight branch, 
                              Observer* obs) :
        branchLengthSum(blSum),
        geographicFactorWeight(geographic),
        branchLenghtFactorWeight(branch),
        dispersalVector(dispersal),
        observer(obs)
    {}
    
    VisitAction visitNode(T* n)
    {
        n->propagateFromParent(branchLengthSum, dispersalVector, geographicFactorWeight, branchLenghtFactorWeight);
        observer->onNodePropagated(n);
        return ContinueTraversing;
    }

private:

    Domain::BranchLength branchLengthSum;
    Weight geographicFactorWeight;
    Weight branchLenghtFactorWeight;
    const Locations::DistanceVector& dispersalVector;
    Observer* observer;
};

}


#endif
