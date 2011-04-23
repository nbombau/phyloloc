//#include "Traverser.h"
//TODO: pass traverser methods implementation from header to here
//namespace Traversal
//{
//    template <class T, class V>
//    void Traverser::traverseDown(T* t, V* v)
//    {
//        std::queue<T*, list<T*>> queue;
//        
//        queue.push(t);
//
//        while (!queue.empty())
//        {
//            T* node = queue.front();
//            queue.pop();
//
//            v->visit(node);
//
//            ListIterator<T>* it = node->getChildrenIterator();
//            
//            while(!it->end())
//            {
//                node = &(it->get());
//                        
//                queue.push(node);
//                it->next();
//            }
//        }
//    }
//
//    template <class T, class V>
//    void Traverser::traverseUp(T* t, V* v)
//    {
//        T* node = t;
//        while(!node->isRoot())
//        {
//            v->visit(node);
//            node = node->parent();
//        }
//    }
//}
