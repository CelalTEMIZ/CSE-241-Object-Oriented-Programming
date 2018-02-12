/* 
 * File:   Cell.h
 * Author: celal
 *
 * Created on November 21, 2015, 10:21 PM
 */

#ifndef CELL_H
#define	CELL_H

#include<iostream>

using namespace std;

class Cell
{
        public:
    
            Cell();
            Cell(int Xposition);
            Cell(int Xposition, char Yposition);

            void setX(int  Xposition) {xPos = Xposition;}
            void setY(char Yposition) {yPos = Yposition;}
        
            const int getXPosition()const {return xPos;}
            const char getYPosition()const {return yPos;}
                         
        private:
            int  xPos;
            char yPos;
    
};


#endif	/* CELL_H */

