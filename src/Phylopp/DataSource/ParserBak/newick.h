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

#ifndef NEWICK_HH_INCLUDED
#define NEWICK_HH_INCLUDED

#include <string>
#include <memory>


namespace Parser
{

// forward decl.
class Tree;

/**
 * Parse a string in Newick format into a tree.
 *
 * \param str   The string to be parsed.
 * \returns A tree corresponding to the string, or 0 in case of errors.
 */
std::auto_ptr<Tree> parse_newick(const std::string& str);

/**
 * Parse a string in Newick format into a tree.
 *
 * \param beg   Iterator to the beginning of the string.
 * \param end   Iterator to the end of the string.
 * \returns A tree corresponding to the string, or 0 in case of errors.
 */
std::auto_ptr<Tree> parse_newick(const char* beg, const char* end);
}

#endif
