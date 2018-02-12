/*******************************************************************/
/*	Object Oriented Programming							           */
/*	Fall 2014									                   */
/*	Homework # 5									               */
/*  															   */
/*  CELAL TEMİZ                                                    */
/* 	101044070											           */
/*																   */
/*******************************************************************/
//For the Cell class, overload the following operators
//<, >, >= , >=, == and != for comparing two Cells. One Cell object is smaller than the
//other if the Y components is smaller. If Y components are equal, then check the X component.
//Operators ++ and - - that increment and decrement the X and Y components by one. Overload both
//prefix and postfix operators.
//Stream insertion and extraction operators



#include<iostream>

using namespace std;

/* The Cell class hold the X and Y positions of the cell */

class Cell
{

    public:
    
        /* Constructors default and two parameters */
        Cell();
        Cell(int xPosition);
        Cell(int xPosition, int yPosition);
        
    
        /* Setter function */
        void setX(int newX) {xPos = newX;}
        void setY(int newY) {yPos = newY;}
       
        /* Getter functions */
        int getXposition() const {return xPos;}
        int getYposition() const {return yPos;}
        
   
    
        /* Operator Overloading */    
         
        friend bool operator <(const Cell& cell_1, const Cell& cell_2 );
        friend bool operator >(const Cell& cell_1, const Cell& cell_2);
        friend bool operator >=(const Cell& cell_1, const Cell& cell_2);
        friend bool operator <=(const Cell& cell_1, const Cell& cell_2);
        friend bool operator ==(const Cell& cell_1, const Cell& cell_2);
        friend bool operator !=(const Cell& cell_1, const Cell& cell_2);       
        friend ostream& operator <<(ostream& outputStream, const Cell& cell);
        friend istream& operator >>(istream& inputStream, Cell& cell);        
        Cell operator ++();      //Prefix
        Cell operator ++(int);  //Postfix
         
        
        void testFunction(); 
 
    private:
    
        /* Cell position on x and y coordinates */
        
        int xPos;
        int yPos;  

        int xPart(int cell)const {return cell;}
        int yPart(int cell)const {return cell;}

};



int main()
{

    // Cell object to test Function

    Cell testObjects;

    testObjects.testFunction();
    
    
        return 0;
}


void Cell::testFunction()
{

    // Test Objects

    Cell testObject_1(4,1);
    
    Cell testObject_2(1,1);
    
    Cell testObject_3(4,7);
    
    Cell testObject_4(7,9);
    
    Cell testObject_5(4,1); 
    
    Cell testObject_6(9,9);
   
    Cell yourTestObject;
    
    
    
    cout << "\nCell testObject_1(4,1)" << endl;
    cout << "Cell testObject_2(1,1)" << endl;
    cout << "Cell testObject_3(4,7)" << endl;
    cout << "Cell testObject_4(7,9)" << endl;
    cout << "Cell testObject_5(4,1)" << endl;
    cout << "Cell testObject_6(9,9)" << endl;
    
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
    
    cout << "Your Cell object coordinates: " << endl;
    
    // Stream insertion operator overloading
    cout << yourTestObject << endl;
   
    // Prefix operator overloading
    
    cout << "Prefix overload on testObject_1 " << endl;
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

// Stream extractin operator overload
istream& operator >>(istream& inputStream, Cell& cell)
{

    int x,y;
    
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


/* No parameter Constructor */
Cell::Cell()
{
    xPos=0;
    yPos=0;
}

/* One parameter constructor to xPosition */
Cell::Cell(int xPosition)
{

    xPos = xPosition;
   
}

/* Consruct to cell x and y coordinates */
Cell::Cell(int xPosition,int yPosition)
{
    xPos = xPosition;
    yPos = yPosition;
}


