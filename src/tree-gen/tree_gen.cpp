#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <mili/mili.h>

namespace {
    void produce_random_tree_rec(std::vector<int>::const_iterator beg,
				 std::vector<int>::const_iterator end,
				 std::ostream &os)
    {
        const size_t size = end - beg;
        if (size == 1)
	    os << *beg;
	else
	    {
                Randomizer<unsigned int> rnd(1, size - 1);

                unsigned int split = rnd.get();
		
		std::vector<int>::const_iterator m = beg + split;

		os << '(';
		produce_random_tree_rec(beg, m, os);
		os << ',';
		produce_random_tree_rec(m, end, os);
		os << ')';
	    }
        Randomizer<unsigned int> rnd(1, 5);
        os << ":" << rnd.get();
    }
    
    void produce_random_tree(size_t size, std::ostream &os)
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
    unsigned int size;
    if (argc<2)
    {
        Randomizer<unsigned int> rnd(0, 10000);
        size = rnd.get();
    }
    else{
        from_string(argv[1],size);
    }

    std::ofstream os("tmp.nwk");
    produce_random_tree(size, os);

    return EXIT_SUCCESS;
}
