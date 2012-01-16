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

#ifndef PROPAGATOR_H
#define PROPAGATOR_H

#include <fenv.h>
#include "Domain/ITree.h"
#include "Domain/LocationManager.h"
#include "PropagatorAspect.h"
#include "PropagatorAction.h"
#include "Phylopp/Traversal/Traverser.h"

class PropagationExceptionHierarchy {};
typedef mili::GenericException<PropagationExceptionHierarchy> PropagationException;


/**
* InvalidTreeException
* --------------------
* Description: Exception used when the tree is not valid for propagation
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidTreeException,
                               PropagationExceptionHierarchy,
                               "Tree is not valid for propagation");

/**
* InvalidArgumentsException
* --------------------
* Description: Exception used when propagation is invoked with invalid arguments
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidArgumentsException,
                               PropagationExceptionHierarchy,
                               "Invalid arguments. Please check that geographic factor and branch length factor are correct");

/**
* RoundingModeException
* --------------------
* Description: Exception used when setting new round mode is not sucessfull
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(RoundingModeException,
                               PropagationExceptionHierarchy,
                               "Error in propagation. Could not set new rounding mode");

namespace Propagation
{
using namespace Domain;
using namespace Traversal;
using namespace Locations;

typedef std::vector<Domain::BranchLength> BranchLengthVector;

template <class T>
struct DummyObserver
{
    void onPropagationStart(TreeId /*treeId*/) { }
    void onIterationStart(unsigned int /*iterationNumber*/) { }
    void onNodePropagated(T* /*node*/) { }
};

template <class T, class Observer = DummyObserver<T> >
class Propagator
{
public:
    Propagator() {}

    static void propagate(Domain::ITree<T>* tree,
                          unsigned int passesCount,
                          double geographicFactorWeight,
                          double branchLengthFactorWeight,
                          Locations::LocationManager& locationManager,
                          Observer& obs
                         )
    {
        //sets rounded mode towards zero, so that convertion from double to float does not bring errors in propagation arguments
        const int defaultRoundingMode = setRoundingMode(FE_TOWARDZERO);

        try
        {
            propagate(tree, passesCount, Weight(geographicFactorWeight), Weight(branchLengthFactorWeight), locationManager, obs);
        }
        catch (const PropagationException& ex)
        {
            setRoundingMode(defaultRoundingMode);
            throw;
        }

        setRoundingMode(defaultRoundingMode);
    }

    static void propagate(Domain::ITree<T>* tree,
                        unsigned int passesCount,
                        double geographicFactorWeight,
                        double branchLengthFactorWeight,
                        Locations::LocationManager& locationManager
                        )
    {
        Observer o;
        propagate(tree, passesCount, geographicFactorWeight, branchLengthFactorWeight, locationManager, o);
    }

    static void propagate(Domain::ITree<T>* tree,
                          unsigned int passesCount,
                          Weight geographicFactorWeight,
                          Weight branchLengthFactorWeight,
                          Locations::LocationManager& locationManager,
                          Observer& observer
                         )
    {
        assertPropagationPremises(geographicFactorWeight, branchLengthFactorWeight, locationManager);

        BranchLength branchLenghtSum = calculateBranchLengthSum(tree->getRoot());

        const DistanceVector& dispersalVector = locationManager.getDispersionVector();

        PropagateFromChildrenAction<T, Observer> childrenAction(branchLenghtSum,
                dispersalVector,
                geographicFactorWeight,
                branchLengthFactorWeight,
                locationManager,
                observer);
        PropagateFromParentAction<T, Observer> parentAction(branchLenghtSum,
                dispersalVector,
                geographicFactorWeight,
                branchLengthFactorWeight,
                observer);

        observer.onPropagationStart(tree->getId());        
        
        for (unsigned int i = 0; i < passesCount; i++)
        {
            observer.onIterationStart(i);
            
            if (isUpPass(i))
            {
                Traverser<T, PropagateFromChildrenAction<T, Observer>, AlwaysTruePredicate<T> >
                ::traversePostOrder(tree, childrenAction);
            }
            else
            {
                Traverser<T, PropagateFromParentAction<T, Observer>, AlwaysTruePredicate<T> >
                ::traverseDescendants(tree, parentAction);
            }
        }
    }
    
    static void propagate(Domain::ITree<T>* tree,
                          unsigned int passesCount,
                          Weight geographicFactorWeight,
                          Weight branchLengthFactorWeight,
                          Locations::LocationManager& locationManager
                          )
    {
        Observer o;
        propagate(tree, passesCount, geographicFactorWeight, branchLengthFactorWeight, locationManager, o);
    }

private:

    static int setRoundingMode(int roundingMode)
    {
        const int currentRoundingMode = fegetround();

        if (fesetround(roundingMode) != 0)
        {
            throw RoundingModeException();
        }
        return currentRoundingMode;
    }

    static void assertPropagationPremises(const Weight geographicFactorWeight, const Weight branchLengthFactorWeight, LocationManager& locationManager)
    {
        if (!(locationManager.isValid()))
        {
            throw InvalidTreeException();
        }

        if (geographicFactorWeight + branchLengthFactorWeight > 1.0f)
        {
            throw InvalidArgumentsException();
        }
    }

    static bool isUpPass(unsigned int i)
    {
        //even passes are up
        return i % 2 == 0;
    }

    static BranchLength calculateBranchLengthSum(T* node)
    {
        BranchLength ret = 0.0f;

        ret = node->getBranchLength();

        if (!node->isLeaf())
        {
            ListIterator<T, Node> it = node->template getChildrenIterator<T>();
            for (; !it.end(); it.next())
            {
                ret += calculateBranchLengthSum(it.get());
            }
        }
        return ret;
    }


};
}

#endif
