#ifndef PROPAGATOR_H
#define PROPAGATOR_H

#include <fenv.h>
#include "Domain/ITree.h"
#include "Domain/LocationAspect.h"
#include "PropagatorAspect.h"
#include "PropagatorAction.h"
#include "Phylopp/Traversal/Traverser.h"

class PropagationExceptionHierarchy {};
typedef GenericException<PropagationExceptionHierarchy> PropagationException;


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
class Propagator
{
public:
    Propagator() {}

    static void propagate(Domain::ITree<T>* tree,
                          unsigned int passesCount,
                          double geographicFactorWeight,
                          double branchLengthFactorWeight
                         )
    {
        //sets rounded mode towards zero, so that convertion from double to float does not bring errors in propagation arguments
        int defaultRoundingMode = setRoundingMode(FE_TOWARDZERO);

        try
        {
            propagate(tree, passesCount, (Weight)geographicFactorWeight, (Weight)branchLengthFactorWeight);
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
                          Weight geographicFactorWeight,
                          Weight branchLengthFactorWeight
                         )
    {
        assertPropagationPremises(geographicFactorWeight, branchLengthFactorWeight);

        BranchLength branchLenghtSum = calculateBranchLengthSum(tree->getRoot());

        const DistanceVector& dispersalVector = T::getDispersionVector();

        PropagateFromChildrenAction<T> childrenAction(branchLenghtSum,
                dispersalVector,
                geographicFactorWeight,
                branchLengthFactorWeight);
        PropagateFromParentAction<T> parentAction(branchLenghtSum,
                dispersalVector,
                geographicFactorWeight,
                branchLengthFactorWeight);
        for (unsigned int i = 0; i < passesCount; i++)
        {
            if (isUpPass(i))
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

    static int setRoundingMode(int roundingMode)
    {
        int currentRoundingMode = fegetround();

        if (fesetround(roundingMode) != 0)
        {
            throw new RoundingModeException();
        }
        return currentRoundingMode;
    }

    static void assertPropagationPremises(const Weight geographicFactorWeight, const Weight branchLengthFactorWeight)
    {
        if (!(T::isValid()))
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
