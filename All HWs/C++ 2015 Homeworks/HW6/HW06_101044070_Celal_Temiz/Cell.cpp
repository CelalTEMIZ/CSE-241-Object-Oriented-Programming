#include<iostream>
#include "Cell.h"
        
using namespace std;


void Cell::testFunction()
{

    // Test Objects

    Cell testObject_1(4,'c');
    
    Cell testObject_2(1,'c');
    
    Cell testObject_3(4,'d');
    
    Cell testObject_4(7,'e');
    
    Cell testObject_5(4,'c'); 
    
    Cell testObject_6(9,'b');
   
    Cell yourTestObject;
    
       
    cout << "\nCell testObject_1(4,'c')" << endl;
    cout << "Cell testObject_2(1,'c')" << endl;
    cout << "Cell testObject_3(4,'d')" << endl;
    cout << "Cell testObject_4(7,'e')" << endl;
    cout << "Cell testObject_5(4,'c')" << endl;
    cout << "Cell testObject_6(9,'b')" << endl;
    
    cout << "\nTest Results" << endl;
    
    if ( testObject_2 < testObject_3) {
    cout << "\ntestObject_2 < testObject_3 " << endl;
    }
    
    if ( testObject_3 != testObject_5) {
    cout << "\ntestObject_3 != testObject_5 " << endl;
    }
      
    if (testObject_4 < testObject_6){
    cout << "\ntestObject_4 < testObject_6 " << endl;
    }
    
    if (testObject_1 >= testObject_5) {
    cout << "\ntestObject_1 >= testObject_5" << endl;
    }
    
    
    cout << "\nEnter your Cell object x and y coordinates: " << endl; 
    // Stream extraction operator overloading
    cin >> yourTestObject;
    
    cout << "\nYour Cell object coordinates: " << endl; 
    
    // Stream insertion operator overloading
    cout << yourTestObject << endl;
   
    
    cout << "Prefix overload on testObject_1 " << endl;
    // Prefix operator overloading
    Cell a = ++testObject_1;
    cout << a.getXposition() << " " << a.getYposition() << endl << endl;
  
    cout << "Postfix overload on testObject_4 " << endl;
    // Postfix operator overloading
    Cell b = testObject_4++;
    cout << testObject_4.getXposition() << " " << testObject_4.getYposition() << endl << endl;
      
}

// Stream insertion operator overload
ostream& operator <<(ostream& outputStream, const Cell& cell)
{

    outputStream << cell.xPos << " " << cell.yPos << endl;
    
    return outputStream;

}

// Stream extraction operator overload
istream& operator >>(istream& inputStream, Cell& cell)
{
    int  x;
    char y;
    
    inputStream >> x >> y;
    
    cell.xPos = cell.xPart(x);
    cell.yPos = cell.yPart(y);
    
    
    return inputStream;

}

// Prefix OPERATOR
Cell Cell::operator++()
{

    xPos++;    
    yPos++;
       
    return Cell(xPos, yPos);


}

// POstfix OPERATOR
Cell Cell::operator++(int ignoreMe)
{

    int tempX = xPos++;
    
    int tempY = yPos++;
        
    return Cell(tempX, tempY);


}

// " < " OPERATOR
bool operator <(const Cell& cell_1, const Cell& cell_2 )
{

    if ( cell_1.getYposition() < cell_2.getYposition()   )

    return true;
    
    
    else if ( (cell_1.getYposition() == cell_2.getYposition() )   &&   ( cell_1.getXposition() < cell_2.getXposition()  )  )
            
    return true;
    
    
    else 
    
    return false;
      
}

// " > " OPERATOR
bool operator >(const Cell& cell_1, const Cell& cell_2 )
{

    if ( cell_1.getYposition() > cell_2.getYposition()   )

    return true;
    
       
    else if ( (cell_1.getYposition() == cell_2.getYposition() )   &&   ( cell_1.getXposition() > cell_2.getXposition()  )  )
            
    return true;
    
       
    else 
    
    return false;
    
}

// " <= " OPERATOR
bool operator <=(const Cell& cell_1, const Cell& cell_2 )
{

    if (  ( cell_1.getYposition() < cell_2.getYposition() )  || (cell_1.getYposition() == cell_2.getYposition() ) )

    return true;
    
  
    else 
    
    return false;
    
   

}

// " >= " OPERATOR
bool operator >=(const Cell& cell_1, const Cell& cell_2 )
{

   if (  ( cell_1.getYposition() > cell_2.getYposition() )  || (cell_1.getYposition() == cell_2.getYposition() ) )

    return true;
    
    
    else 
    
    return false;
    
}

// " == " OPERATOR
bool operator ==(const Cell& cell_1, const Cell& cell_2 )
{

   if (  ( cell_1.getYposition() == cell_2.getYposition() )  && (cell_1.getXposition() == cell_2.getXposition() ) )

    return true;
    
    
    else 
    
    return false;
    
   

}

// " != " OPERATOR
bool operator !=(const Cell& cell_1, const Cell& cell_2 )
{

   if (  ( cell_1.getYposition() != cell_2.getYposition() )  || (cell_1.getXposition() != cell_2.getXposition() ) )

    return true;
        
    else 
    
    return false;
    
   

}


// No parameter Constructor 
Cell::Cell()
{
    xPos=0;
    yPos='0';
}
 

// One parameter constructor to xPosition 
Cell::Cell(int xPosition)
{

    xPos = xPosition;
   
}
 

// Consruct to cell x and y coordinates 
Cell::Cell(int xPosition,char yPosition)
{
    xPos = xPosition;
    yPos = yPosition;
}
 


