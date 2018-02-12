//
// CELAL TEMIZ - 101044070
//
// CSE 241 - HW06
//
// Inheritance, Templates, STL
// Implementing a templated class hierarchy for sets and maps.
//

#include <iostream>
#include <memory>
#include "GTUSet.cpp"
#include "GTUMap.cpp"


using namespace std;
using namespace CelalTemiz;

template <class T>
void setIntersection (const GTUSetBase<T>&obj1, const GTUSetBase<T>&);

// Test functions to set and map containers
void testSetContainer();
void testMapContainer();


int main(int argc, char** argv)
{
    try
    {
        cout << "\n< Set Container Testing >"<<endl<<endl;
        testSetContainer();
        cout << "\n------------------------------------------------\n" << endl;
        cout << "< Map Container Testing >" <<endl;
        testMapContainer();
    }

    catch (sameElement)
    {
        cerr << endl<< "Cannot add same element !!"<<endl;
    }
    catch(int exc)
    {
        cerr << "Index is out of range to erase !! "<<endl;
    }
    catch (bad_alloc& ba)
    {
        cerr << "bad_alloc Caught: " << ba.what() << endl;
    }
    catch (exception& e)
    {
        cerr << "Exception: " << e.what() <<endl;
    }

    catch (...)
    {
        cerr << endl<< "An unexpected exception has been caught !!"<<endl;
    }

    return 0;
}

void testSetContainer()
{
    // Integer Set Container
    cout << "-- Set1 Testing --"<<endl;

    GTUSet<int> set1;

    if(set1.emptyFunction())
    {
        set1.insertFunction(1);     // Add elements to set container
        set1.insertFunction(3456);
        set1.insertFunction(23);
        set1.insertFunction(8);
    }

    // Print set elements
    cout << "Before Set1 Elements : ";
    set1.printFunction();
    cout << "Before Set1 size : " << set1.sizeFunction()<<endl;

    // if the element is already in the set, throws exception
    // set1.insertFunction(23);

    set1.eraseFunction(2);   // Erase element to given index

    typename GTUSet<int>::template GTUIterator<int> iterator1;

    // Iterator Test
    cout << "Called eraseFunction to given index !\nAfter Set1 Elements > Iterator Testing : ";
    for (iterator1 = set1.beginFunction(); iterator1 != set1.endFunction(); ++iterator1)
        cout << *iterator1 << " ";

    cout << endl<<"After Set1 size : " << set1.sizeFunction()<<endl;
    cout << "CountFunction Result : " << set1.countFunction(3456)<<endl;


    GTUSet<int>set3;
    set3.insertFunction(1);
    set3.insertFunction(3456);
    cout << endl<< "Set1 Elements : ";
    set1.printFunction();
    cout << "Set3 Elements : ";
    set3.printFunction();
    cout <<"SetIntersection Result to Set1 and Set3 : ";
    setIntersection<int>(set1,set3);

/////////////////////////////////////////////////////////////////////////////////////////////////////

    // Character Set Container
    GTUSet<char>set2(5);
    set2.insertFunction('a');
    set2.insertFunction('s');
    set2.insertFunction('d');
    set2.insertFunction('f');
    set2.insertFunction('b');

    cout << endl << endl<<"-- Set2 Testing--"<<endl;
    cout << "Before Set2 Elements : ";
    set2.printFunction();   // Before a b d f s
    cout << "Before Set2 size : " << set2.sizeFunction()<<endl;

    // if the element is already in the set, throws exception
    // set2.insertFunction('d');

                            // Before a b d f s
    set2.eraseFunction(2);  // After  a b f s
    set2.eraseFunction(2);  // After  a b s

    typename GTUSet<char>::template GTUIterator<char> iterator2;
    
    // Iterator Test
    cout << "Called eraseFunction to given index !\nIterator Testing > After Set2 Elements : ";
    for (iterator2 = set2.beginFunction(); iterator2 != set2.endFunction(); ++iterator2)
        cout << *iterator2 << " ";

    cout << endl<< "After Set2 size : " << set2.sizeFunction()<<endl;

    if(set2.countFunction('k') == 0)    // Count Function Test
        cout << "This is not an element of set !\n";


    char findElement = 'a';             // Find function test
    iterator2 = set2.findFunction(findElement);
    if(iterator2==set2.beginFunction())
        cout << "Find function is succesfull !! "<<endl;


    if(set2.max_sizeFunction() > 987654321 ) // Max_size function test
        set2.clearFunction();   // Clear function test

    cout << "Last Set2 size  : " << set2.sizeFunction()<<endl;


}

void testMapContainer()
{
    ///////////// Map 1 Test  //////////////////

    cout << endl<<"-- Map1 Testing --"<<endl;
    GTUMap<int,char> map1;
    map1.insertFunction(pair<int,char>(1,'c'));
    map1.insertFunction(pair<int,char>(22,'s'));
    map1.insertFunction(pair<int,char>(333,'e'));

    cout << "Before Map 1 Elements > Iterator Testing : "<<endl;
    typename GTUMap<int,char>::template GTUIterator<pair<int,char>> iterator1;

    for (iterator1 = map1.beginFunction(); iterator1 != map1.endFunction(); ++iterator1)
        cout << iterator1->first << " - " << iterator1->second << endl;


    cout <<"Before Map1 size : "<< map1.sizeFunction() << endl;
    map1.eraseFunction(0);
    cout <<"Called eraseFunction to given index !\nAfter  Map1 size : "<< map1.sizeFunction() << endl;
    cout <<"After Map1 Elements : "<<endl;
    map1.printFunction();


    ///////////// Map 2 Test //////////////////

    cout << endl << endl<<"-- Map2 Testing --"<<endl;
    GTUMap<int,double> map2;
    map2.insertFunction(pair<int,double>(8,3.6));
    map2.insertFunction(pair<int,double>(11,5.21));
    map2.insertFunction(pair<int,double>(9,2.5));
    map2.insertFunction(pair<int,double>(10,3.38));


    // if the element is already in the set, throws exception
    // map2.insertFunction(pair<int,double>(8,3.6));


    typename GTUMap<int,double>::template GTUIterator<pair<int,double>> iterator2;
    cout <<"Before Map2 Elements :"<<endl;
    // Iterator Test
    for (iterator2 = map2.beginFunction(); iterator2 != map2.endFunction(); ++iterator2)
        cout << iterator2->first << " - " << iterator2->second << endl;

    cout <<"Before Map2 size : "<< map2.sizeFunction() << endl;


    if(map2.countFunction(9) == 1)    // Count Function Test
        cout << "This is an element of map !\n";

    map2.eraseFunction(1);
    cout << "Called eraseFunction to given index !\nAfter Map2 Elements :" << endl;
    map2.printFunction();

    int findElement = 10;             // Find function test
    iterator2 = map2.findFunction(findElement);
    ++iterator2;
    if(iterator2 == map2.endFunction())
        cout << "Find function is succesfull !! "<<endl;


    if(map2.emptyFunction()==false)
        map2.clearFunction();   // Clear Function Test
    cout <<"Last Map2 size   : "<< map2.sizeFunction() << endl;

}

template <class T>
void setIntersection (const GTUSetBase<T>& obj1, const GTUSetBase<T>&obj2)
{
    std::shared_ptr<GTUSetBase<T>> sPtr;
    for(int i=0; i<obj1.sizeFunction(); ++i)
        for(int j=0; j<obj2.sizeFunction(); ++j)
            if(obj1.getPtrValue(i) == obj2.getPtrValue(j))
            {
                cout << obj1.getPtrValue(i)<<" ";
            }
}