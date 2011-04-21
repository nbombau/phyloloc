// Console.cpp : main project file.

#include <stdlib.h>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <list>
#include "../Domain/ListIterator.h"
#include "../Domain/INode.h"
#include "../Domain/ITree.h"
#include "../Phylopp/Traversal/INodeVisitor.h"
#include "../Phylopp/Traversal/Traverser.h"

using namespace std;
using namespace Domain;
using namespace Traversal;

class PrintfVisitor : public INodeVisitor<PlacesNode>
{
public:
    void visit(PlacesNode* n)
    {
        printf("%s\n", n->getName().c_str());
    }
};

int main()
{
    list<int> enteros;
    enteros.push_back(1);
    enteros.push_back(4);
    enteros.push_back(5);

    PlacesNode* n = new PlacesNode();
    PlacesNode* c = n->addChild();
    c->setName("a2"); 
    c = n->addChild();
    c->setName("a3"); 
    c = n->addChild();
    c->setName("a4"); 
    c = n->addChild();
    c->setName("a5"); 
    c = n->addChild();
    c->setName("a6"); 

    printf("ITERATOR\n");

    ListIterator<PlacesNode>* iter = n->getChildrenIterator();
    int i = 2;
    while(!iter->end())
    {
        printf("nodo: %d \n", i);
        iter->next();
        i++;
    }

    printf("TRAVERSER\n");

    Traverser<PlacesNode, PrintfVisitor>* t = new Traverser<PlacesNode, PrintfVisitor>();
    PrintfVisitor* v = new PrintfVisitor();
    t->traverseDown(n, v);

    printf("Hello World");
    getchar();
    return 0;
}
