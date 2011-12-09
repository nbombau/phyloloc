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
#ifndef VECTOR_HELPER_H
#define VECTOR_HELPER_H

#include <vector>
#include <algorithm>
#include <functional>

namespace Propagation
{
//TODO: add more specific methods that use this general methods
class VectorHelper
{
public:
    template <typename T, typename Operation>
    static void vectorialOperation(const std::vector<T>& a,
                                   const std::vector<T>& b,
                                   std::vector<T>& result)
    {
        assert(a.size() == b.size());

        result.reserve(a.size());

        std::transform(a.begin(), a.end(), b.begin(),
                       result.begin(), Operation());
    }

    template <typename T, typename Operation>
    static void scalarOperation(std::vector<T>& a,
                                T scalar)
    {
        std::transform(a.begin(), a.end(), a.begin(),
                       std::bind1st(Operation(), scalar));
    }

};
}

#endif
