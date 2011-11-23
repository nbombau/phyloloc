#ifndef MACRO_CONSENSOR_OBSERVER_H
#define MACRO_CONSENSOR_OBSERVER_H

#include "bitset.h"
#include "IConsensorObserver.h"

namespace Consensus
{
/**
 * Class: MacroConsensorObserver
 * ----------------------
 * Description: Macro observer to be used when multiple consensor
 * observers are needed.
 * Type Parameter T: T is the underlying node class
 */
//TODO: DO
/* template <class T>
 class MacroConsensorObserver : public IConsensorObserver<T>
 {
 private:

     std::vector<IConsensorObserver>

 public:


     virtual void onStart(const ITreeCollection<Node>& trees)
     {}

     /**
      * Method: notifyInclude
      * ---------------
      * Description: Notifies when a node is included in the consensed tree.
      * @param node node that has been included in the consensed tree
      */
/*virtual void onInclude(Node* node, const bitset& cluster)
{

}

/**
 * Method: notifyExclude
 * ---------------
 * Description: Notifies when a node is excluded in the consensed tree.
 * @param node node that has been excluded in the consensed tree
 */
/* virtual void onExclude(Node* node, const bitset& cluster)
 {

 }

 virtual void onEnd(const ITree<Node>& consensed)
 {

 }*/

};
}