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
    
    FilesInfo info = FilesInfo("tmp.nwk","places.dat");
    
    ITreeCollection<GuiNode> treeCollection = ITreeCollection<GuiNode>();
    fileDataSource->load(info,treeCollection);
    
    ListIterator< ITree<GuiNode> > *iter = treeCollection.getIterator();
    
    while(!iter->end())
    {
        printTree(iter->get());
        iter->next();
    }
    delete iter;

    info = FilesInfo("tmp2.nwk","");
    fileDataSource->save(treeCollection,info);
       
    delete fileDataSource;
    
    return 0;
}

void printTree(ITree<GuiNode> tree)
{
    printNode(tree.getRoot());
    cout << '\n';
}

void printNode(GuiNode *node)
{
    if (!node->isLeaf())
    {
        cout << '(';
        ListIterator<GuiNode>* iter = node->getChildrenIterator();

        while (!iter->end())
        {
            printNode(&iter->get());

            iter->next();

            if (!iter->end())
            {
                cout << ',';
            }
        }
        delete iter;
        cout << ')';

    }
    cout << node->getName() << ':' << node->getBranchLength() << "|" << node->getLocation();
}
