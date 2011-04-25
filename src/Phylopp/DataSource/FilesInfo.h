#ifndef FILESINFO_H
#define FILESINFO_H

#include <string>
namespace DataSource
{
    class FilesInfo
    {
    public:
        
        FilesInfo(const std::string treesFilePath,const std::string locationsFilePath)
        {
            this->treesFilePath=treesFilePath;
            this->locationsFilePath=locationsFilePath;
        }
        
        std::string getTreesFilePath() const
        {
            return treesFilePath;
        }
        
        std::string getLocationsFilePath() const
        {
            return locationsFilePath;
        }
        
    private:
        std::string treesFilePath;
        std::string locationsFilePath;
    };
    
}

#endif