#ifndef GTUSETBASE_H
#define	GTUSETBASE_H

#include <iostream>

using namespace std;

namespace CelalTemiz
{
    // Exception Class
    class sameElement {};

    // GTUSetBase Class
    template <class T>
    class GTUSetBase
    {
    public:

        // My Iterator Class
        template <class U=T>
        class GTUIterator
        {
            public:
                GTUIterator():pointer(NULL) {}
                GTUIterator(T* newPointer) : pointer(newPointer) { }
                bool operator ==(const GTUIterator & other) const {return this->pointer==other.pointer;}
                bool operator !=(const GTUIterator & other) const {return this->pointer!=other.pointer;}
                GTUIterator& operator =(const GTUIterator & other) {pointer = &(*other); return *this;}
                // Pre Increment Operator
                GTUIterator & operator++() { pointer++; return *this; }
                // Post Increment Operator
                GTUIterator   operator++(int) {GTUIterator temp = *this; pointer++; return temp;}
                // Pre Decrement Operator
                GTUIterator & operator--() {pointer--; return *this;}
                // Post Decrement Operator
                GTUIterator   operator--(int) {GTUIterator temp = *this; pointer--; return temp;}
                T& operator*() const  {return *pointer;}
                T* operator->() const {return  pointer;}

            protected:
                T* pointer;
        };


        GTUSetBase() {}
        virtual ~GTUSetBase() {}
        virtual T getPtrValue(int index) const = 0;
        virtual bool emptyFunction() const = 0; // Test whether container is empty
        virtual int  sizeFunction() const = 0; // Return container size
        virtual int  max_sizeFunction() const = 0; // Return maximum size
        virtual void insertFunction(const T& element) throw (sameElement) = 0; // Insert element
        virtual void eraseFunction(int index) throw(int) = 0; //Erase element
        virtual void clearFunction() = 0; // Clear all content
        virtual int  countFunction(const T& element) const = 0; // Count elements with a specific value
        virtual GTUIterator<T> findFunction(T& element) const=0;  // Get iterator to element
        virtual GTUIterator<T> endFunction()const = 0; // Return iterator to end
        virtual GTUIterator<T> beginFunction()const = 0; // Return iterator to end
        virtual bool search(const T& element) const = 0; // Search element
    };

} // CelalTemiz


#endif	/* GTUSETBASE_H */

