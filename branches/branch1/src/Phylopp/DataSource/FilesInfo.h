#ifndef FILESINFO_H
#define FILESINFO_H

#include <string>

namespace DataSource
{
class FilesInfo
{
public:

    FilesInfo(const std::string& treesFilePath, const std::string& locationsFilePath, const std::string& distancesFilePath)
    {
        this->treesFilePath = treesFilePath;
        this->locationsFilePath = locationsFilePath;
        this->distancesFilePath = distancesFilePath;
    }

    std::string getTreesFilePath() const
    {
        return treesFilePath;
    }

    std::string getLocationsFilePath() const
    {
        return locationsFilePath;
    }

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
