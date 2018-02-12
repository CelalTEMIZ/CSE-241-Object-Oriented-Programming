package hw07;


/**
 * GTUSetInt.java
 * Interface class that has the following methods.
 * @author Celal  TEMIZ
 * @param <T> Generic GTUSet Container
 */
public interface GTUSetInt<T> 
{    
    boolean emptyFunction(); //Return whether the set container is empty
    int  sizeFunction(); // Return container size
    int  max_sizeFunction();// Return maximum size
    void insertFunction(T element) throws IllegalArgumentException; // Insert element
    void eraseFunction(int index)throws Exception; //Erase element
    void clearFunction()throws Exception; // Clear all content
    int  countFunction(T element)throws Exception; // Count elements with a specific value 
    boolean search(T element); // Search element
    T getValue(int index); // Get set element to given index
    GTUSetInt<T> intersection(GTUSetInt<T> otherSet); //The returned set is the intersection of this set and the
    GTUIterator<T> findFunction(T element);  // Get iterator to element
    GTUIterator<T> endFunction();    // Return iterator to end
    GTUIterator<T> beginFunction();  // Return iterator to end
    
    /**
     * 
     * @param <T> 
     */
    public interface GTUIterator<T> 
    {
    /**
     * @return true if this list iterator has more elements when traversing
     * the list in the forward direction
     */
     public boolean hasNext();

     /**
     * @return true if this list iterator has more elements when traversing
     * the list in the reverse direction.
     */
     public boolean hasPrevious();

     /**
     * @return the next element in the list and advances the cursor position
     */
     public T next();

     /**
     * @return the previous element in the list and moves the cursor
     * position backwards.
     */
     public T previous();

    } // End GTUIterator 
    

} // End GTUSetInt