#include "IConsensorObserver.h"
#include "ListIterator.h"
#include <list>


namespace Consensor
{
    using namespace std;
    using namespace Domain;
       
    /**
    * Class: MacroConsensorObserver
    * ----------------------
    * Description: Macro observer to be used when multiple consensor
    * observers are needed.
    * Type Parameter T: T is the underlying node class 
    */
    template <class T>
    class MacroConsensorObserver : public IConsensorObserver<T>
    {
    public:
        /**
        * Method: notifyInclude
        * ---------------
        * Description: Notifies when a node is included in the consensed tree.
        * @param node node that has been included in the consensed tree
        */
        virtual void notifyInclude(T* node)
        {
            ListIterator<IConsensorObserver<T>>* iter = new ListIterator<IConsensorObserver<T>>(observers);

            while(!iter.end())
            {
                IConsensorObserver<T>* o = iter.get();
                o.notifyInclude(node);
                iter.next();
            }
        }

        /**
        * Method: notifyExclude
        * ---------------
        * Description: Notifies when a node is excluded in the consensed tree.
        * @param node node that has been excluded in the consensed tree
        */
        virtual void notifyExclude(T* node)
        {
            //TODO: Reuse the code from the method above
            ListIterator<IConsensorObserver<T>>* iter = new ListIterator<IConsensorObserver<T>>(observers);

            while(!iter.end())
            {
                IConsensorObserver<T>* o = iter.get();
                o.notifyExclude(node);
                iter.next();
            }
        }

        /**
        * Method: addObserver
        * -------------------
        * Description: Adds an observer
        */
        virtual void addObserver(IConsensorObserver<T>* o)
        {
            observers.push_back(o);
        }

        /**
        * Method: clearObservers
        * ----------------------
        * Description: Clears the observers
        */
        virtual void clearObservers()
        {
            observers.clear();
        }

    private:
        list<IConsensorObserver<T>*> observers;
    };
}