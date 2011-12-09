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

#ifndef SEARCHNODE_H
#define SEARCHNODE_H

#include "Domain/LocationManager.h"
#include "Phylopp/Traversal/Traverser.h"
#include "Phylopp/Traversal/NodeVisitor.h"


using namespace Traversal;

namespace Searching
{
template <class T>
struct IsLeafPredicate
{
    bool operator()(T* node) const
    {
        return node->isLeaf();
    }
};

template <class T>
class SelectNodeAction
{
public:
    SelectNodeAction(const std::string& searchString, const Locations::LocationManager locationManager)
    {
        regExp = searchString;
        this->locationManager = locationManager;
    }

    VisitAction visitNode(T* n)
    {
        Location location = locationManager.getLocation(n->getName());
        if (!location.empty() && location.find(regExp, 0) != std::string::npos)
        {
            n->setSelected(true);
            n->update();
        }
        return ContinueTraversing;
    }
private:
    std::string regExp;
    Locations::LocationManager locationManager;
};


template <class T>
class SearchNode : public T
{
public:
    void setRoot(T* root)
    {
        node = root;
    }

    void search(const std::string& expression, Locations::LocationManager locationManager)
    {
        Traverser<T, SelectNodeAction<T> , IsLeafPredicate<T> > t;
        SelectNodeAction<T> a(expression, locationManager);

        t.traverseDescendants(node, a);
    }
private:
    T* node;
};

}

#endif
