
#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include <list>

namespace Domain
{

    /**
    * Class: ListIterator
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
        ListIterator(const std::list<K*>& l) : iterableList(l)
        {
            it = iterableList.begin();
        }


        ListIterator(const ListIterator<T,K>& it) : iterableList(it.iterableList)
        {
            this->it = iterableList.begin();
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

    private:

        typedef typename std::list<K*>::iterator iterator;
        typedef typename std::list<K*>::const_iterator const_iterator;

        const std::list<K*>& iterableList;
        const_iterator it;

        ListIterator& operator= (const ListIterator& other) 
        {
            return *this;
        }
    };
}

#endif
