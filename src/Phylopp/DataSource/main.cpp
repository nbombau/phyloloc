#import "FileDataSource.h"
#import "IDataSourceStrategy.h"
#import "FilesInfo.h"
#include "../../Domain/ITreeCollection.h"
#include "../../Domain/INode.h"
#include "../../Domain/ListIterator.h"
#include "../../PhyloGUI/GuiAspect.h"

#import <iostream>

using namespace std;
using namespace Domain;
using namespace DataSource;
using namespace PhyloGui;

typedef GuiAspect<BaseAspect> GuiNode;
//typedef Node<BaseAspect> dummyNode;

void printTree(ITree<GuiNode> tree);
void printNode(GuiNode *node);

int main(void)
{
    IDataSourceStrategy<GuiNode,FilesInfo> *fileDataSource = new FileDataSource<GuiNode>();
    
    FilesInfo info = FilesInfo("tmp.nwk","");
    
    ITreeCollection<GuiNode> treeCollection = ITreeCollection<GuiNode>();
    fileDataSource->load(info,treeCollection);
    
    ListIterator< ITree<GuiNode> > *iter = treeCollection.getIterator();
    
    while(!iter->end())
    {
        printTree(iter->get());
        iter->next();
    }
    delete iter;

    return 0;
}

void printTree(ITree<GuiNode> tree)
{
    printNode(tree.getRoot());
}

void printNode(GuiNode *node)
{
    if (node->isLeaf())
    {
        cout << node->getName();
    }
    else
    {
        cout << '(';
        ListIterator<GuiNode>* iter = node->getChildrenIterator();
        
        while (!iter->end())
        {
            printNode(&iter->get());
	    cout << ',';            
            iter->next();
        }
        delete iter;
        cout << ')';

    }
    cout << ':' << node->getBranchLength();
}
