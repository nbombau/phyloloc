#ifndef PROPAGATOR_H
#define PROPAGATOR_H

#include "Domain/INode.h"
#include "Domain/ListIterator.h"
#include "VectorHelper.h"

typedef float Probability;
typedef unsigned int LocationId;
typedef std::vector<Probability> LocationProbabilities;

namespace Propagation
{
    template <class T>
    class PropagatorAspect : public Domain::Node<PropagatorAspect<T> >
    {
    public:
        //TODO: Temporary, wired until integration
        PropagatorAspect() 
        { 
        }
                
        ~PropagatorAspect() {}
        
        void propagateFromChildren()
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
               
            }
        }
        
        void propagateFromParent()
        {                        
            if(!this->isRoot())
            {
                VectorHelper::vectorialOperation<Probability, std::plus<Probability> >(
                    probabilities, this->getParent()->probabilities, probabilities
                );
                
                VectorHelper::scalarOperation<Probability, std::multiplies<Probability> >(
                    probabilities, 0.5f
                );
            }
        }
        
        
    //TODO: temporary until integgration. protected removed for initializing leaf probabilities
    //shall be removed during integration
    //protected:
        
        LocationProbabilities probabilities;
        
    };

}

#endif
