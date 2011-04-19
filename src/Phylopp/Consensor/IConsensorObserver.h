#ifndef ICONSENSOROBSERVER_H
#define ICONSENSOROBSERVER_H

namespace Consensor
{
    /**
    * Interface: IConsensorObserver
    * ----------------------
    * Description: Interface for observers that shall be used during the
    * consensor algorithm. The consensors observers shall notify when a node
    * is included or excluded from de resulting consensed tree.
    * Type Parameter T: T is the underlying node class 
    */
    template <class T>
    class IConsensorObserver
    {
    public:
        /**
        * Method: notifyInclude
        * ---------------
        * Description: Notifies when a node is included in the consensed tree.
        * @param node node that has been included in the consensed tree
        */
        virtual void notifyInclude(T* node) = 0;

        /**
        * Method: notifyExclude
        * ---------------
        * Description: Notifies when a node is excluded in the consensed tree.
        * @param node node that has been excluded in the consensed tree
        */
        virtual void notifyExclude(T* node) = 0;
    };
}

#endif