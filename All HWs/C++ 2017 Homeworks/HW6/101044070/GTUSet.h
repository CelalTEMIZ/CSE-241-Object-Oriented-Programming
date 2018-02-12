#ifndef GTUSET_H
#define	GTUSET_H

#include "GTUSetBase.h"

#include <iostream>
#include <memory>

using namespace std;

namespace CelalTemiz
{
    // GTUSet Class
    template<class T>
    class GTUSet : public GTUSetBase<T>
    {

    public:
        GTUSet();
        GTUSet(int capacity);
        T getPtrValue(int index)const ;
        int getCapacity()const { return capacity; } // Return capacity of set container
        void sortFunction(); // Sort elements in set container
        virtual void insertFunction(const T& element) throw (sameElement); // Insert element
        virtual bool search(const T& element) const; // Search element
        virtual int  sizeFunction() const; // Return container size
        virtual int  max_sizeFunction() const ;  // Return maximum size
        virtual void eraseFunction(int index) throw(int);  // Erase element to given index
        int getNumberOfUsed()const; // Return number of used element in the container
        virtual bool emptyFunction() const; // Test whether container is empty
        virtual void clearFunction(); // Clear all content
        virtual int  countFunction(const T& element) const ; // Count elements with a specific value
        void printFunction();


        T& operator [](int index);
        GTUSet& operator =(const GTUSet& rightSide); // Assignment Operator

        // Get iterator to element
        virtual typename GTUSetBase<T>::template GTUIterator<T> findFunction(T& element) const
        {
            typename GTUSetBase<T>::template GTUIterator<T> itr;
            itr = this->endFunction();

            size_t size = sizeFunction();

            for(size_t i = 0; i<size; ++i) {
                if (sp.get()[i] == element) {
                    itr = const_cast<T *>(&sp.get()[i]);
                    break;
                }
            }
            return itr;
        }

        //Return iterator to end
        virtual typename GTUSetBase<T>::template GTUIterator<T> endFunction()const
        {
            typename GTUSetBase<T>::template GTUIterator<T> itr;
            size_t size = sizeFunction();
            itr = const_cast<T*>(&sp.get()[size]);
            return itr;
        }

        //Return iterator to begin
        virtual typename GTUSetBase<T>::template GTUIterator<T> beginFunction()const
        {
            typename GTUSetBase<T>::template GTUIterator<T> itr;
            size_t size = sizeFunction();
            itr = const_cast<T*>(&sp.get()[0]);
            return itr;
        }

    protected:
        std::shared_ptr<T> sp;
        int capacity;
        int used;

    };
}// CelalTemiz

#endif	/* GTUSET_H */

