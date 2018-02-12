
#ifndef COMPUTER_H__
#define COMPUTER_H__

#include<iostream>
#include<string>
#include<sstream>



using namespace std;
using std::string;



class Computer {
    
    public:
       Computer();
       Computer(int option);
       Computer(CPU otherCPUObject, CPUProgram otherCPUProgramObject, Memory otherMemoryObject, int option );
       
       void setCPU(CPU newComputerObject) {computerCPUobject = newComputerObject ;}
       void setCPUProgram(CPUProgram newComputerObject){computerCPUProgramObject = newComputerObject;}
       void setMemory(Memory newComputerObject) {computerMemoryObject = newComputerObject ;}
       
       
       CPU getCPU()               {return computerCPUobject; }
       CPUProgram getCPUProgram() {return computerCPUProgramObject; } 
       Memory getMemory()         {return computerMemoryObject; }
       
       
       void execute();
       
    private:
        
       CPU computerCPUobject;
       Memory computerMemoryObject;
       CPUProgram computerCPUProgramObject;
       int chooseOption;
};




#endif