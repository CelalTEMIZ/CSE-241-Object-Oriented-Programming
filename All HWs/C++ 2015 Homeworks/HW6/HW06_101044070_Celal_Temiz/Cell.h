#ifndef CELL_H
#define	CELL_H

#include<iostream>

using namespace std;

class Cell
{

    public:
    
        /* Constructors default and two parameters */
        Cell();
        Cell(int xPosition);
        Cell(int xPosition, char yPosition);
        
    
        // Setter function 
        void setX(int newX) {xPos = newX;}
        void setY(char newY) {yPos = newY;}
        void setXY(int newX, char newY){xPos=newX; yPos=newY;}
       
        // Getter functions 
        int getXposition()  const {return xPos;}
        char getYposition() const {return yPos;}
        
   
    
        // Operator Overloading     
         
        friend bool operator <(const Cell& cell_1, const Cell& cell_2 );
        friend bool operator >(const Cell& cell_1, const Cell& cell_2);
        friend bool operator >=(const Cell& cell_1, const Cell& cell_2);
        friend bool operator <=(const Cell& cell_1, const Cell& cell_2);
        friend bool operator ==(const Cell& cell_1, const Cell& cell_2);
        friend bool operator !=(const Cell& cell_1, const Cell& cell_2);       
        friend ostream& operator <<(ostream& outputStream, const Cell& cell);
        friend istream& operator >>(istream& inputStream, Cell& cell);        
        Cell operator ++();             //Prefix
        Cell operator ++(int);          //Postfix
         
        void testFunction(); 
 
    private:
    
        // Cell position on x and y coordinates 
        
        int xPos;
        char yPos;  

        int xPart(int cell)const {return cell;}
        int yPart(char cell)const {return cell;}

};

#endif	/* CELL_H */

