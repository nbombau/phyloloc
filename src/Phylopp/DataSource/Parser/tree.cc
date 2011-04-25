#include "tree.hh"
#include <ostream>
#include <algorithm>
#include <cassert>

int Parser::Tree::add_node(const std::string &node_label, 
			      int node_left_child, 
			      int node_right_child,
			      double left_length,
			      double right_length)
{
    int new_node = parent_.size();

    // topology...
    parent_.push_back(-1);
    length_to_parent_.push_back(0.0);
    left_child_.push_back(node_left_child);
    right_child_.push_back(node_right_child);
    label_.push_back(node_label);
    

    if (node_left_child >= 0)
	{
	    parent_[node_left_child]  = new_node;
	    length_to_parent_[node_left_child]  = left_length;
	}
    if (node_right_child >= 0)
	{
	    parent_[node_right_child] = new_node;
	    length_to_parent_[node_right_child]  = right_length;
	}

    return new_node;
}


void Parser::Tree::dfs_print(std::ostream &os, int node) const
{
    assert(node >= 0);
    
    int left = left_child_[node];
    int right = right_child_[node];
    if (is_leaf(node))
	{
	    // leaf
	    os << label_[node];
	}
    else if (is_inner(node))
	{
	    // inner node
	    os << '(';
	    dfs_print(os, left);
	    os << ',';
	    dfs_print(os, right);
	    os << ')';
	}
    else
	assert(!"Inconsistent tree!");

    os << ':' << length_to_parent_[node];

}

void Parser::Tree::print(std::ostream &os) const
{
    dfs_print(os, root_);
    os << ';';
}
