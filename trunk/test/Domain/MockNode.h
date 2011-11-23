#ifndef MOCK_NODE_H
#define MOCK_NODE_H

#include <gmock/gmock.h> 
#include <string>

#include "../../src/Domain/INode.h"
#include "../../src/Domain/LocationAspect.h"

template <class T>
class MockNode : public T
{
 public:
     
     bool visited;
     
     MockNode() : visited(false) {}
};

typedef MockNode<Domain::Node> TestNode;

#endif
