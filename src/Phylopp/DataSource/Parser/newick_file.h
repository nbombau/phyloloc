#ifndef NEWICK_FILE_H
#define NEWICK_FILE_H

#include <string>
#include <memory>
#include "../../../Domain/ITree.h"
#include "newick.hh"
#include "tree.hh"
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>


namespace BiRC { namespace treelib{

    template <class T> 
    class NewickParser
    {
    public:
        
        void parse_newick_file(const char *fname,Domain::ITree<T>*phyloTree)
        {	
            const int filedes = open(fname, 0, 0); // FIXME: not exception safe
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

        //std::auto_ptr<Tree>
        //BiRC::treelib::parse_newick_file(const std::string &fname)
        //{
         //   return parse_newick_file(fname.c_str());
        //}


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
    
}}

#endif