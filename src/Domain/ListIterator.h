
#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include "IIterator.h"
#include <list>

namespace Domain
{
    using namespace std;

    /**
    * Interface: ListIterator
    * ----------------------
    * Description: Class for a simple list forward iterator abstraction. 
    * Allows the client to easily iterate a list.
    * Type Parameter T: T is the object that conforms the collection 
    * to be iterated
    */
    template <class T>
    class ListIterator : public IIterator<T>
    {
    public:
        //Constructor
        ListIterator(std::list<T*> l)
	    { 
		    iterableList = l;
            it = iterableList.begin();
	    }
    
        /*
        * Method: restart
        * ---------------
        * Description: Restarts the iterator
        */
        virtual void restart()
        {
            it = iterableList.begin();
        }

        virtual bool end() const { return it == iterableList.end(); }

        virtual void next() { ++it; }

        virtual void endOfUse() { delete this; }

        virtual const T& get() const { return **it; }

        //TODO: revisar si es correcto que haya uno no const 
        //tambien revisar el tema de punteros, y la doble dereferencia
        virtual T& get() { return **it; }

        virtual size_t count() { return iterableList.size(); }       

    protected:

        ~ListIterator() { }

    private:

        typedef typename std::list<T*>::iterator iterator;
        typedef typename std::list<T*>::const_iterator const_iterator;
    
        std::list<T*> iterableList;
        iterator it;
    };
}

#endif