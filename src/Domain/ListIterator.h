
#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include <list>

namespace Domain
{

/**
* Interface: ListIterator
* ----------------------
* Description: Class for a simple list forward iterator abstraction.
* Allows the client to easily iterate a list.
* Type Parameter T: T is the object that conforms the collection
* to be iterated
*/
template < class T, class K = T >
class ListIterator
{
public:
    //Constructor
    ListIterator(std::list<K*> l)
    {
        iterableList = l;
        it = iterableList.begin();
    }

    virtual void restart()
    {
        it = iterableList.begin();
    }

    virtual bool end() const
    {
        return it == iterableList.end();
    }

    virtual void next()
    {
        ++it;
    }

    virtual const T* get() const
    {
        return static_cast<T*>(*it);
    }

    virtual T* get()
    {
        return static_cast<T*>(*it);
    }

    virtual size_t count()
    {
        return iterableList.size();
    }

    ~ListIterator() { }

private:

    typedef typename std::list<K*>::iterator iterator;
    typedef typename std::list<K*>::const_iterator const_iterator;

    std::list<K*> iterableList;
    iterator it;
};
}

#endif
