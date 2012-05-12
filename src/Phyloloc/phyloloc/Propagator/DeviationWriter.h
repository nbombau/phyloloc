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

#ifndef DEVIATION_WRITER_H
#define DEVIATION_WRITER_H

namespace Propagation
{
//TODO: Create DeviationWriter.cpp and write implementations in that file
class DeviationWriter
{
public:
    DeviationWriter(const std::string& filename)
    {
        //TODO: Open file and save offstream for further writes
    }

    ~DeviationWriter()
    {
        //TODO: Close file
    }

    write(const std::string& treeName, const NodeName& nodeName, unsigned int iteration,
          ProbabilitiesConstIterator begin, ProbabilitiesConstIterator end)
    {
        //TODO: Write a single line to the stream, in the following format
        //   Treename, Nodename, iteration, begin, begin + 1, begin + 2....end
        //for example
        // Tree1, Node1, 3, 0.2, 0.23, 0.30, 0.28, 0.02
    }
};
}

#endif
