package hw07;
import javafx.util.Pair;

/**
 *
 * @author Celal TEMIZ - 101044070
 * 
 * CSE 241 - Object Oriented Programming
 * HW07    - Java Inheritance and Generic
 */
public class HW07 
{

    /**
     * @param args the command line arguments
     * 
     */ 
    
    public static void main(String[] args) 
    {         
        try 
        {
        ////////////////////////////////////////////////////////////////////////////////////   
        /////////////////////// Integer set container //////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
            
            GTUSet<Integer> mySet1  = new GTUSet<>(Integer[].class); // Create new set object
                         
            if(mySet1.emptyFunction()) 
            {            
                mySet1.insertFunction(3);   // Insert function tests
                mySet1.insertFunction(44);
                mySet1.insertFunction(5555);
                mySet1.insertFunction(66666);

 
                // Intersection Test          
                GTUSet<Integer> mySet2  = new GTUSet<>(Integer[].class); 
                mySet2.insertFunction(3);
                mySet2.insertFunction(44);
            
                System.out.print("Intersection result to Set1 and Set2 : "); 
                GTUSetInt<Integer> resultSet = mySet1.intersection(mySet2);
             
                
                mySet1.iteratorSet = mySet1.findFunction(3);             // Find  function test
                if(mySet1.iteratorSet == mySet1.beginFunction())         // Begin function test
                {
                    System.out.println("\nFind function and begin function are succesfull to Set1 !!"); 
                }

                // throws exception InvalidParameterException if the element is already in the set
                // mySet1.insertFunction(44);
                
                              
                // Iterator functions tests to set class
                System.out.println("\nSet1 elements :");    
                while(mySet1.iteratorSet.hasNext())
                {
                    
                    System.out.println(mySet1.iteratorSet.next());
                }
                
                System.out.printf("Before size of Set1 : %d\n", mySet1.sizeFunction()); // Size function test
                mySet1.eraseFunction(1);    // Erase function test
                System.out.printf("Called eraseFunction to given index\nAfter size of Set1 : %d\n", mySet1.sizeFunction()); 
                
                // Count function test
                System.out.printf("Count function result is : %d \n", mySet1.countFunction(66666));
                
               
                if(mySet1.max_sizeFunction() > 987654321)   // Clear and size functions test
                {
                    mySet1.clearFunction();  
                    System.out.printf("Clear function called \nLast Set1 size is : %d\n ", mySet1.sizeFunction() );
                } 
            }

            
            /////////////////////////////////////////////////////////////////////////////////
            ///////////////// Character set container ///////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////
            GTUSet<Character> mySet3 = new GTUSet<>(Character[].class, 15);      // Capacity = 15
             
            if(mySet3.emptyFunction()) 
            {            
                mySet3.insertFunction('C');
                mySet3.insertFunction('S');
                mySet3.insertFunction('E');
                mySet3.insertFunction('*');
                
                
                System.out.println("\nSet3 elements :");
                // Iterator Testing 
                while(mySet3.iteratorSet.hasNext())
                {
                  System.out.println(mySet3.iteratorSet.next());
                }
                
                System.out.printf("Before size of Set3 : %d\n", mySet3.sizeFunction());
                
                mySet3.iteratorSet = mySet3.findFunction('*');  // Find Function test
                if(mySet3.iteratorSet == mySet3.endFunction())  // End function test
                {
                    System.out.println("Find function and end function succesfull to Set3 !!"); 
                }
                
            }   
                
            ///////////////////////////////////////////////////////////////////////
            ///////////////////// String set container ////////////////////////////
            ///////////////////////////////////////////////////////////////////////
            GTUSet<String> mySet4  = new GTUSet<>(String[].class); 
            
            if(mySet4.emptyFunction()) 
            {            
                mySet4.insertFunction("GEBZE");
                mySet4.insertFunction("TECHNICAL");
                mySet4.insertFunction("UNIVERSITY");
                mySet4.insertFunction("*#+%&/()?=");
                
                System.out.println("\nSet4 elements :");
                // Iterator Testing 
                while(mySet4.iteratorSet.hasNext())
                {
                  System.out.println(mySet4.iteratorSet.next());
                }
                
                System.out.printf("Before size of Set4 : %d\n", mySet4.sizeFunction());
                
                mySet4.eraseFunction(0);    // Erase function tests to given indexes
                mySet4.eraseFunction(1);
                mySet4.eraseFunction(2);
                
                System.out.printf("Called eraseFunction to given index\nAfter size of Set4 : %d\n", mySet4.sizeFunction());
            }   
   
//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// General Map Container  /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
           
            
            GTUMap map1 = new GTUMap(Pair[].class,10);  // Create new map object
  
            if(map1.emptyFunction())    // Empty function test
            {
                System.out.println("\n----------------------------------------");
                System.out.println("Generic Map Container Test : ");
                Pair <Integer,Integer> p1 = new Pair<>(1,2);
                Pair <Integer,Double> p2  = new Pair<>(3,4.4);
                map1.insertFunction(p1);    // Insert function tests
                map1.insertFunction(p2); 
                map1.insertFunction(new Pair<>(2,"GTU"));
                
                
                // throws exception InvalidParameterException if the element is already in the map
                // map1.insertFunction(new Pair<>(2,"GTU"));
                
                
                map1.insertFunction(new Pair<>(4.1,"CSE"));
                map1.insertFunction(new Pair<>('C',"Object Oriented Programming"));
              
                
                System.out.println("Map 1 Elements :"); 
                
                // Iterator Testing to map class
                while(map1.iteratorMap.hasNext())
                {
                  System.out.println(map1.iteratorMap.next());
                }             
                
                GTUMap map2 = new GTUMap(Pair[].class,5);  // Create new map object
                Pair <Integer,Integer> p3 = new Pair<>(1,2);
                map2.insertFunction(p3);
                
                // Intersction function test
                System.out.println("Intersection result to map1 and map2 : "); 
                GTUSetInt<Integer> resultMap = map1.intersection(map2);
                                              
                if(map1.countFunction(p1) == 1)   // Count Function Test 
                {
                    System.out.println("This is an element of map !\n");
                }

                System.out.printf("Before size of map1 : %d\n", map1.sizeFunction());
                System.out.println("----------------------------------------");
                System.out.printf("at(3) function result   : %s\n", map1.at(3).toString());       // 4.8
                System.out.printf("at(4.1) function result : %s\n", map1.at(4.1).toString());   // "CSE"
                System.out.printf("at('C') function result : %s\n", map1.at('C').toString());   // "Object Oriented Programming"
                System.out.println("----------------------------------------");
                
                map1.eraseFunction(0);  // Erase function tests to given indexes
                map1.eraseFunction(1);
                map1.eraseFunction(2);
                

                System.out.printf("Called eraseFunction to given index\nAfter size of map1 : %d\n", map1.sizeFunction());
                
                if(map1.max_sizeFunction() > 987654321)
                {
                    map1.clearFunction();   // Size and clear function test
                    System.out.printf("Called clearFunction\nLast size of map1 : %d\n", map1.sizeFunction());
                }
                
            }  

        }
               
        catch (IllegalArgumentException e)
        {
            System.out.println("Exception Caught: " + e); 
        }
        
        catch (Exception e) 
        {
            System.out.println("Exception Caught: " + e); 
        }
        
    }
    
}
