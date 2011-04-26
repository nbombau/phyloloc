#ifndef NEWICK_FILE_H
#define NEWICK_FILE_H

#include <string>
#include <memory>
#include "../../../Domain/ITree.h"
#include "../../../Domain/ListIterator.h"
#include "newick.h"
#include "tree.h"
#include <sys/stat.h>
#include <sys/mman.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>

namespace Parser{

    template <class T> 
    class NewickParser
    {
    public:
        
        void loadNewickFile(const std::string fname,Domain::ITree<T>*phyloTree)
        {	
            const int filedes = open(fname.c_str(), 0, 0); // FIXME: not exception safe
            struct stat file_stat;
            fstat(filedes, &file_stat);
            const size_t len = file_stat.st_size;
            const int prot = PROT_READ;
            const int flags = MAP_PRIVATE;
            const off_t off = 0;

            // FIXME: There is no error handling here!
            char *beg = static_cast<char *>(mmap(0, len, prot, flags, filedes, off));
            char *end = beg + len;

            std::auto_ptr<Tree> tree(parse_newick(beg, end));

            convertTree(tree.get(),tree.get()->root(),phyloTree->getRoot());
                
            munmap(beg, len);
            close(filedes);

        }
        
        void saveNewickFile(const std::string fname,Domain::ITree<T>*phyloTree)
        {
            std::ofstream os(fname.c_str());
            saveTree(phyloTree->getRoot(), os);
            os.close();
        }

    private:
        
        void saveTree(T *node,std::ostream& os)
        {
                    
            if (node->isLeaf())
            {
                os << node->getName();
            }
            else
            {
                os << '(';
                Domain::ListIterator<T>* iter = node->getChildrenIterator();
                                
                while (!iter->end())
                {
                    saveTree(&iter->get(),os);
                               
                    iter->next();
                    
                    if (!iter->end())
                    {
                        os << ',';
                    }
                }
                delete iter;
                os << ')';

            }
            os << ':' << node->getBranchLength();
        }
        
        void convertTree(Tree *tree,int node, T *phyloNode)
        {
            
            int left = tree->left_child(node);
            int right = tree->right_child(node);
            if (tree->is_leaf(node))
            {
                phyloNode->setName(tree->label(node));
            }
            else if (tree->is_inner(node))
            {
                    // inner node
                T*phyloLeft = phyloNode->addChild();
                convertTree(tree,left, phyloLeft);
                    
                T*phyloRight = phyloNode->addChild();
                convertTree(tree,right, phyloRight);
                        
            }
            else
                assert(!"Inconsistent tree!");
                
            phyloNode->setBranchLength(tree->length_to_parent(node));
        }

    };
}

#endif