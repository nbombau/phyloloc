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
                
                initProbabilities(locationManager, probabilities);
                
                //if it's leaf, theres nothing to propagate
                if (!this->isLeaf())
                {           
                    Domain::ListIterator<PropagatorAspect<T>, Domain::Node > childIter = this->template getChildrenIterator<PropagatorAspect<T> >();
                    
                    for (; !childIter.end(); childIter.next())
                    {
                        PropagatorAspect<T>* child = childIter.get();
                        
                        LocationProbabilities correctedProbabilities(child->probabilities);
                        
                        applyCorrectionFactors(branchLengthSum, child->getBranchLength(), dispersalVector, geographicFactorWeight, branchLenghtFactorWeight, correctedProbabilities, false);
                        
                        VectorHelper::vectorialOperation<Probability, std::plus<Probability> >(
                        probabilities, correctedProbabilities, probabilities
                        );
                    }
                    
                    normalize(probabilities);
                    
                    //applyCorrectionFactors(branchLengthSum, dispersalVector, geographicFactorWeight, branchLenghtFactorWeight);
                }
                else
                {
                    initProbabilities(locationManager, initialProbabilities);
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
                    
                    applyCorrectionFactors(branchLengthSum, this->getBranchLength(), dispersalVector, geographicFactorWeight, branchLenghtFactorWeight, probabilities, true);
                }
            }
                
            static void applyCorrectionFactors(Domain::BranchLength branchLengthSum,
                        Domain::BranchLength branchLength,
                        const Locations::DistanceVector& dispersalVector,
                        Weight geographicFactorWeight,
                        Weight branchLenghtFactorWeight,
                        LocationProbabilities& prob,
                        bool normalize)
            {
                //remaining weight
                const Weight remainingWeight = 1.0f - geographicFactorWeight - branchLenghtFactorWeight;
                
                //branchlength correction factor
                const Domain::BranchLength branchLengthCorrectionFactor = 1.0f - branchLength / branchLengthSum;
                
                //store all probabilities' sum in order to normalize later
                Probability sum = 0.0f;
                
                for (unsigned int i = 0; i < prob.size(); i++)
                {
                    Probability current = prob[i];
                    
                    //weight topological factor
                    Probability weighted = current * remainingWeight;
                    
                    //weight branchLength factor
                    weighted += current * branchLengthCorrectionFactor * branchLenghtFactorWeight;
                    
                    //weight geographic factor
                    weighted += current * dispersalVector[i] * geographicFactorWeight;
                    
                    prob[i] = weighted;
                    
                    sum += weighted;
                }
                
                if(normalize)
                    //normalize so that probabilities vector's sum is 1
                    VectorHelper::scalarOperation<Probability, std::multiplies<Probability> >(
                    prob, 1.0f / sum
                    );
            }
            
            static void normalize(LocationProbabilities& prob)
            {
                Probability sum = 0.0;
                
                for(ProbabilitiesConstIterator it = prob.begin(); it != prob.end(); ++it)
                {
                    sum += *it;
                }
                
                VectorHelper::scalarOperation<Probability, std::multiplies<Probability> >(
                prob, (1.0 / sum)
                );
            }
            
            LocationProbabilities::const_iterator probabilitiesBegin() const
            {
                return probabilities.begin();
            }
            
            LocationProbabilities::const_iterator probabilitiesEnd() const
            {
                return probabilities.end();
            }
            
            void getInitialProbabilities(LocationProbabilities& prob) const
            {
                prob.clear();
                
                for(ProbabilitiesConstIterator it = initialProbabilities.begin(); it != initialProbabilities.end(); ++it)
                    prob.push_back(*it);
            }
            
            //TODO: temporary until integgration. protected removed for initializing leaf probabilities
            //shall be removed during integration
            //protected:
            
            LocationProbabilities probabilities;
            LocationProbabilities initialProbabilities;
                                                                                                   
        private:
            
            void initProbabilities(Locations::LocationManager& locationManager, LocationProbabilities& prob)
            {
                size_t locationCount = locationManager.getLocationsCount();
                
                //If probabilities vector not initialized yet, initialize
                //as vector of zeros
                if (prob.empty())
                {
                    if (prob.empty())
                    {
                        prob.resize(locationCount, 0);
                    }
                    else
                    {
                        prob.clear();
                        prob.resize(locationCount, 0);
                    }
                    
                    if (this->isLeaf())
                    {
                        Locations::LocationId id = locationManager.getNameLocationId(this->getName());
                        
                        if (id > 0)
                            prob[id - 1] = 1.0f;
                    }
                }
            }
    };
    
}

#endif
