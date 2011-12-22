#ifndef DEVIATION_PROPAGATOR_OBSERVER_H
#define DEVIATION_PROPAGATOR_OBSERVER_H

#include "DeviationsExporter.h"
#include "Domain/ITree.h"

namespace Propagation
{
    
    template <class T>
    class DeviationPropagatorObserver
    {   
        public:
            
            DeviationPropagatorObserver(DeviationsExporter& w ) : writer(w) { }
            
            void onIterationStart(unsigned int iterationNumber)
            {
                currentIteration = iterationNumber;
            }
            
            void onPropagationStart(Domain::TreeId id)
            {
                currentTreeId = id;
            }
            
            void onNodePropagated(T* node) const 
            { 
                if(node->isLeaf())
                {
                    LocationProbabilities initial;
                    LocationProbabilities deviation;
                    node->getInitialProbabilities(initial);
                    
                    ProbabilitiesConstIterator initialIter;
                    ProbabilitiesConstIterator currentIter;
                    
                    for(initialIter = initial.begin(), currentIter = node->probabilitiesBegin(); 
                    initialIter != initial.end() && currentIter != node->probabilitiesEnd(); 
                    ++initialIter, ++currentIter)
                    {
                        deviation.push_back(fabs(*initialIter - *currentIter));
                    }
                    
                    writer.write(currentTreeId, node->getName(), currentIteration, deviation.begin(), deviation.end());
                }
            }  
            
        private:
            
            unsigned int currentIteration;
            Domain::TreeId currentTreeId;
            DeviationsExporter& writer;
    };
}

#endif