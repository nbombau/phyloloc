/*
    Copyright (C) 2011 Emmanuel Teisaire, Nicolás Bombau, Carlos Castro, Damián Domé, FuDePAN

    This file is part of the Phyloloc project.

    Phyloloc is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Phyloloc is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Phyloloc.  If not, see <http://www.gnu.org/licenses/>.
*/

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
    ListIterator(const std::list<K*>& l) :
        iterableList(l)
    {
        it = iterableList.begin();
    }

    ListIterator(const ListIterator<T, K>& it) :
        iterableList(it.iterableList)
    {
        this->it = iterableList.begin();
    }

    void restart()
    {
        it = iterableList.begin();
    }

    bool end() const
    {
        return it == iterableList.end();
    }

    void next()
    {
        ++it;
    }

    const T* get() const
    {
        return static_cast<T*>(*it);
    }

    T* get()
    {
        return static_cast<T*>(*it);
    }

    size_t count() const
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
