/*
    FilesInfo: class for storing paths to trees, distances and locations files

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

#ifndef FILESINFO_H
#define FILESINFO_H

#include <string>

namespace DataSource
{
class FilesInfo
{
public:

    /**
     * Constructor
     *
     * @param treeFilePath Path to trees file
     * @param locationsFilePath Path to locations file
     * @param distancesFilePath Path to distances file
     *
     */
    FilesInfo(const std::string& treesFilePath, const std::string& locationsFilePath, const std::string& distancesFilePath)
    {
        this->treesFilePath = treesFilePath;
        this->locationsFilePath = locationsFilePath;
        this->distancesFilePath = distancesFilePath;
    }

    /**
     * Get the trees file path
     *
     * @return tree file path
     */
    std::string getTreesFilePath() const
    {
        return treesFilePath;
    }

    /**
     * Get the locations file path
     *
     * @return locations file path
     */
    std::string getLocationsFilePath() const
    {
        return locationsFilePath;
    }

    /**
     * Get the distances file path
     *
     * @return distances file path
     */
    std::string getDistancesFilePath() const
    {
        return distancesFilePath;
    }


private:
    std::string treesFilePath;
    std::string locationsFilePath;
    std::string distancesFilePath;
};
}

#endif
