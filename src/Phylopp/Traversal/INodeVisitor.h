
#ifndef INODEVISITOR_H
#define INODEVISITOR_H

namespace Traversal
{
/**
* Interface: INodeVisitor
* ----------------------
* Description: Interface for node visitors. The client shall implement
* any operation needed on the nodes in their visitor implementations.
* Type Parameter T: T is the node type. Hence, T should implement INode
*/
template <class T>
class INodeVisitor
{
public:
    /**
    * Method: visit
    * -------------
    * Description: Action to perform when visiting a node
    * during a traversal.
    * @param t a node
    */
    virtual void visit(T& t) = 0;
};
}

#endif
