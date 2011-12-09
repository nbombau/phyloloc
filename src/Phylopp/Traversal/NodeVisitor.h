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

#ifndef NODEVISITOR_H
#define NODEVISITOR_H

enum VisitAction
{
    ContinueTraversing,
    StopTraversing
};

template <class Action, class Predicate, class Node>
class NodeVisitor
{
    Action& action;
    Predicate predicate;

public:
    NodeVisitor(Action& a) :
        action(a)
    {}

    VisitAction visit(Node* n)
    {
        if (predicate(n))
            return action.visitNode(n);
        else
            return ContinueTraversing;
    }
};

#endif
