// Console.cpp : main project file.

#include <stdlib.h>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <list>
#include "../Domain/ListIterator.h"
#include "../PhyloGUI/GuiAspect.h"
#include "../Domain/INode.h"
#include "../Domain/ITreeCollection.h"
#include "../Domain/ITree.h"
#include "../Phylopp/Traversal/INodeVisitor.h"
#include "../Phylopp/Traversal/Traverser.h"

using namespace std;
using namespace Domain;
using namespace Traversal;
using namespace PhyloGui;


typedef GuiAspect<BaseAspect> GuiNode;

class PrintfVisitor : public INodeVisitor<GuiNode>
{
public:
    void visit(GuiNode& n)
    {
        printf("%s\n", n.getName().c_str());
    }
};

int main()
{

    ITreeCollection<GuiAspect> col = ITreeCollection<GuiAspect>();

    FillTree(col);

    printf("GUI ASPECT\n");

    GuiNode n2 = GuiNode();
    GuiNode* c2 = n2.addChild();
    c2->setName("a2"); 
    c2 = n2.addChild();
    c2->setName("a3"); 
    c2 = n2.addChild();
    c2->setName("a4"); 
    c2 = n2.addChild();
    c2->setName("a5"); 
    c2 = n2.addChild();
    c2->setName("a6"); 

    printf("ITERATOR\n");

    ListIterator<GuiNode>* iter2 = n2.getChildrenIterator();
    int i = 2;
    while(!iter2->end())
    {
        printf("nodoGui: %d \n", i);
        iter2->next();
        i++;
    }

    delete iter2;

    printf("TRAVERSER\n");

    Traverser<GuiNode, PrintfVisitor> t = Traverser<GuiNode, PrintfVisitor>();
    PrintfVisitor v = PrintfVisitor();
    t.traverseDown(n2, v);

    printf("Hello World");
    getchar();
    return 0;
}


void FillTree(ITreeCollection<GuiNode>& col)
{
    ITree<GuiNode>* t = col.addTree();
    GuiNode* = t->getRoot();
    
}