#ifndef FILESINFO_H
#define FILESINFO_H

//#include <string>
namespace DataSource
{
    using namespace std;
    class FilesInfo
    {
    public:
        string getTreesFilePath() const
        {
            return treesFilePath;
        }
        
        string getLocationsFilePath() const
        {
            return locationsFilePath;
        }
        
        void setTreesFilePath(const string treesFilePath)
        {
            this->treesFilePath=treesFilePath;
        }
        
        void setLocationsFilePath(const string locationsFilePath)
        {
            this->locationsFilePath=locationsFilePath;
        }

    private:
        string treesFilePath;
        string locationsFilePath;
    };
    
}

#endif