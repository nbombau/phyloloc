/*
    Copyright (C) 2011 Emmanuel Teisaire, Nicolás Bombau, Carlos Castro, Damián Domé, Leonardo Boquillon FuDePAN

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

#ifndef DEVIATIONS_EXPORTER_H
#define DEVIATIONS_EXPORTER_H

#include <string>
#include <vector>
#include <fstream>
#include <mili/mili.h>
#include "PropagatorAspect.h"

namespace Propagation
{

using namespace mili;

class DeviationsExporter
{
public:
    DeviationsExporter(std::string fileName)
    {
        of.open(fileName.c_str());
    }

    void write(Domain::TreeId id, const NodeName& nodeName, unsigned int iteration,
               ProbabilitiesConstIterator begin, ProbabilitiesConstIterator end)
    {
        std::vector<float> v;

        of << id;
        of << ",";
        of << (nodeName + ",");

        v.push_back(static_cast<float>(iteration));

        for (ProbabilitiesConstIterator it = begin; it != end; ++it)
            v.push_back(*it);

        of << v;
        of << std::endl;
    }

private:
    std::ofstream of;

};
}

#endif
