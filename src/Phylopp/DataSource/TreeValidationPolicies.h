/*
    DefaultValidationPolicy: a class that defines policies for trees data validation

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

#ifndef TREE_VALIDATION_POLICIES_H
#define TREE_VALIDATION_POLICIES_H

class DefaultValidationPolicy
{
public:
    template <class T>
    bool validate(const T* /*node*/) const
    {
        return true;
    }
};

class ForbidMissinbgDataPolicy
{
public:
    template <class T>
    bool validate(const T* node) const
    {
        return mili::implies(node->isLeaf(), !node->getName().empty());
    }
};

#endif
