
#include <iostream>
#include <fstream>
#include <vector>

namespace {
    void produce_random_tree_rec(std::vector<int>::const_iterator beg,
				 std::vector<int>::const_iterator end,
				 std::ostream &os)
    {
	if (end - beg == 1)
	    os << *beg;
	else
	    {
		int size = end - beg;
		int split = rand() % (size-1) + 1;
		
		std::vector<int>::const_iterator m = beg + split;
		
		os << '(';
		produce_random_tree_rec(beg, m, os);
		os << ',';
		produce_random_tree_rec(m, end, os);
		os << ')';
	    }
    }
    
    void produce_random_tree(int size, std::ostream &os)
    {
	std::vector<int> labels(size);
	for (int i = 0; i < size; ++i) 
	    labels[i] = i;
	std::random_shuffle(labels.begin(), labels.end());
	
	produce_random_tree_rec(labels.begin(), labels.end(), os);
	os << ';' << std::endl;
    }
}

int
main(int argc,char * argv[])
{
	
	srand(time(0));
	
    int size;
    if (argc<2)
    {
    	size = rand() % 100000;
    }
    else{
		size = atoi(argv[1]);	
    }

    std::ofstream os("tmp.nwk");
    produce_random_tree(size, os);


    return 0;
}
