#ifndef MOCK_NODE_H
#define MOCK_NODE_H

#include <gmock/gmock.h> 
#include <string>

#include "../../src/Domain/INode.h"

template <class T>
class MockNode : public Domain::Node<MockNode<T> > {
 public:
     
     bool visited;
     
     MockNode() : visited(false) {}
};

typedef MockNode<Domain::BaseAspect> TestNode;

#endif