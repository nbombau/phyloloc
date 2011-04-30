#ifndef MOCK_NODE_H
#define MOCK_NODE_H

#include <gmock/gmock.h> 
#include <string>

#include "../../src/Domain/INode.h"

template <class T>
class MockNode : public Domain::Node<MockNode<T> > {
 public:
    /* MOCK_CONST_METHOD0(isRoot,bool());
     MOCK_CONST_METHOD0(isLeaf,bool());*/
     //MOCK_CONST_METHOD0(getParent,T*());
     //MOCK_CONST_METHOD0(getChildrenIterator,ListIterator<T>*());
     //MOCK_CONST_METHOD0(addChild,T*());
    /*MOCK_CONST_METHOD0(getName,std::string());
     MOCK_METHOD1(setName,void(const std::string& n));
     MOCK_CONST_METHOD0(getLocation,std::string());
     MOCK_METHOD1(setLocation,void(const std::string& n));
     MOCK_CONST_METHOD0(getBranchLength,float());
     MOCK_CONST_METHOD1(setBranchLength,void(const float n)); */
     
     bool visited;
     
     MockNode() : visited(false) {}
};

#endif