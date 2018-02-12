#include "GTUMap.h"

namespace CelalTemiz
{

    // No parameter constructor
    template<class K, class V>
    GTUMap<K, V>::GTUMap()
    {
        mapSize = 0;
        mapCapacity= 1;
        mapArray = new pair<K, V>[mapCapacity];

    };

    // Constructor that takes map size parameter from the user
    template<class K, class V>
    GTUMap<K, V>::GTUMap(int newMapCapacity)
    {
        mapSize = 0;
        mapCapacity = newMapCapacity;
        mapArray = new pair<K, V>[mapCapacity];
    }

    // Test whether container is empty
    template<class K,class V>
    bool GTUMap<K, V>::emptyFunction()
    {
        if(mapSize == 0)
            return true;
        else
            return  false;
    }

    // Insert element, throws exception if the element is already in the map
     template<class K, class V>
     void GTUMap<K, V>::insertFunction(pair<K,V> (pairObj) ) throw (sameElement)
    {
        if (search(pairObj.first))
        {
            throw  sameElement();
        }

         mapArray[mapSize] = pairObj;
         ++mapSize;
    }

    // Search Function
    template<class K, class V>
    bool GTUMap<K, V>::search(const K& element) const
    {
        for (int i = 0; i < getMapSize(); ++i)
            if (mapArray[i].first == element)
                return true;

        return false;
    }

    // Erase element
    template<class K, class V>
    void GTUMap<K, V>::eraseFunction(K index) throw(int)
    {
        if (index > getMapSize())
        {
            throw -1;
        }
        else
        {
            for (K i = index; i < getMapSize(); ++i)
                mapArray[i] = mapArray[i+1];

            --mapSize;
        }
    }

    // Return container size
    template<class K, class  V>
    int GTUMap<K,V>::sizeFunction() const
    {
        return mapSize;
    }

    // Return map capacity
    template<class K, class V>
    int GTUMap<K, V>::getMapCapacity()const
    {
        return mapCapacity;
    }

    // Return map size
    template<class K, class V>
    int GTUMap<K, V>::getMapSize()const
    {
        return mapSize;
    }

    // Print map key and value parameters
    template<class K, class V>
    void GTUMap<K, V>::printFunction()
    {
        for(int i=0; i<getMapSize(); ++i)
            cout << mapArray[i].first << " " << mapArray[i].second << endl;

    }

    // Access Element
    // If k matches the key of an element in the container, the function returns a reference to its mapped value.
    template <class K, class V>
    V& GTUMap<K, V>::operator[] (const K& k)
    {
        return mapArray[k].second;
    }

    // Clear all container
    template <class K, class V>
    void GTUMap<K, V>::clearFunction()
    {
        int tempSize = getMapSize();

        for(int i=0; i<tempSize; ++i) {
            eraseFunction(0);
        }

    }

    // Count elements with a specific value
    template<class K,class V>
    int GTUMap<K, V>::countFunction(const K& element)const
    {
        int counter = 0;

        for (int i = 0; i < getMapSize(); ++i)
            if (mapArray[i].first == element)
                ++counter;

        return counter;
    }

}

