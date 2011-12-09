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

#ifndef STRICT_CONSENSOR_H
#define STRICT_CONSENSOR_H

#include "Phylopp/Consensor/IConsensorObserver.h"
#include "Phylopp/Consensor/StrictConsensor.h"

namespace Consensus
{
template <class Node>
class StatisticStrictConsensor : StrictConsensor<Node>
{
public:

    virtual ITree<Node> consensus(ITreeCollection<Node> trees, IConsensorObserver<Node> observer)
    {
        ITree<Node> t = consensus(trees, observer);

        //iterate through t assigning statistics
    }
};

}
