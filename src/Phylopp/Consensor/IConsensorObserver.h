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

#ifndef ICONSENSOR_OBSERVER_H
#define ICONSENSOR_OBSERVER_H

#include "bitset.h"
#include "Domain/ITreeCollection.h"

namespace Consensus
{
/**
 * Interface: IConsensorObserver
 * ----------------------
 * Description: Interface for observers that shall be used during the
 * consensor algorithm. The consensors observers shall notify when a node
 * is included or excluded from de resulting consensed tree.
 * Type Parameter T: T is the underlying node class
 */
template <class Node>
class IConsensorObserver
{

public:
    virtual void onStart(const Domain::ITreeCollection<Node>& trees) = 0;

    /**
     * Method: notifyInclude
     * ---------------
     * Description: Notifies when a node is included in the consensed tree.
     * @param node node that has been included in the consensed tree
     */
    virtual void onInclude(const Node* const node, const bitset& cluster) = 0;

    /**
     * Method: notifyExclude
     * ---------------
     * Description: Notifies when a node is excluded in the consensed tree.
     * @param node node that has been excluded in the consensed tree
     */
    virtual void onExclude(const Node* const node, const bitset& cluster) = 0;

    virtual void onEnd(Domain::ITree<Node>* consensed) = 0;

};
}


#endif
