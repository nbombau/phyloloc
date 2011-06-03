
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
    using namespace std;
    
    typedef MockNode<Domain::BaseAspect> TestNode;
    typedef std::map<std::string, std::string> LocationsMap;

    
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
        
        void loadTreeFromFile(std::string treesFile,std::string placesFile,ITreeCollection<TestNode>& trees)
        {
            FilesInfo info(treesFile,placesFile);
            fileDataSource.load(info,trees);
        }
        
        void saveTreeToFile(std::string treesFile,ITreeCollection<TestNode>& trees)
        {
            FilesInfo info(treesFile,"");
            fileDataSource.save(trees,info);
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
        
        static bool compareLocations(ITreeCollection<TestNode>& trees, LocationsMap& map)
        {
            bool ret(true);
            
            ListIterator< ITree<TestNode> > *treesIterator = trees.getIterator();
 
            while (ret && !treesIterator->end())
            {
                ITree<TestNode>* tree = treesIterator->get();
                ret = compareNodeLocations(tree->getRoot(),map);
                treesIterator->next();
            }
            
            delete treesIterator;
            
            return ret;
            
        }
        
    private:
        
        static bool compareNodeLocations (const TestNode* node1,LocationsMap& map)
        {
            bool ret = node1->getLocation()==map[node1->getName()];
                       
            EXPECT_TRUE(ret) << "Node location: " << node1->getLocation() << " - Expected: " << map[node1->getName()];
          
            if (ret)
            {
                ListIterator<TestNode> *iterNode = node1->getChildrenIterator();

                while (ret && !iterNode->end())
                {
                    ret = compareNodeLocations(iterNode->get(),map);
                    iterNode->next();
                }
                      
                delete iterNode;
            }
        
            return ret;
               
        }
        static bool compareNodes (const TestNode* node1,const TestNode* node2)
        {
            
            bool ret = node1->getName()==node2->getName() &&
                       node1->getBranchLength()-node2->getBranchLength() < epsilon &&
                       node1->getLocation()==node2->getLocation();
                       
                       
            EXPECT_TRUE(ret) << "n1: " << node1->getName()<< ":" << node1->getBranchLength() 
                << " - n2: " << node2->getName()<< ":" << node2->getBranchLength();
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
                        ret = compareNodes(iterNode1->get(),iterNode2->get());
                        iterNode1->next();
                        iterNode2->next();
                    }
                }
               
                delete iterNode1;
                delete iterNode2;
            }
        
            return ret;
            
        }
        
        static bool compareTrees(ITree<TestNode>* tree1, ITree<TestNode>* tree2)
        {
            bool ret = compareNodes(tree1->getRoot(),tree2->getRoot()); 
            EXPECT_TRUE(ret);
            
            return ret;
        }
    };
    
                                
    TEST_F(FileDataSourceTest, loadTest1) 
    {

        ITreeCollection<TestNode> myTrees;
        loadTree1(myTrees.addTree());

        ITreeCollection<TestNode> trees;
        loadTreeFromFile("TestTrees/tree1.nwk","TestTrees/trees.dat",trees);
        
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    }
    
    TEST_F(FileDataSourceTest, loadTest2) 
    {
        ITreeCollection<TestNode> myTrees;
        loadTree2(myTrees.addTree());
        
        ITreeCollection<TestNode> trees;
        loadTreeFromFile("TestTrees/tree2.nwk","TestTrees/trees.dat",trees);
        
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    }
    
    TEST_F(FileDataSourceTest, loadTest3) 
    {
        ITreeCollection<TestNode> myTrees;
        loadTree3(myTrees.addTree());
        
        ITreeCollection<TestNode> trees;
        loadTreeFromFile("TestTrees/tree3.nwk","TestTrees/trees.dat",trees);
        
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    }
    
    TEST_F(FileDataSourceTest, loadTest4) 
    {
        ITreeCollection<TestNode> myTrees;
        loadTree4(myTrees.addTree());
        
        ITreeCollection<TestNode> trees;
        loadTreeFromFile("TestTrees/tree4.nwk","TestTrees/trees.dat",trees);
        
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    }
    
    TEST_F(FileDataSourceTest, loadTest5) 
    {
        ITreeCollection<TestNode> myTrees;
        loadTree5(myTrees.addTree());
        
        ITreeCollection<TestNode> trees;
        loadTreeFromFile("TestTrees/tree5.nwk","TestTrees/trees.dat",trees);
        
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    }
   
    TEST_F(FileDataSourceTest, loadTest6) 
    {
        ITreeCollection<TestNode> myTrees;
        loadTree6(myTrees.addTree());
        
        ITreeCollection<TestNode> trees;
        loadTreeFromFile("TestTrees/tree6.nwk","TestTrees/trees.dat",trees);
        
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    }
    
    TEST_F(FileDataSourceTest, loadTest7) 
    {
        ITreeCollection<TestNode> myTrees;
        loadTree7(myTrees.addTree());
        
        ITreeCollection<TestNode> trees;
        loadTreeFromFile("TestTrees/tree7.nwk","TestTrees/trees.dat",trees);
        
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    }
    
    TEST_F(FileDataSourceTest, loadTest8) 
    {
        ITreeCollection<TestNode> myTrees;
        loadTree8(myTrees.addTree());
        
        ITreeCollection<TestNode> trees;
        loadTreeFromFile("TestTrees/tree8.nwk","TestTrees/trees.dat",trees);
        
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    }
    

    TEST_F(FileDataSourceTest, loadTest9) 
    {
        ITreeCollection<TestNode> myTrees;
        loadTree1(myTrees.addTree());
        loadTree2(myTrees.addTree());
        loadTree3(myTrees.addTree());
        loadTree4(myTrees.addTree());
        loadTree5(myTrees.addTree());
        loadTree6(myTrees.addTree());
        loadTree7(myTrees.addTree());
        loadTree8(myTrees.addTree());
      
        ITreeCollection<TestNode> trees;
        loadTreeFromFile("TestTrees/tree1.nwk","TestTrees/trees.dat",trees);
        loadTreeFromFile("TestTrees/tree2.nwk","TestTrees/trees.dat",trees);
        loadTreeFromFile("TestTrees/tree3.nwk","TestTrees/trees.dat",trees);
        loadTreeFromFile("TestTrees/tree4.nwk","TestTrees/trees.dat",trees);
        loadTreeFromFile("TestTrees/tree5.nwk","TestTrees/trees.dat",trees);
        loadTreeFromFile("TestTrees/tree6.nwk","TestTrees/trees.dat",trees);
        loadTreeFromFile("TestTrees/tree7.nwk","TestTrees/trees.dat",trees);
        loadTreeFromFile("TestTrees/tree8.nwk","TestTrees/trees.dat",trees);
      
        EXPECT_TRUE(compareTreeCollections(myTrees,trees));
    } 
  
    TEST_F(FileDataSourceTest, saveTest1) 
    {
        ITreeCollection<TestNode> trees;
        loadTree1(trees.addTree());
        
        saveTreeToFile("TestTrees/outTree.nwk",trees);
        
        std::ifstream f("TestTrees/outTree.nwk");
        std::string line;
        getline(f, line);
                
        EXPECT_EQ("(:0,:0,(:0,:0):0):0;",line);
    }      
   
    TEST_F(FileDataSourceTest, saveTest2) 
    {
        ITreeCollection<TestNode> trees;
        loadTree1(trees.addTree());
        loadTree2(trees.addTree());
        loadTree3(trees.addTree());
        loadTree4(trees.addTree());
        loadTree5(trees.addTree());
        loadTree6(trees.addTree());
        loadTree7(trees.addTree());
        loadTree8(trees.addTree());
        
        saveTreeToFile("TestTrees/outTree.nwk",trees);
        
        std::ifstream f("TestTrees/outTree.nwk");
        std::string line,tree_str;
       
        while (getline(f, line))
            tree_str += line;
            
        std::string expected_str;
        
        expected_str.append("(:0,:0,(:0,:0):0):0;");
        expected_str.append("(A:0,B:0,(C:0,D:0):0):0;");
        expected_str.append("(A:0,B:0,(C:0,D:0)E:0)F:0;");
        expected_str.append("(:0.1,:0.2,(:0.3,:0.4):0.5):0;");
        expected_str.append("(:0.1,:0.2,(:0.3,:0.4):0.5):0;");
        expected_str.append("(A:0.1,B:0.2,(C:0.3,D:0.4):0.5):0;");
        expected_str.append("(A:0.1,B:0.2,(C:0.3,D:0.4)E:0.5)F:0;");
        expected_str.append("((B:0.2,(C:0.3,D:0.4)E:0.5)F:0.1)A:0;");
                                      
        EXPECT_EQ(expected_str,tree_str);
    }

    // Empty file. Three with no places loaded.
    TEST_F(FileDataSourceTest, loadLocations1) 
    {        
        ITreeCollection<TestNode> trees;
        loadTreeFromFile("TestTrees/fullTree.nwk","TestTrees/locations1.dat",trees);
        LocationsMap map;
        
        EXPECT_TRUE(compareLocations(trees,map));
    } 

    // Single location.
    TEST_F(FileDataSourceTest, loadLocations2) 
    {        
        ITreeCollection<TestNode> trees;
        loadTreeFromFile("TestTrees/fullTree.nwk","TestTrees/locations2.dat",trees);

        LocationsMap map;
        map["a"]="placeA";
        EXPECT_TRUE(compareLocations(trees,map));
    }

    // Correctly formed file, with a location per node
    TEST_F(FileDataSourceTest, loadLocations3) 
    {        
        ITreeCollection<TestNode> trees;
        loadTreeFromFile("TestTrees/fullTree.nwk","TestTrees/locations3.dat",trees);

        LocationsMap map;
        map["a"]="placeA";
        map["b"]="placeB";
        map["c"]="placeC";
        map["d"]="placeD";
        map["e"]="placeE";
        map["f"]="placeF";
    
        EXPECT_TRUE(compareLocations(trees,map));
    }

    // Multiple locations for a node
    TEST_F(FileDataSourceTest, loadLocations4) 
    {        
        ITreeCollection<TestNode> trees;
        loadTreeFromFile("TestTrees/fullTree.nwk","TestTrees/locations4.dat",trees);

        LocationsMap map;
        map["a"]="placeA2";
        
        EXPECT_TRUE(compareLocations(trees,map));
    } 

    // More associations node/location than nodes in the tree
    TEST_F(FileDataSourceTest, loadLocations5) 
    {        
        ITreeCollection<TestNode> trees;
        loadTreeFromFile("TestTrees/fullTree.nwk","TestTrees/locations5.dat",trees);

        LocationsMap map;
        map["a"]="place";
        map["b"]="place";
        map["c"]="place";
        map["d"]="place";
        map["e"]="place";
        map["f"]="place";
        map["g"]="place";
        map["h"]="place";
        map["i"]="place";
        map["j"]="place";
        map["k"]="place";
        map["l"]="place";
        map["m"]="place";
        map["n"]="place";
        map["i"]="place";
        map["j"]="place";

        EXPECT_TRUE(compareLocations(trees,map));
    } 

    // Try to load a malformed file
    TEST_F(FileDataSourceTest, loadLocations6) 
    {        
        ITreeCollection<TestNode> trees;

        //TODO: Validate a MalformedFile exception when loading locations6.dat
        EXPECT_TRUE(true);
    } 

    // Try to load non existent file
    TEST_F(FileDataSourceTest, loadLocations7) 
    {        
        ITreeCollection<TestNode> trees;
        
        //TODO: Validate a FileNotFound exception when loading a non existent file
        EXPECT_TRUE(true);
    } 
}
