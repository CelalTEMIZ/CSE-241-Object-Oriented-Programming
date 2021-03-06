#include<iostream>
#include<string>
#include<fstream>


#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"
#include "Computer.h"

using namespace std;



Computer::Computer()
{
}

Computer::Computer(int option)
{
    chooseOption = option;
	
}

Computer::Computer(CPU otherCPUObject, CPUProgram otherCPUProgramObject, Memory otherMemoryObject, int option )
{
    computerCPUobject = otherCPUObject;
    computerCPUProgramObject = otherCPUProgramObject;
    computerMemoryObject = otherMemoryObject;
    chooseOption = option; 
}

void Computer::execute()
{

    while(!computerCPUobject.halted()) 
    {
  
                        string instruction = computerCPUProgramObject.getLine( computerCPUobject.getPC());
                        computerCPUobject.execute(instruction, computerMemoryObject);
                        computerCPUobject.print();                           
    
    }	
	
}


