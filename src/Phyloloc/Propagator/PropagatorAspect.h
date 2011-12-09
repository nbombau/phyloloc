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

#ifndef PROPAGATORASPECT_H
#define PROPAGATORASPECT_H

#include "Domain/INode.h"
#include "Domain/ListIterator.h"
#include "Domain/LocationManager.h"
#include "VectorHelper.h"

namespace Propagation
{
typedef float Probability;
typedef float Weight;
typedef unsigned int LocationId;
typedef std::vector<Probability> LocationProbabilities;
typedef std::vector<Probability>::const_iterator ProbabilitiesConstIterator;

template <class T>
class PropagatorAspect : public T
{
public:
    PropagatorAspect() {}
    ~PropagatorAspect() {}

    void propagateFromChildren(Domain::BranchLength branchLengthSum,
                               const Locations::DistanceVector& dispersalVector,
                               Weight geographicFactorWeight,
                               Weight branchLenghtFactorWeight,
                               Locations::LocationManager& locationManager)
    {

        initProbabilities(locationManager);

        //if it's leaf, theres nothing to propagate
        if (!this->isLeaf())
        {
            Domain::ListIterator<PropagatorAspect<T>, Domain::Node > childIter = this->template getChildrenIterator<PropagatorAspect<T> >();

            for (; !childIter.end(); childIter.next())
            {
                PropagatorAspect<T>* child = childIter.get();

                VectorHelper::vectorialOperation<Probability, std::plus<Probability> >(
                    probabilities, child->probabilities, probabilities
                );
            }

            VectorHelper::scalarOperation<Probability, std::multiplies<Probability> >(
                probabilities, 1.0f / float(childIter.count())
            );

            applyCorrectionFactors(branchLengthSum, dispersalVector, geographicFactorWeight, branchLenghtFactorWeight);
        }
    }

    void propagateFromParent(Domain::BranchLength branchLengthSum,
                             const Locations::DistanceVector& dispersalVector,
                             Weight geographicFactorWeight,
                             Weight branchLenghtFactorWeight)
    {
        if (!this->isRoot())
        {
            VectorHelper::vectorialOperation<Probability, std::plus<Probability> >(
                probabilities, this->template getParent<PropagatorAspect<T> >()->probabilities, probabilities
            );

            VectorHelper::scalarOperation<Probability, std::multiplies<Probability> >(
                probabilities, 0.5f
            );

            applyCorrectionFactors(branchLengthSum, dispersalVector, geographicFactorWeight, branchLenghtFactorWeight);
        }
    }

    void applyCorrectionFactors(Domain::BranchLength branchLengthSum,
                                const Locations::DistanceVector& dispersalVector,
                                Weight geographicFactorWeight,
                                Weight branchLenghtFactorWeight)
    {
        //remaining weight
        Weight remainingWeight = 1.0f - geographicFactorWeight - branchLenghtFactorWeight;

        //branchlength correction factor
        Domain::BranchLength branchLengthCorrectionFactor = 1.0f - this->getBranchLength() / branchLengthSum;

        //store all probabilities' sum in order to normalize later
        Probability sum = 0.0f;

        for (unsigned int i = 0; i < probabilities.size(); i++)
        {
            Probability current = probabilities[i];

            //weight topological factor
            Probability weighted = current * remainingWeight;

            //weight branchLength factor
            weighted += current * branchLengthCorrectionFactor * branchLenghtFactorWeight;

            //weight geographic factor
            weighted += current * dispersalVector[i] * geographicFactorWeight;

            probabilities[i] = weighted;
            sum += weighted;
        }
        //normalize so that probabilities vector's sum is 1
        VectorHelper::scalarOperation<Probability, std::multiplies<Probability> >(
            probabilities, 1.0f / sum
        );
    }

    LocationProbabilities::const_iterator getProbabilitiesIterator() const
    {
        return probabilities.begin();
    }

    //TODO: temporary until integgration. protected removed for initializing leaf probabilities
    //shall be removed during integration
    //protected:

    LocationProbabilities probabilities;

private:

    void initProbabilities(Locations::LocationManager& locationManager)
    {
        size_t locationCount = locationManager.getLocationsCount();

        //If probabilities vector not initialized yet, initialize
        //as vector of zeros
        if (probabilities.empty())
        {
            if (probabilities.empty())
            {
                probabilities.resize(locationCount, 0);
            }
            else
            {
                probabilities.clear();
                probabilities.resize(locationCount, 0);
            }

            if (this->isLeaf())
            {
                Locations::LocationId id = locationManager.getNameLocationId(this->getName());

                if (id > 0)
                    probabilities[id - 1] = 1.0f;
            }
        }
    }
};

}

#endif
