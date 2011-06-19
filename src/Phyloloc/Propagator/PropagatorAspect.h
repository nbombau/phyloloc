#ifndef PROPAGATOR_H
#define PROPAGATOR_H

#include "Domain/INode.h"
#include "Domain/ListIterator.h"
#include "Domain/LocationAspect.h"
#include "VectorHelper.h"

namespace Propagation
{
    typedef float Probability;
    typedef float Weight;
    typedef unsigned int LocationId;
    typedef std::vector<Probability> LocationProbabilities;
    
    template <class T>
    class PropagatorAspect : public Domain::Node<PropagatorAspect<T> >
    {
    public:
        //TODO: Temporary, wired until integration
        PropagatorAspect() 
        { 
        }
                
        ~PropagatorAspect() {}
        
        void propagateFromChildren(Domain::BranchLength branchLengthSum, 
                                   Locations::DistanceVector& dispersalVector, 
                                   Weight geographicFactorWeight, 
                                   Weight branchLenghtFactorWeight)
        {          
            if(!this->isLeaf())
            {
                Domain::ListIterator<PropagatorAspect<T> > childIter = this->getChildrenIterator();
                
                for(; !childIter.end(); childIter.next())
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
                                 Locations::DistanceVector& dispersalVector, 
                                 Weight geographicFactorWeight, 
                                 Weight branchLenghtFactorWeight)
        {                        
            if(!this->isRoot())
            {
                VectorHelper::vectorialOperation<Probability, std::plus<Probability> >(
                    probabilities, this->getParent()->probabilities, probabilities
                );
                
                VectorHelper::scalarOperation<Probability, std::multiplies<Probability> >(
                    probabilities, 0.5f
                );
                                
                applyCorrectionFactors(branchLengthSum, dispersalVector, geographicFactorWeight, branchLenghtFactorWeight);
            }
        }
        
        void applyCorrectionFactors(Domain::BranchLength branchLengthSum, 
                                       Locations::DistanceVector& dispersalVector, 
                                       Weight geographicFactorWeight, 
                                       Weight branchLenghtFactorWeight)
        {
            //remaining weight
            Weight remainingWeight = 1.0f - geographicFactorWeight - branchLenghtFactorWeight;
            
            //branchlength correction factor
            Domain::BranchLength branchLengthCorrectionFactor = 1.0f - this->getBranchLength() / branchLengthSum;
            
            //store all probabilities' sum in order to normalize later
            Probability sum = 0.0f;
            
            for(unsigned int i = 0; i < probabilities.size(); i++)
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
        
        
    //TODO: temporary until integgration. protected removed for initializing leaf probabilities
    //shall be removed during integration
    //protected:
        
        LocationProbabilities probabilities;        
    };
   
}

#endif
