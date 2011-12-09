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
