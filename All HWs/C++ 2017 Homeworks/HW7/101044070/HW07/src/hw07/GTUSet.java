package hw07;

import java.lang.reflect.Array;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * GTUSet class implements GTUSetInt interface
 *
 * @author Celal
 * @param <T>
 */
public class GTUSet<T> implements GTUSetInt<T> 
{ 

    public T[] data;
    private int capacity;
    private int used;
    GTUIterator iteratorSet = new GTUIterator();
    
    /**
     * Class Constructor initialises data members to zero
     */
    public GTUSet() 
    {   
        capacity = 0;
        used = 0; 
    }

    /**
     * Class constructor takes parameter and create generic array
     *
     * @param cls constructor parameter
     */
    public GTUSet(Class<T[]> cls) 
    {
        data = cls.cast(Array.newInstance(cls.getComponentType(), 20));
    }
 
    /**
     * Class constructor takes parameters and create generic array
     *
     * @param cls constructor parameter
     * @param capacityValue Set container capacity
     */
    public GTUSet(Class<T[]> cls, int capacityValue)
    { 
        capacity = capacityValue;
        data = cls.cast(Array.newInstance(cls.getComponentType(), capacity));
    }

    /**
     * @return number of used element in set container
     */
    public int getUsed() 
    {
        return used;
    }

    /**
     * @return number of capacity of set container
     */
    public int getCapacity()
    {
        return capacity;
    }

    /**
     * Get set element to given index
     * 
     * @param index to return set container data
     * @return set element to given index
     */
    @Override
    public T getValue(int index) 
    {
        return data[index];
    }

    /**
     * 
     * @param otherSet other set container to intersection
     * @return set is the intersection of this set and the given set.
     */
    @Override
    public GTUSetInt<T> intersection(GTUSetInt<T> otherSet) 
    {
        GTUSetInt<T> result = new GTUSet<>();  

        for (int i = 0; i < this.sizeFunction(); ++i) {
            for (int j = 0; j < otherSet.sizeFunction(); ++j) {
                if (this.data[i].equals(otherSet.getValue(j))) {
                    try {
                        //result.insertFunction(this.data[i]);
                    } catch (IllegalArgumentException ex) {
                        Logger.getLogger(GTUSet.class.getName()).log(Level.SEVERE, null, ex);
                    }
                    System.out.print(this.data[i]);
                    System.out.print(" ");
                }
            }
        }

        return result;
    }

    /**
     * Insert function adds element to the set container
     *
     * @param element to insert element to set container
     * @exception IllegalArgumentException if the element is already in the set  
     */
    @Override
    public void insertFunction(T element) throws IllegalArgumentException
    {
          
        if (search(element))
        {
            throw new IllegalArgumentException("The element is already in the set !! ");   
        }

        data[used] = element;
        used++;
    }

    /**
     * Erase function deletes element to given index
     *
     * @param index to delete element from the set container to given index
     * @throws Exception if the set container is already empty
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
            data[i] = data[i + 1];
        }

        --used;
    }

    /**
     * Removes all elements from the set container (which are destroyed),
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
            throw new Exception("The set is already empty !!");
        }

        for (int i = 0; i < tempSize; ++i) 
        {
            eraseFunction(0);
        }
    }

    /**
     * Count function searches the container for elements equivalent to element
     *
     * @param element to number of matches in the set container
     * @return the number of matches in the set container
     * @throws Exception
     */
    @Override
    public int countFunction(T element) throws Exception 
    {
        int counter=0;
        
        if (this.sizeFunction() == 0) 
        {
            throw new Exception("The set is already empty !!");
        }

        for (int i = 0; i < sizeFunction(); ++i) 
        {
            if (data[i].equals(element)) 
            {
                ++counter;
            }
        }
        return counter;
    }

    /**
     * whether the set container is empty
     * @return true if the set is empty, otherwise false
     */
    @Override
    public boolean emptyFunction()
    {
        return used == 0;
    }

    /**
     * Size Function
     * @return set container size
     */
    @Override
    public int sizeFunction() 
    {
        return used;
    }

    /**
     * max_size Function
     * @return the maximum number of elements that the set container can hold.
     */
    @Override
    public int max_sizeFunction()
    {
        return 2147483647; // equal to 2^31 − 1
    }

    /**
     * Search Function
     * @param element to target value in the set container
     * @return true if the searched element is in the set container, otherwise
     * false
     */
    @Override
    public boolean search(T element)
    {
        for (int i = 0; i < sizeFunction(); ++i) {
            if (data[i].equals(element)) {
                return true;
            }
        }

        return false;
    }

    /**
     * Find Function
     * @param element to find element
     * @return iterator to element
     */
    @Override
    public GTUIterator<T> findFunction(T element) // Get iterator to element
    {
        GTUIterator findIterator = new GTUIterator();
        
        findIterator = this.endFunction();
        
        int size = sizeFunction();
        
        for(int i = 0; i<size; ++i) 
        {
            if (this.getValue(i).equals(element)) 
            {
                findIterator.currentIndex = i;
                break;
            }
        }
            
        return findIterator;
    }

    /**
     * Begin Function
     * @return an iterator referring to the first element in the set container.
     */
   
    @Override
    public GTUIterator <T> beginFunction() 
    {
        GTUIterator<T> itr;
        iteratorSet.currentIndex = 0;
        itr = iteratorSet;

        return itr;
    }
    
    /**
     * End Function
     * @return an iterator referring to the past-the-end element in the set
     * container
     */
   
    @Override
    public GTUIterator<T> endFunction() 
    {
        GTUIterator<T> itr;
        iteratorSet.currentIndex = sizeFunction();
        itr = iteratorSet;

        return itr;
    }
   

    /**
     * The class GTUIterator implements the following methods
     *
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
            return (T) data[currentIndex++];
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

    } // End GTUIterator
    

} // End GTUSet class
