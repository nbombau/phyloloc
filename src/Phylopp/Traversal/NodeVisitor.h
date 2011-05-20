#ifndef NODEVISITOR_H
#define NODEVISITOR_H

enum VisitAction
{
    continueTraversing,
    stopTraversing
};

template <class Action, class Predicate, class Node>
class NodeVisitor
{
    Action& action;
    Predicate predicate;

public:
    NodeVisitor(Action& a) : action(a) {}
    
    VisitAction visit(Node* n)
    {
        if(predicate(n))
            return action.visitNode(n);
        else
            return continueTraversing;
    }
};

#endif
