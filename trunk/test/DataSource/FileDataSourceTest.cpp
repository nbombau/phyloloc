
#include <stddef.h>
#include <gtest/gtest.h>

#include "Domain/ListIterator.h"
#include "Domain/ITree.h"
#include "Domain/ITreeCollection.h"
#include "Domain/INode.h"
#include "Phylopp/DataSource/FileDataSource.h"
#include "Domain/LocationAspect.h"

namespace
{

using namespace DataSource;
using namespace Domain;
using ::testing::Test;
using namespace std;

typedef std::map<std::string, std::string> LocationsMap;

typedef Locations::LocationAspect<Domain::Node> TestNode;

class FileDataSourceTest : public Test
{
protected:

    static const BranchLength epsilon = 0.0001;

    FileDataSource<TestNode> fileDataSource;

    FileDataSourceTest() { }

    virtual ~FileDataSourceTest() { }

    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {
        //This is not necesary since locationmanager is not a singleton anymore
        //LocationAspect<Domain::Node>::clear();
    }


    static inline void setNodeAttrs(TestNode* node, NodeName name, BranchLength length, Location location, Locations::LocationManager& locationManager)
    {
        node->setName(name);
        node->setBranchLength(length);
        locationManager.addLocation(location, name);
    }

    //TODO update tests to support distances file
    void loadTreeFromFile(std::string treesFile, std::string placesFile, std::string distancesFile, ITreeCollection<TestNode>& trees, Locations::LocationManager& locationManager)
    {
        FilesInfo info(treesFile, placesFile, distancesFile);
        fileDataSource.load(info, trees, locationManager, true);
    }

    void saveTreeToFile(std::string treesFile, ITreeCollection<TestNode>& trees)
    {
        FilesInfo info(treesFile, "", "");
        fileDataSource.save(trees, info);
    }

    // (,,(,));    no nodes are named
    static void loadTree1(ITree< TestNode >* tree, Locations::LocationManager& locationManager)
    {

        TestNode* root = tree->getRoot();
        setNodeAttrs(root, "", 0.0f, "", locationManager);

        TestNode* child1 = root->addChild<TestNode>();
        setNodeAttrs(child1, "", 0.0f, "", locationManager);

        TestNode* child2 = root->addChild<TestNode>();
        setNodeAttrs(child2, "", 0.0f, "", locationManager);

        TestNode* child3 = root->addChild<TestNode>();
        setNodeAttrs(child3, "", 0.0f, "", locationManager);

        TestNode* child4 = child3->addChild<TestNode>();
        setNodeAttrs(child4, "", 0.0f, "", locationManager);

        TestNode* child5 = child3->addChild<TestNode>();
        setNodeAttrs(child5, "", 0.0f, "", locationManager);

    }

    // (A,B,(C,D)); leaf nodes are named
    static void loadTree2(ITree< TestNode >* tree, Locations::LocationManager& locationManager)
    {
        TestNode* root = tree->getRoot();
        setNodeAttrs(root, "", 0.0f, "", locationManager);

        TestNode* child1 = root->addChild<TestNode>();
        setNodeAttrs(child1, "A", 0.0f, "", locationManager);

        TestNode* child2 = root->addChild<TestNode>();
        setNodeAttrs(child2, "B", 0.0f, "", locationManager);

        TestNode* child3 = root->addChild<TestNode>();
        setNodeAttrs(child3, "", 0.0f, "", locationManager);

        TestNode* child4 = child3->addChild<TestNode>();
        setNodeAttrs(child4, "C", 0.0f, "", locationManager);

        TestNode* child5 = child3->addChild<TestNode>();
        setNodeAttrs(child5, "D", 0.0f, "", locationManager);

    }

    // (A,B,(C,D)E)F; all nodes are named
    static void loadTree3(ITree< TestNode >* tree, Locations::LocationManager& locationManager)
    {
        TestNode* root = tree->getRoot();
        setNodeAttrs(root, "F", 0.0f, "",locationManager);

        TestNode* child1 = root->addChild<TestNode>();
        setNodeAttrs(child1, "A", 0.0f, "",locationManager);

        TestNode* child2 = root->addChild<TestNode>();
        setNodeAttrs(child2, "B", 0.0f, "",locationManager);

        TestNode* child3 = root->addChild<TestNode>();
        setNodeAttrs(child3, "E", 0.0f, "",locationManager);

        TestNode* child4 = child3->addChild<TestNode>();
        setNodeAttrs(child4, "C", 0.0f, "",locationManager);

        TestNode* child5 = child3->addChild<TestNode>();
        setNodeAttrs(child5, "D", 0.0f, "",locationManager);

    }


    // (:0.1,:0.2,(:0.3,:0.4):0.5);  all but root node have a distance to parent
    static void loadTree4(ITree< TestNode >* tree, Locations::LocationManager& locationManager)
    {
        TestNode* root = tree->getRoot();
        setNodeAttrs(root, "", 0.0f, "",locationManager);

        TestNode* child1 = root->addChild<TestNode>();
        setNodeAttrs(child1, "", 0.1f, "",locationManager);

        TestNode* child2 = root->addChild<TestNode>();
        setNodeAttrs(child2, "", 0.2f, "",locationManager);

        TestNode* child3 = root->addChild<TestNode>();
        setNodeAttrs(child3, "", 0.5f, "",locationManager);

        TestNode* child4 = child3->addChild<TestNode>();
        setNodeAttrs(child4, "", 0.3f, "",locationManager);

        TestNode* child5 = child3->addChild<TestNode>();
        setNodeAttrs(child5, "", 0.4f, "",locationManager);

    }


    // (:0.1,:0.2,(:0.3,:0.4):0.5):0.0;       all have a distance to parent
    static void loadTree5(ITree< TestNode >* tree, Locations::LocationManager& locationManager)
    {
        TestNode* root = tree->getRoot();
        setNodeAttrs(root, "", 0.0f, "",locationManager);

        TestNode* child1 = root->addChild<TestNode>();
        setNodeAttrs(child1, "", 0.1f, "",locationManager);

        TestNode* child2 = root->addChild<TestNode>();
        setNodeAttrs(child2, "", 0.2f, "",locationManager);

        TestNode* child3 = root->addChild<TestNode>();
        setNodeAttrs(child3, "", 0.5f, "",locationManager);

        TestNode* child4 = child3->addChild<TestNode>();
        setNodeAttrs(child4, "", 0.3f, "",locationManager);

        TestNode* child5 = child3->addChild<TestNode>();
        setNodeAttrs(child5, "", 0.4f, "",locationManager);

    }

    // (A:0.1,B:0.2,(C:0.3,D:0.4):0.5);  distances and leaf names
    static void loadTree6(ITree< TestNode >* tree, Locations::LocationManager& locationManager)
    {
        TestNode* root = tree->getRoot();
        setNodeAttrs(root, "", 0.0f, "",locationManager);

        TestNode* child1 = root->addChild<TestNode>();
        setNodeAttrs(child1, "A", 0.1f, "",locationManager);

        TestNode* child2 = root->addChild<TestNode>();
        setNodeAttrs(child2, "B", 0.2f, "",locationManager);

        TestNode* child3 = root->addChild<TestNode>();
        setNodeAttrs(child3, "", 0.5f, "",locationManager);

        TestNode* child4 = child3->addChild<TestNode>();
        setNodeAttrs(child4, "C", 0.3f, "",locationManager);

        TestNode* child5 = child3->addChild<TestNode>();
        setNodeAttrs(child5, "D", 0.4f, "",locationManager);

    }

    // (A:0.1,B:0.2,(C:0.3,D:0.4)E:0.5)F;     distances and all names
    static void loadTree7(ITree< TestNode >* tree, Locations::LocationManager& locationManager)
    {
        TestNode* root = tree->getRoot();
        setNodeAttrs(root, "F", 0.0f, "",locationManager);

        TestNode* child1 = root->addChild<TestNode>();
        setNodeAttrs(child1, "A", 0.1f, "",locationManager);

        TestNode* child2 = root->addChild<TestNode>();
        setNodeAttrs(child2, "B", 0.2f, "",locationManager);

        TestNode* child3 = root->addChild<TestNode>();
        setNodeAttrs(child3, "E", 0.5f, "",locationManager);

        TestNode* child4 = child3->addChild<TestNode>();
        setNodeAttrs(child4, "C", 0.3f, "",locationManager);

        TestNode* child5 = child3->addChild<TestNode>();
        setNodeAttrs(child5, "D", 0.4f, "",locationManager);

    }

    // ((B:0.2,(C:0.3,D:0.4)E:0.5)F:0.1)A;    a tree rooted on a leaf node
    static void loadTree8(ITree< TestNode >* tree, Locations::LocationManager& locationManager)
    {
        TestNode* root = tree->getRoot();
        setNodeAttrs(root, "A", 0.0f, "",locationManager);

        TestNode* child1 = root->addChild<TestNode>();
        setNodeAttrs(child1, "F", 0.1f, "",locationManager);

        TestNode* child2 = child1->addChild<TestNode>();
        setNodeAttrs(child2, "B", 0.2f, "",locationManager);

        TestNode* child3 = child1->addChild<TestNode>();
        setNodeAttrs(child3, "E", 0.5f, "",locationManager);

        TestNode* child4 = child3->addChild<TestNode>();
        setNodeAttrs(child4, "C", 0.3f, "",locationManager);

        TestNode* child5 = child3->addChild<TestNode>();
        setNodeAttrs(child5, "D", 0.4f, "",locationManager);

    }

    static void assertTreeCollectionsEquals(
        const ITreeCollection<TestNode>& expectedTrees, 
        const ITreeCollection<TestNode>& actualTrees, 
        const Locations::LocationManager locationManager)
    {

        ITreeCollection<TestNode>::iterator iterExpected = expectedTrees.getIterator();
        ITreeCollection<TestNode>::iterator iterActual = actualTrees.getIterator();

        ASSERT_EQ(iterExpected.count(), iterActual.count());

        while (!iterExpected.end())
        {
            assertTreesEquals(iterExpected.get(), iterActual.get(), locationManager);
            iterExpected.next();
            iterActual.next();
        }
    }

    static void assertLocationsEquals(const ITreeCollection<TestNode>& actualTrees, const Locations::LocationManager locationManager, LocationsMap& expectedLocationsMap)
    {
        ITreeCollection<TestNode>::iterator treesIterator = actualTrees.getIterator();

        for (; !treesIterator.end(); treesIterator.next())
        {
            ITree<TestNode>* tree = treesIterator.get();
            assertNodeLocationsEquals(tree->getRoot(), locationManager, expectedLocationsMap);
        }
    }
    
    static void assertConsistency (const ITreeCollection<TestNode>& trees, const Locations::LocationManager& locationManager)
    {
        //check trees and locationManager to be empty
        ITreeCollection<TestNode>::iterator treesIterator = trees.getIterator();
        EXPECT_TRUE(treesIterator.end()); 
        EXPECT_TRUE(locationManager.isEmpty());
    }

private:

    static void assertNodeLocationsEquals(const TestNode* actualNode, const Locations::LocationManager locationManager, LocationsMap& expectedLocationsMap)
    {
        ASSERT_EQ(expectedLocationsMap[actualNode->getName()], locationManager.getLocation(actualNode->getName()));

        ListIterator<TestNode, Domain::Node> iterNode = actualNode->getChildrenIterator<TestNode>();

        for (; !iterNode.end() ; iterNode.next())
        {
            assertNodeLocationsEquals(iterNode.get(), locationManager, expectedLocationsMap);
        }
    }

    static void assertNodesEquals(const TestNode* expectedNode, const TestNode* actualNode, const Locations::LocationManager locationManager)
    {

        ASSERT_EQ(expectedNode->getName(), actualNode->getName());

        ASSERT_EQ(expectedNode->getBranchLength(), actualNode->getBranchLength());

        ASSERT_EQ(locationManager.getLocation(expectedNode->getName()), locationManager.getLocation(actualNode->getName()));

        ListIterator<TestNode, Domain::Node> iterExpected = expectedNode->getChildrenIterator<TestNode>();
        ListIterator<TestNode, Domain::Node> iterActual = actualNode->getChildrenIterator<TestNode>();

        ASSERT_EQ(iterExpected.count(), iterActual.count());

        while (!iterExpected.end())
        {
            assertNodesEquals(iterExpected.get(), iterActual.get(), locationManager);
            iterExpected.next();
            iterActual.next();
        }
    }

    static void assertTreesEquals(const ITree<TestNode>* expectedTree, const ITree<TestNode>* actualTree, const Locations::LocationManager locationManager)
    {
        assertNodesEquals(expectedTree->getRoot(), actualTree->getRoot(), locationManager);
    }
};


TEST_F(FileDataSourceTest, loadTest1)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> myTrees;
    loadTree1(myTrees.addTree(), locationManager);

    ITreeCollection<TestNode> trees;
    loadTreeFromFile("TestTrees/tree1.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager);

    assertTreeCollectionsEquals(myTrees, trees, locationManager);
}

TEST_F(FileDataSourceTest, loadTest2)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> myTrees;
    loadTree2(myTrees.addTree(), locationManager);

    ITreeCollection<TestNode> trees;
    loadTreeFromFile("TestTrees/tree2.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager);

    assertTreeCollectionsEquals(myTrees, trees, locationManager);
}

TEST_F(FileDataSourceTest, loadTest3)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> myTrees;
    loadTree3(myTrees.addTree(), locationManager);

    ITreeCollection<TestNode> trees;
    loadTreeFromFile("TestTrees/tree3.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager);

    assertTreeCollectionsEquals(myTrees, trees, locationManager);
}

TEST_F(FileDataSourceTest, loadTest4)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> myTrees;
    loadTree4(myTrees.addTree(), locationManager);

    ITreeCollection<TestNode> trees;
    loadTreeFromFile("TestTrees/tree4.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager);

    assertTreeCollectionsEquals(myTrees, trees, locationManager);
}

TEST_F(FileDataSourceTest, loadTest5)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> myTrees;
    loadTree5(myTrees.addTree(), locationManager);

    ITreeCollection<TestNode> trees;
    loadTreeFromFile("TestTrees/tree5.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager);

    assertTreeCollectionsEquals(myTrees, trees, locationManager);
}

TEST_F(FileDataSourceTest, loadTest6)
{
    Locations::LocationManager locationManager;    

    ITreeCollection<TestNode> myTrees;
    loadTree6(myTrees.addTree(), locationManager);

    ITreeCollection<TestNode> trees;
    loadTreeFromFile("TestTrees/tree6.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager);

    assertTreeCollectionsEquals(myTrees, trees, locationManager);
}

TEST_F(FileDataSourceTest, loadTest7)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> myTrees;
    loadTree7(myTrees.addTree(), locationManager);

    ITreeCollection<TestNode> trees;
    loadTreeFromFile("TestTrees/tree7.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager);

    assertTreeCollectionsEquals(myTrees, trees, locationManager);
}

TEST_F(FileDataSourceTest, loadTest8)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> myTrees;
    loadTree8(myTrees.addTree(), locationManager);

    ITreeCollection<TestNode> trees;
    loadTreeFromFile("TestTrees/tree8.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager);

    assertTreeCollectionsEquals(myTrees, trees, locationManager);
}


TEST_F(FileDataSourceTest, loadTest9)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> myTrees;
    loadTree1(myTrees.addTree(), locationManager);
    loadTree2(myTrees.addTree(), locationManager);
    loadTree3(myTrees.addTree(), locationManager);
    loadTree4(myTrees.addTree(), locationManager);
    loadTree5(myTrees.addTree(), locationManager);
    loadTree6(myTrees.addTree(), locationManager);
    loadTree7(myTrees.addTree(), locationManager);
    loadTree8(myTrees.addTree(), locationManager);

    ITreeCollection<TestNode> trees;
    loadTreeFromFile("TestTrees/tree1.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager);
    loadTreeFromFile("TestTrees/tree2.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager);
    loadTreeFromFile("TestTrees/tree3.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager);
    loadTreeFromFile("TestTrees/tree4.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager);
    loadTreeFromFile("TestTrees/tree5.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager);
    loadTreeFromFile("TestTrees/tree6.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager);
    loadTreeFromFile("TestTrees/tree7.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager);
    loadTreeFromFile("TestTrees/tree8.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager);

    assertTreeCollectionsEquals(myTrees, trees, locationManager);
}

TEST_F(FileDataSourceTest, loadTreesWithNoSeparator)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> trees;
    ASSERT_THROW(loadTreeFromFile("TestTrees/tree9.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager), MissingTreeSeparator);

    assertConsistency(trees, locationManager);
}

TEST_F(FileDataSourceTest, loadMalformedTree)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> trees;
    ASSERT_THROW(loadTreeFromFile("TestTrees/tree10.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager), MalformedExpression);
    
    assertConsistency(trees, locationManager);
}

TEST_F(FileDataSourceTest, loadMalformedTree2)
{
    Locations::LocationManager locationManager;
    ITreeCollection<TestNode> trees;
    
    ASSERT_THROW(loadTreeFromFile("TestTrees/tree13.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager), MalformedExpression);
    
    assertConsistency(trees, locationManager);
}

TEST_F(FileDataSourceTest, invalidBranchLength)
{
    Locations::LocationManager locationManager;
    ITreeCollection<TestNode> trees;
     
    ASSERT_THROW(loadTreeFromFile("TestTrees/tree12.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager), MalformedExpression);
    
    assertConsistency(trees, locationManager);
}

TEST_F(FileDataSourceTest, loadMissingTree)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> trees;
    ASSERT_THROW(loadTreeFromFile("TestTrees/tree11.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist", trees, locationManager), TreeFileNotFound);
    
    assertConsistency(trees, locationManager);
}

TEST_F(FileDataSourceTest, saveTest1)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> trees;
    loadTree1(trees.addTree(), locationManager);

    saveTreeToFile("TestTrees/outTree.nwk", trees);

    std::ifstream f("TestTrees/outTree.nwk");
    std::string line;
    getline(f, line);

    EXPECT_EQ("(:0,:0,(:0,:0):0):0;", line);
}

TEST_F(FileDataSourceTest, saveTest2)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> trees;
    loadTree1(trees.addTree(), locationManager);
    loadTree2(trees.addTree(), locationManager);
    loadTree3(trees.addTree(), locationManager);
    loadTree4(trees.addTree(), locationManager);
    loadTree5(trees.addTree(), locationManager);
    loadTree6(trees.addTree(), locationManager);
    loadTree7(trees.addTree(), locationManager);
    loadTree8(trees.addTree(), locationManager);

    saveTreeToFile("TestTrees/outTree.nwk", trees);

    std::ifstream f("TestTrees/outTree.nwk");
    std::string line, tree_str;

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

    EXPECT_EQ(expected_str, tree_str);
}

// Empty file. Tree with no places loaded.
TEST_F(FileDataSourceTest, loadLocations1)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> trees;
    loadTreeFromFile("TestTrees/fullTree.nwk", "TestTrees/locations1.dat", "TestTrees/distances2.dist", trees, locationManager);
    LocationsMap map;

    assertLocationsEquals(trees, locationManager, map);
}

// Single location.
TEST_F(FileDataSourceTest, loadLocations2)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> trees;
    loadTreeFromFile("TestTrees/fullTree.nwk", "TestTrees/locations2.dat", "TestTrees/distances2.dist", trees, locationManager);

    LocationsMap map;
    map["a"] = "placeA";
    assertLocationsEquals(trees, locationManager, map);
}

// Correctly formed file, with a location per node
TEST_F(FileDataSourceTest, loadLocations3)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> trees;
    loadTreeFromFile("TestTrees/fullTree.nwk", "TestTrees/locations3.dat", "TestTrees/distances3.dist", trees, locationManager);

    LocationsMap map;
    map["a"] = "placeA";
    map["b"] = "placeB";
    map["c"] = "placeC";
    map["d"] = "placeD";
    map["e"] = "placeE";
    map["f"] = "placeF";

    assertLocationsEquals(trees, locationManager, map);
}

// Multiple locations for a node
TEST_F(FileDataSourceTest, loadLocations4)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> trees;
    loadTreeFromFile("TestTrees/fullTree.nwk", "TestTrees/locations4.dat", "TestTrees/distances2.dist", trees, locationManager);

    LocationsMap map;
    map["a"] = "placeA2";

    assertLocationsEquals(trees, locationManager, map);
}

// More associations node/location than nodes in the tree
TEST_F(FileDataSourceTest, loadLocations5)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> trees;
    loadTreeFromFile("TestTrees/fullTree.nwk", "TestTrees/locations5.dat", "TestTrees/distances2.dist", trees, locationManager);

    LocationsMap map;
    map["a"] = "place";
    map["b"] = "place";
    map["c"] = "place";
    map["d"] = "place";
    map["e"] = "place";
    map["f"] = "place";
    map["g"] = "place";
    map["h"] = "place";
    map["i"] = "place";
    map["j"] = "place";
    map["k"] = "place";
    map["l"] = "place";
    map["m"] = "place";
    map["n"] = "place";
    map["i"] = "place";
    map["j"] = "place";

    assertLocationsEquals(trees, locationManager, map);
}

// Try to load a malformed file
TEST_F(FileDataSourceTest, loadLocations6)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> trees;

    ASSERT_THROW(loadTreeFromFile("TestTrees/fullTree.nwk", "TestTrees/locations6.dat", "TestTrees/distances2.dist", trees, locationManager), MalformedFile);

    assertConsistency(trees, locationManager);
}

// Try to load non existent file
TEST_F(FileDataSourceTest, loadLocations7)
{
    Locations::LocationManager locationManager;

    ITreeCollection<TestNode> trees;

    ASSERT_THROW(loadTreeFromFile("TestTrees/fullTree.nwk", "TestTrees/locations7.dat", "TestTrees/distances2.dist", trees, locationManager), DataFileNotFound);

    assertConsistency(trees, locationManager);
}

// Try to load missing data trees with resctrected policy
TEST_F(FileDataSourceTest, loadMissingData)
{
    Locations::LocationManager locationManager;
    ITreeCollection<TestNode> trees;
    
    FilesInfo info("TestTrees/tree1.nwk", "TestTrees/trees.dat", "TestTrees/distances2.dist");
    
    ASSERT_THROW(fileDataSource.load(info, trees, locationManager, false), MissingDataException);
    
    assertConsistency(trees, locationManager);
}

// Try to load non existant distances file
TEST_F(FileDataSourceTest, loadMissingDistances)
{
    Locations::LocationManager locationManager;
    ITreeCollection<TestNode> trees;
    
    ASSERT_THROW(loadTreeFromFile("TestTrees/tree1.nwk", "TestTrees/trees.dat", "TestTrees/nonexistantdistances.dist", trees, locationManager), DistancesFileNotFound);
    assertConsistency(trees, locationManager);
}

// Try to load malformed distances file
TEST_F(FileDataSourceTest, loadMalformedDistancesFile)
{
    Locations::LocationManager locationManager;
    ITreeCollection<TestNode> trees;
    
    ASSERT_THROW(loadTreeFromFile("TestTrees/tree1.nwk", "TestTrees/trees.dat", "TestTrees/malformeddistances.dist", trees, locationManager), MalformedDistancesFile);
    assertConsistency(trees, locationManager);
}

// Try to load malformed distances file
TEST_F(FileDataSourceTest, loadMalformedDistancesFile2)
{
    Locations::LocationManager locationManager;
    ITreeCollection<TestNode> trees;
    
    ASSERT_THROW(loadTreeFromFile("TestTrees/tree1.nwk", "TestTrees/trees.dat", "TestTrees/malformeddistances2.dist", trees, locationManager), MalformedDistancesFile);
    assertConsistency(trees, locationManager);
}

// Try to load distances form inexistant locations 
TEST_F(FileDataSourceTest, loadInexistantLocationDistances)
{
    Locations::LocationManager locationManager;
    ITreeCollection<TestNode> trees;
    
    ASSERT_THROW(loadTreeFromFile("TestTrees/tree1.nwk", "TestTrees/locations1.dat", "TestTrees/distances1.dist", trees, locationManager), InvalidLocation);
    assertConsistency(trees, locationManager);
}

}
