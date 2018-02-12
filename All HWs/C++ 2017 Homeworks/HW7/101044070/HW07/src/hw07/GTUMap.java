package hw07;

import java.lang.reflect.Array;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.util.Pair;

/**
 * GTUMap class 
 * @author Celal TEMIZ
 * @param <K> Key - Generic GTUMap Container 
 * @param <V> Value - Generic GTUMap Container
 *
 */
public class GTUMap<K, V> extends GTUSet<javafx.util.Pair<K, V>> 
{
    public Pair<K, V>[] mapArray;
    private int used;
    private int capacity;
    GTUIterator iteratorMap = new GTUIterator();
    
    /**
    * No parameter constructor
    */
    public GTUMap()
    {
        used = 0;
        capacity = 0;
    }

    /**
     *
     * @param cls constructor parameter
     * @param capacityValue container capacity
     */
    public GTUMap(Class<Pair<K, V>[]> cls, int capacityValue)
    {
        mapArray = cls.cast(Array.newInstance(cls.getComponentType(), 10));
    }

    /**
     *
     * @param index parameter to map data
     * @return key value to given index
     */
    public K getMapKey(int index) 
    {
        return mapArray[index].getKey();
    }
    
    /**
    * 
    * @param index to map data
    * @return value to given index
    */
   
    public V getMapValue(int index) 
    {
        return mapArray[index].getValue();
    }
    
   /**
    * 
    * @param index to return map data
    * @return an pair object to given index
    */
    @Override
    public Pair<K,V> getValue(int index)
    {
        return mapArray[index];
    }
 
    /**
    *
    * @return number of used elements in the set
    */
    public int getMapUsed() 
    {
        return used;
    }

    /**
    *
    * @return map capacity
    */
    public int getMapCapacity()
    {
        return capacity;
    }

    /**
    * Insert element to set container
    * @param pairObj to insert to map container
    * @throws IllegalArgumentException if the element is already in the set
    */
    @Override
    public void insertFunction(Pair<K, V> pairObj) throws IllegalArgumentException
    {
        if (searchMap(pairObj.getKey())) 
        {
            throw new IllegalArgumentException("The element is already in the set !! ");
        }        
        
        mapArray[used] = pairObj;
        ++used;
    }

    /**
    * Erase element
    * @param index to erase element to map container
    * @throws Exception if the set is already empty 
    */
    @Override
    public void eraseFunction(int index) throws Exception
    {
        if (this.sizeFunction() == 0)
        {
            throw new Exception("The set is already empty !!");
        }

        for (int i = index; i < sizeFunction(); ++i)
        {
            mapArray[i] = mapArray[i + 1];
        }

        --used;
    }

    /**
    *
    * @return  map container size
    */
    @Override
    public int sizeFunction()
    {
        return used;
    }

   
    /**
    * Test whether container is empty
    * @return true if the map is empty, otherwise false
    */
    @Override
    public boolean emptyFunction()
    {
        return used == 0;
    }
    
    /**
    *  
    * @return the maximum number of elements that the set container can hold.
    */
    @Override
    public int max_sizeFunction()
    {
        return 2147483647; // equal to 2^31 − 1
    }
    
    /**
    * Search function
    * @param element to search element in the map container
    * @return true if the searched element is in the set container, otherwise
    */
    public boolean searchMap(K element)
    {
        for (int i = 0; i < sizeFunction(); ++i)
        {
            if (mapArray[i].getKey().equals(element))
            {
                return true;
            }
        }
        return false;
    }
    
     
    /**
    * Removes all elements from the map container (which are destroyed),
    * leaving the container with a size of 0.
    *
    * @throws Exception if the set is already empty
    */
    @Override
    public void clearFunction() throws Exception 
    {  
        int tempSize = sizeFunction();
        
        if (this.sizeFunction() == 0) 
        {
            throw new Exception("The map is already empty !!");
        }

        for (int i = 0; i < tempSize; ++i) 
        {
            eraseFunction(0);
        }
    }
    
    /**
     * Count elements with a specific value
     * @param pairObject to count number of elements in the map container
     * @return number of elements with a specific value
     * @throws Exception 
     */
    @Override
    public int countFunction(Pair<K,V> pairObject) throws Exception
    {
        int counter=0;
        
        if (this.sizeFunction() == 0) 
        {
            throw new Exception("The set is already empty !!");
        }

        for (int i = 0; i < sizeFunction(); ++i) 
        {
            if (mapArray[i].getKey().equals(pairObject.getKey())) 
            {
                ++counter;
            }
        }
        return counter;
    }
    
    
    /**
     * Intersection function
     * @param otherMap to intersection parameter
     * @return set is the intersection of this set and the given set.
     */
    @Override
    public GTUSetInt<Pair<K,V>> intersection(GTUSetInt<Pair<K,V> > otherMap) 
    {
       
        GTUSetInt<Pair<K,V>> result = new GTUMap<>();        
        
        for (int i = 0; i < this.sizeFunction(); ++i) {
            for (int j = 0; j < otherMap.sizeFunction(); ++j) {

                if (this.getMapKey(i).equals(otherMap)) 
                {
                    try {
                        result.insertFunction(this.data[i]);
                    } catch (Exception ex) {
                        Logger.getLogger(GTUSet.class.getName()).log(Level.SEVERE, null, ex);
                    }
                    System.out.print(this.mapArray[i].getKey());
                    System.out.print(" ");
                    System.out.print(this.mapArray[i].getValue());
                }
            }
        }

        return result;
    }
    
    /**
     * Access element
     * @param k key parameter
     * @return If k matches the key of an element in the map, the method returns a reference to its mapped value.
     */
    public V at(K k) 
    {
       for(int i=0; i<sizeFunction(); ++i) 
       { 
            if(this.mapArray[i].getKey().equals(k))
            {
                return mapArray[i].getValue(); 
            }
       }
       
       return null;
    }
    
    /**
     * The class GTUIterator implements the following methods
     * @param <T> 
     */
    public class GTUIterator<T> implements GTUSetInt.GTUIterator<T>
    {

        private int currentIndex = 0;

        /**
         * @return true if this list iterator has more elements when traversing
         * the list in the forward direction
         */
        @Override
        public boolean hasNext() 
        {
            return currentIndex < sizeFunction();
        }

        /**
         * @return true if this list iterator has more elements when traversing
         * the list in the reverse direction.
         */
        @Override
        public boolean hasPrevious()
        {
            return sizeFunction() > 0;
        }

        /**
         * @return the next element in the list and advances the cursor position
         */
        @Override
        public T next()
        {
            return (T) mapArray[currentIndex++];
        }

        /**
         * @return the previous element in the list and moves the cursor
         * position backwards.
         */
        @Override
        public T previous()
        {
            return (T) getValue(sizeFunction() - 1);
        }

    } // End GTUIterator Class
    
 

} // End Map Class
