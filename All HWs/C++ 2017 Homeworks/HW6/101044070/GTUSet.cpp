
#include "GTUSet.h"

namespace CelalTemiz
{
    // No parameter constructor
    template<class T>
    GTUSet<T>::GTUSet() :GTUSetBase<T>(),capacity(1),used(0) //call base class constructor
    {
        std::shared_ptr<T> msp( new T[capacity] );
        sp=msp;
    }

    // Constructor that takes set size from the user
    template<class T>
    GTUSet<T>::GTUSet(int capacityValue):GTUSetBase<T>(),capacity(capacityValue),used(0)
    {
        std::shared_ptr<T> msp( new T[getCapacity()] );
        sp=msp;
    }

    // Assignment operator overloading
    template<class T>
    GTUSet<T>& GTUSet<T>::operator =(const GTUSet<T>& rightSide)
    {
        if (&rightSide == this)
            return *this;
        if (capacity != rightSide.capacity) {
            capacity = rightSide.capacity;
        }

        used = rightSide.used;
        shared_ptr<T> sp( new T[capacity] );
        for(int i = 0; i < used; i++) {
             sp.get()[i] = rightSide.getPtrValue(i);
        }

        return *this;
    }

    // Index operator overloading
    template<class T>
    T& GTUSet<T>::operator[](int index)
    {
        return sp.get()[index];
    }


    // Search Function
    template<class T>
    bool GTUSet<T>::search(const T& element) const
    {

        for (int i = 0; i < getNumberOfUsed(); ++i)
            if (sp.get()[i] == element)
                return true;

        return false;
    }


    // Insert element, throws exception sameElement if the element is already in the container
    template<class T>
    void GTUSet<T>::insertFunction(const T& element) throw (sameElement)
    {

        if (search(element))
        {
            throw  sameElement();
        }


        sp.get()[used] = element;
        used++;
        sortFunction(); // Sort set container elements
    }

    // Sort function to set
    template<class T>
    void GTUSet<T>::sortFunction()
    {
        for(int i=1; i<sizeFunction(); ++i) {
            for (int j = 0; j < sizeFunction() - i; ++j)
                if (sp.get()[j] > sp.get()[j + 1])
                {
                    T temp = sp.get()[j];
                    sp.get()[j] = sp.get()[j+1];
                    sp.get()[j+1] = temp;
                }
        }
    }

    // Return container size
    template<class T>
    int GTUSet<T>::sizeFunction() const
    {
        return used;
    }

    // Return maximum size
    template <class T>
    int GTUSet<T>::max_sizeFunction() const
    {
        return 2147483647; // equal to 2^31 − 1
    }

    // Return number of used elements in container
    template <class T>
    int GTUSet<T>::getNumberOfUsed() const
    {
        return used;
    }

    // Getter
    template <class T>
    T GTUSet<T>::getPtrValue(int index) const
    {
        return sp.get()[index];
    }


    // Test whether container is empty
    template<class T>
    bool GTUSet<T>::emptyFunction() const
    {
        if(used==0)
            return true;
        else
            return false;
    }

    // Erase element to given index
    template<class T>
    void GTUSet<T>::eraseFunction(int index) throw(int)
    {
        if (index > getNumberOfUsed())
        {
            throw index;
        }
        else
        {
            for (int i = index; i < getNumberOfUsed(); ++i)
                sp.get()[i] = sp.get()[i+1];
            --used;
        }
    }

    // Clear all container
    template<class T>
    void GTUSet<T>::clearFunction()
    {

        if(this->emptyFunction())
            throw std::out_of_range("Index out of range\n");

        int tempSize = getNumberOfUsed();

        for(int i=0; i<tempSize; ++i) {
            eraseFunction(0);
        }

    }

    // Print container members
    template<class T>
    void GTUSet<T>::printFunction()
    {
        for(int i=0; i<getNumberOfUsed(); ++i)
            cout << sp.get()[i] << " " ;
        cout << endl;
    }


    // Count elements with a specific value
    template<class T>
    int GTUSet<T>::countFunction(const T& element)const
    {
        int counter = 0;

        for (int i = 0; i < getNumberOfUsed(); ++i)
            if (sp.get()[i] == element)
                ++counter;

        return counter;
    }



}// CelalTemiz
