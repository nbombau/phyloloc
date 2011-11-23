#ifndef NODEVISITOR_H
#define NODEVISITOR_H

enum VisitAction
{
    ContinueTraversing,
    StopTraversing
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
            return ContinueTraversing;
    }
};

#endif
