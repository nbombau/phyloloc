#ifndef IITERATOR_H
#define IITERATOR_H


namespace Domain
{
    /**
    * Interface: IIterator
    * ----------------------
    * Description: Interface for a simple forward iterator abstraction. 
    * Type Parameter T: T is the object that conforms the collection 
    * to be iterated
    */
    template <class T>
    struct IIterator
    {
        /**
        * Method: restart
        * ---------------
        * Description: Restarts the iterator
        */
        virtual void restart() = 0;

        /**
        * Method: end
        * -----------
        * Description: Informs whether it is the end of the collection
        * @return true if it is the end of the collection, false otherwise
        */
        virtual bool end() const = 0;

        /**
        * Method: restart
        * -------------
        * Description: Restarts the iterator
        */
        virtual void next() = 0;

        /**
        * Method: endOfUse
        * ----------------
        * Description: Disposes the resources used by the iterator
        */
        virtual void endOfUse() = 0;

        /**
        * Method: get
        * -----------
        * Description: Gets the current item
        * @return the current item of the iteration
        */
        virtual const T& get() const = 0;

        /**
        * Method: count
        * -------------
        * Description: Disposes the resources used by the iterator
        * @return count of elements in the collection that is being iterated
        */
        virtual size_t count()
        {
            size_t ret(0);

            restart();

            while(!end())
            {
                ret++;
                next();
            }

            return ret;
        }


        const T& operator *() const
        {
            return get();
        }

        const T* operator ->() const
        {
            return &get();
        }

        protected:
            //Destructor
            virtual ~IIterator(){}
    };

}

#endif
