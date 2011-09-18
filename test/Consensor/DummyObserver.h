#ifndef DUMMY_OBSERVER_H
#define DUMMY_OBSERVER_H

template <class Node>
class DummyObserver //: public Consensus::IConsensorObserver<Node>
{
public:
    DummyObserver()
    { }
    void onStart(const Domain::ITreeCollection<Node>& /*trees*/)
    { }
    void onInclude(Node* node, const Consensus::bitset& /*cluster*/)
    { }
    void onExclude(Node* /*node*/, const Consensus::bitset& /*cluster*/)
    { }
    void onEnd(Domain::ITree<Node>& /*consensed*/)
    { }
};

#endif