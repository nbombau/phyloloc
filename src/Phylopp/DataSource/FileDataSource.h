#ifndef FILEDATASOURCE_H
#define FILEDATASOURCE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <map>

#include "IDataSourceStrategy.h"
#include "FilesInfo.h"
#include "Domain/ITreeCollection.h"
#include "Domain/ITree.h"
#include "Domain/ListIterator.h"

#include "Parser/newick_file.h"

#define FILE_LOCATION_PARSER_MAX_LINE 256

using namespace std;

namespace DataSource
{
    
    template <class T>
    class FileDataSource : public IDataSourceStrategy<T, FilesInfo>
    {
    private:
        /**
         * Method: loadData
         * --------------------
         * Description: Loads a set of informations associated with
         * nodes into a map from a file.
         * @param file the name of the file to parse
         * @param bag a map with node names as keys and string as values
         * @returns false if the file is not properly formatted
         */
        bool loadData(const string& file, DataBag& bag)
        {
            ifstream f(file.c_str());
            bool ret(true);
            
            if (f)
            {
                stringstream* ss;
                NodeName name;
                
                char line[FILE_LOCATION_PARSER_MAX_LINE];
                char *token1;
                char *token2;       
                
                // Read each line in order to get the information associated to
                // the node. Assumes that each line represents a node.
                while (f.getline(line, FILE_LOCATION_PARSER_MAX_LINE) && ret)
                {
                    token1 = strtok (line, "," );
                    token2 = strtok (NULL, "," ); 
                    if (token1 == NULL || token2 == NULL)
                    {
                        ret = false;
                        cerr << "Malformed data file: line has no data.\n";
                    }
                    else 
                    {
                        name = token1;
                        string value(token2);
                        bag[name] = value;
                    }
                }
            }
            else
            {
                ret = false;
                cerr << "Data file " << file << " not found\n";
            }
            
            return ret;
        }
        
    public:
        void load(FilesInfo& info,Domain::ITreeCollection<T>& trees)
        {
			DataBag bag;
			if (loadData(info.getLocationsFilePath(),bag))
            {
                NewickParser<T> newick;
                newick.loadNewickFile(info.getTreesFilePath(),trees,bag);
            }    
            
        }
        
        void save(Domain::ITreeCollection<T>& trees, FilesInfo& info)
        {
            NewickParser<T> newick;
            
            Domain::ListIterator< Domain::ITree<T> >* iter = trees.getIterator();
            
            while (!iter->end())
            {
                Domain::ITree<T>& tree = iter->get();
                newick.saveNewickFile(info.getTreesFilePath(),&tree);
                iter->next();
            }
            delete iter;
        }
    };
}

#endif
