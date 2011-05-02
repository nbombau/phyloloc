
#include <stddef.h>
#include <gtest/gtest.h>

#include "Domain/ListIterator.h"
#include "Domain/ITree.h"
#include "Domain/ITreeCollection.h"
#include "Domain/INode.h"
#include "Phylopp/DataSource/FileDataSource.h"
#include "../Domain/MockNode.h"


namespace {

    using namespace DataSource;
    using namespace Domain;
    using ::testing::Test;  
    
    typedef MockNode<Domain::BaseAspect> TestNode;

    class FileDataSourceTest : public Test 
    {
    protected:

        static const BranchLength epsilon= 0.0001;
        
        FileDataSource<TestNode> fileDataSource;
         
        FileDataSourceTest() { }

        virtual ~FileDataSourceTest() { }
        
        virtual void SetUp() 
        {
              
        }

        virtual void TearDown() 
        {
        
        }
        
        
        static inline void setNodeAttrs(TestNode* node, NodeName name, BranchLength length, Location location)
        {
            node->setName(name);
            node->setBranchLength(length);
            node->setLocation(location);
        }
        
    
        // (,,(,));    no nodes are named
        static void loadTree1(ITree< TestNode >* tree)
        {
            TestNode* root = tree->getRoot();
            setNodeAttrs(root,"",0.0f,"");        
            
            TestNode* child1 = root->addChild();
            setNodeAttrs(child1,"",0.0f,"");
            
            TestNode* child2 = root->addChild();
            setNodeAttrs(child2,"",0.0f,"");
            
            TestNode* child3 = root->addChild();
            setNodeAttrs(child3,"",0.0f,"");
            
            TestNode* child4 = child3->addChild();
            setNodeAttrs(child4,"",0.0f,"");
            
            TestNode* child5 = child3->addChild();
            setNodeAttrs(child5,"",0.0f,"");
            
        }
            
        // (A,B,(C,D)); leaf nodes are named
        static void loadTree2(ITree< TestNode >* tree)
        {
            TestNode* root = tree->getRoot();
            setNodeAttrs(root,"",0.0f,"");        
            
            TestNode* child1 = root->addChild();
            setNodeAttrs(child1,"A",0.0f,"");
            
            TestNode* child2 = root->addChild();
            setNodeAttrs(child2,"B",0.0f,"");
            
            TestNode* child3 = root->addChild();
            setNodeAttrs(child3,"",0.0f,"");
            
            TestNode* child4 = child3->addChild();
            setNodeAttrs(child4,"C",0.0f,"");
            
            TestNode* child5 = child3->addChild();
            setNodeAttrs(child5,"D",0.0f,"");
            
        }
        
        // (A,B,(C,D)E)F; all nodes are named
        static void loadTree3(ITree< TestNode >* tree)
        {
            TestNode* root = tree->getRoot();
            setNodeAttrs(root,"F",0.0f,"");        
            
            TestNode* child1 = root->addChild();
            setNodeAttrs(child1,"A",0.0f,"");
            
            TestNode* child2 = root->addChild();
            setNodeAttrs(child2,"B",0.0f,"");
            
            TestNode* child3 = root->addChild();
            setNodeAttrs(child3,"E",0.0f,"");
            
            TestNode* child4 = child3->addChild();
            setNodeAttrs(child4,"C",0.0f,"");
            
            TestNode* child5 = child3->addChild();
            setNodeAttrs(child5,"D",0.0f,"");
            
        }   
        
        
        // (:0.1,:0.2,(:0.3,:0.4):0.5);  all but root node have a distance to parent
        static void loadTree4(ITree< TestNode >* tree)
        {
            TestNode* root = tree->getRoot();
            setNodeAttrs(root,"",0.0f,"");        
            
            TestNode* child1 = root->addChild();
            setNodeAttrs(child1,"",0.1f,"");
            
            TestNode* child2 = root->addChild();
            setNodeAttrs(child2,"",0.2f,"");
            
            TestNode* child3 = root->addChild();
            setNodeAttrs(child3,"",0.5f,"");
            
            TestNode* child4 = child3->addChild();
            setNodeAttrs(child4,"",0.3f,"");
            
            TestNode* child5 = child3->addChild();
            setNodeAttrs(child5,"",0.4f,"");
            
        }     
        
        
        // (:0.1,:0.2,(:0.3,:0.4):0.5):0.0;       all have a distance to parent
        static void loadTree5(ITree< TestNode >* tree)
        {
            TestNode* root = tree->getRoot();
            setNodeAttrs(root,"",0.0f,"");        
            
            TestNode* child1 = root->addChild();
            setNodeAttrs(child1,"",0.1f,"");
            
            TestNode* child2 = root->addChild();
            setNodeAttrs(child2,"",0.2f,"");
            
            TestNode* child3 = root->addChild();
            setNodeAttrs(child3,"",0.5f,"");
            
            TestNode* child4 = child3->addChild();
            setNodeAttrs(child4,"",0.3f,"");
            
            TestNode* child5 = child3->addChild();
            setNodeAttrs(child5,"",0.4f,"");
            
        }
        
        // (A:0.1,B:0.2,(C:0.3,D:0.4):0.5);  distances and leaf names
        static void loadTree6(ITree< TestNode >* tree)
        {
            TestNode* root = tree->getRoot();
            setNodeAttrs(root,"",0.0f,"");        
            
            TestNode* child1 = root->addChild();
            setNodeAttrs(child1,"A",0.1f,"");
            
            TestNode* child2 = root->addChild();
            setNodeAttrs(child2,"B",0.2f,"");
            
            TestNode* child3 = root->addChild();
            setNodeAttrs(child3,"",0.5f,"");
            
            TestNode* child4 = child3->addChild();
            setNodeAttrs(child4,"C",0.3f,"");
            
            TestNode* child5 = child3->addChild();
            setNodeAttrs(child5,"D",0.4f,"");
            
        } 
        
        // (A:0.1,B:0.2,(C:0.3,D:0.4)E:0.5)F;     distances and all names
        static void loadTree7(ITree< TestNode >* tree)
        {
            TestNode* root = tree->getRoot();
            setNodeAttrs(root,"F",0.0f,"");        
            
            TestNode* child1 = root->addChild();
            setNodeAttrs(child1,"A",0.1f,"");
            
            TestNode* child2 = root->addChild();
            setNodeAttrs(child2,"B",0.2f,"");
            
            TestNode* child3 = root->addChild();
            setNodeAttrs(child3,"E",0.5f,"");
            
            TestNode* child4 = child3->addChild();
            setNodeAttrs(child4,"C",0.3f,"");
            
            TestNode* child5 = child3->addChild();
            setNodeAttrs(child5,"D",0.4f,"");
            
        }
       
        // ((B:0.2,(C:0.3,D:0.4)E:0.5)F:0.1)A;    a tree rooted on a leaf node
        static void loadTree8(ITree< TestNode >* tree)
        {
            TestNode* root = tree->getRoot();
            setNodeAttrs(root,"A",0.0f,"");        
            
            TestNode* child1 = root->addChild();
            setNodeAttrs(child1,"F",0.1f,"");
            
            TestNode* child2 = child1->addChild();
            setNodeAttrs(child2,"B",0.2f,"");
            
            TestNode* child3 = child1->addChild();
            setNodeAttrs(child3,"E",0.5f,"");
            
            TestNode* child4 = child3->addChild();
            setNodeAttrs(child4,"C",0.3f,"");
            
            TestNode* child5 = child3->addChild();
            setNodeAttrs(child5,"D",0.4f,"");
            
        }
        
        static bool compareTreeCollections(ITreeCollection<TestNode>& trees1, ITreeCollection<TestNode>& trees2)
        {
                 
            ListIterator< ITree<TestNode> > *iter1 = trees1.getIterator();
            ListIterator< ITree<TestNode> > *iter2 = trees2.getIterator();
            
            bool ret = iter1->count()==iter2->count();
            EXPECT_TRUE(ret);
            
            if (ret)
            {
                while (ret && !iter1->end())
                {
                    ret = compareTrees(iter1->get(),iter2->get());
                    iter1->next();
                    iter2->next();
                }
            }
            
            delete iter1;
            delete iter2;
            
            return ret;
            
        }
        
    private:
        static bool compareNodes (const TestNode* node1,const TestNode* node2)
        {
            
            bool ret = node1->getName().compare(node2->getName()) == 0 &&
                       node1->getBranchLength()-node2->getBranchLength() < epsilon &&
                       node1->getLocation().compare(node2->getLocation()) == 0;
                       
                       
            EXPECT_TRUE(ret) << "n1: " << node1->getName()<< ":" << node1->getBranchLength() << " - n2: " << node2->getName()<< ":" << node2->getBranchLength();
            if (ret)
            {
                ListIterator<TestNode> *iterNode1 = node1->getChildrenIterator();
                ListIterator<TestNode> *iterNode2 = node2->getChildrenIterator();
            
                ret = iterNode1->count()==iterNode2->count(); 
                
                EXPECT_TRUE(ret);
               
                if (ret)
                {
                    while (ret && !iterNode1->end())
                    {
                        ret = compareNodes(&iterNode1->get(),&iterNode2->get());
                        iterNode1->next();
                        iterNode2->next();
                    }
                }
               
                delete iterNode1;
                delete iterNode2;
            }
        
            return ret;
            
        }
        
        static bool compareTrees(ITree<TestNode>& tree1, ITree<TestNode>& tree2)
        {
            bool ret = compareNodes(tree1.getRoot(),tree2.getRoot()); 
            EXPECT_TRUE(ret);
            
            return ret;
        }
    };
    
                                
    TEST_F(FileDataSourceTest, loadTest1) 
    {
        ITreeCollection<TestNode> myTrees;
        loadTree1(myTrees.addTree());
        
        FilesInfo info("TestTrees/tree1.nwk","TestTrees/trees.dat");
        ITreeCollection<TestNode> trees;
        fileDataSource.load(info,trees);
        
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    }
    
    TEST_F(FileDataSourceTest, loadTest2) 
    {
        ITreeCollection<TestNode> myTrees;
        loadTree2(myTrees.addTree());
        
        FilesInfo info("TestTrees/tree2.nwk","TestTrees/trees.dat");
        ITreeCollection<TestNode> trees;
        fileDataSource.load(info,trees);
        
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    }
    
    TEST_F(FileDataSourceTest, loadTest3) 
    {
        ITreeCollection<TestNode> myTrees;
        loadTree3(myTrees.addTree());
        
        FilesInfo info("TestTrees/tree3.nwk","TestTrees/trees.dat");
        ITreeCollection<TestNode> trees;
        fileDataSource.load(info,trees);
        
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    }
    
    TEST_F(FileDataSourceTest, loadTest4) 
    {
        ITreeCollection<TestNode> myTrees;
        loadTree4(myTrees.addTree());
        
        FilesInfo info("TestTrees/tree4.nwk","TestTrees/trees.dat");
        ITreeCollection<TestNode> trees;
        fileDataSource.load(info,trees);
        
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    }
    
    TEST_F(FileDataSourceTest, loadTest5) 
    {
        ITreeCollection<TestNode> myTrees;
        loadTree5(myTrees.addTree());
        
        FilesInfo info("TestTrees/tree5.nwk","TestTrees/trees.dat");
        ITreeCollection<TestNode> trees;
        fileDataSource.load(info,trees);
        
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    }
   
    TEST_F(FileDataSourceTest, loadTest6) 
    {
        ITreeCollection<TestNode> myTrees;
        loadTree6(myTrees.addTree());
        
        FilesInfo info("TestTrees/tree6.nwk","TestTrees/trees.dat");
        ITreeCollection<TestNode> trees;
        fileDataSource.load(info,trees);
        
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    }
    
    TEST_F(FileDataSourceTest, loadTest7) 
    {
        ITreeCollection<TestNode> myTrees;
        loadTree7(myTrees.addTree());
        
        FilesInfo info("TestTrees/tree7.nwk","TestTrees/trees.dat");
        ITreeCollection<TestNode> trees;
        fileDataSource.load(info,trees);
        
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    }
    
    TEST_F(FileDataSourceTest, loadTest8) 
    {
        ITreeCollection<TestNode> myTrees;
        loadTree8(myTrees.addTree());
        
        FilesInfo info("TestTrees/tree8.nwk","TestTrees/trees.dat");
        ITreeCollection<TestNode> trees;
        fileDataSource.load(info,trees);
        
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    }
}
