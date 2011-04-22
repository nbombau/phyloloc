.SILENT:

CC = g++
CC_OP = -pedantic -Wall -Wextra -ansi -o
CC_OP_DEBUG = -pedantic -Wall -Wextra -ansi -g -o
DEST_NAME = phylo
GUI_SOURCE = PhyloGUI
PHYLOPP_SOURCE = Phylopp
PHYLOLOC_SOURCE = Phyloloc
MAIN_SOURCE = Main
DOMAIN_SOURCE = Domain

help:
	@-echo ""
	@-echo "- Use make install to compile the proyect."
	@-echo "- Use make debug to compile the proyect with debugging capabilities."
	@-echo ""
	
debug:
	@-echo ""
	@-echo "Compiling proyect with debugging capabilities..."
	@-echo ""
	$(CC) $(CC_OP_DEBUG) $(DEST_NAME) $(MAIN_SOURCE)/Console.cpp $(PHYLOPP_SOURCE)/Traversal/Traverser.cpp
	
install:
	@-echo ""
	@-echo "Compiling proyect..."
	@-echo ""
	$(CC) $(CC_OP) $(DEST_NAME) $(MAIN_SOURCE)/Console.cpp