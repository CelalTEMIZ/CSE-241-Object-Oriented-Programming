#include "Cell.h"

using namespace std;


Cell::Cell(){
    
  xPos = 0;
  yPos = NULL;
    
}

Cell::Cell(int Xposition){
    
    xPos = 0;
}

Cell::Cell(int Xposition, char Yposition)
{
  xPos = Xposition;
  yPos = Yposition;  
}
