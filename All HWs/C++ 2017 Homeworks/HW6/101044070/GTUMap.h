#ifndef GTUMAP_H
#define GTUMAP_H

#include "GTUSet.h"
#include "GTUSetBase.h"
#include <iostream>

using namespace std;

namespace CelalTemiz {

    template<class K, class V>
    class GTUMap : public GTUSet<pair<K, V> > {
    public:

        GTUMap();
        GTUMap(int newMapCapacity);
        int getMapSize() const ;
        int getMapCapacity() const;
        virtual int  sizeFunction() const; // Return container size
        virtual void insertFunction(pair<K,V> (pairObj)) throw (sameElement);
        virtual void eraseFunction(K index) throw(int); //Erase element
        virtual bool emptyFunction(); // Test whether container is empty
        void printFunction();
        V& operator[] (const K& k); // Access Element
        virtual void clearFunction(); // Clear all content
        virtual int countFunction(const K& element) const ; //Count elements with a specific value
        virtual bool search(const K& element) const; //search element

        // Get iterator to element
        virtual typename GTUSetBase<pair<K,V>>::template GTUIterator<pair<K,V>> findFunction(K& element) const
        {
            typename GTUSetBase<pair<K,V>>::template GTUIterator<pair<K,V>> itr;
            itr = this->endFunction();

            size_t size = getMapSize();

            for(size_t i = 0; i<size; ++i) {
               if (mapArray[i].first == element) {
                    itr = const_cast<pair<K,V>*>(&mapArray[i]);
                    break;
                }
            }
            return itr;
        }

        //Return iterator to begin
        virtual typename GTUSetBase<pair<K,V>>::template GTUIterator<pair<K,V>> beginFunction()const
        {
            typename GTUSetBase<pair<K,V>>::template GTUIterator<pair<K,V>> itr;
            size_t size = getMapSize();
            itr = const_cast<pair<K,V>*>(&mapArray[0]);
            return itr;
        }

        //Return iterator to begin
        virtual typename GTUSetBase<pair<K,V>>::template GTUIterator<pair<K,V>> endFunction()const
        {
            typename GTUSetBase<pair<K,V>>::template GTUIterator<pair<K,V>> itr;
            size_t size = getMapSize();
            itr = const_cast<pair<K,V>*>(&mapArray[size]);
            return itr;
        }

    private:
        pair<K, V> *mapArray;
        int mapSize;
        int mapCapacity;

    };



}//CelalTemiz


#endif //GTUMAP_H
