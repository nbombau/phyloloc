#ifndef NEWICK_FILE_HH_INCLUDED
#define NEWICK_FILE_HH_INCLUDED

#include <string>
#include <memory>
#include "../../../Domain/ITree.h"

// FIXME: There is no errorhandling in these functions!!!

using namespace Domain;

namespace BiRC { namespace treelib {
    // forward decl.
    class Tree;

    /**
     * Parse a string in Newick format from a file.
     *
     * \param fname	Name of the file to parse.
     * \returns	A tree corresponding to the string, or 0 in case of errors.
     */
	template <class T>
    std::auto_ptr<Tree> parse_newick_file(const char *fname,ITree<T>*phyloTree);

    /**
     * Parse a string in Newick format from a file.
     *
     * \param fname	Name of the file to parse.
     * \returns	A tree corresponding to the string, or 0 in case of errors.
     */
    std::auto_ptr<Tree> parse_newick_file(const std::string &fname);
	
	template <class T>
	void convertTree(Tree *tree,int node, T *phyloNode);
}}

#endif
