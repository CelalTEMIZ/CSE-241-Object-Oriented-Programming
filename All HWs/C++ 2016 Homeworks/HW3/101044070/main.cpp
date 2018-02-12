#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include "CPU.h"
#include "CPUProgram.h"

using namespace std;



int main(int argc, char **argv)
{
        
    string fileName = argv[1];
    char option = argv[2][0];
    
     // Program Usage
        if(argc < 3 || argc > 3) {        
            cout << "Usage : ./yourProg filename option\n";
            return -1;
        }
 
  
  // if option is 1, program will execute each instruction after displaying the instruction first.
  // or program will run and finish by executing each instructions


      if(argv[2][0]!='0' && argv[2][0]!='1') {
      
        cout << "Program option must be 0 or 1 \n";
                return -1;
      }
    
    CPUProgram myProg(fileName);
    CPU myCPU;
    
    
    myCPU.setPC(0);
    myCPU.setFlag(0); 
     
    while (!myCPU.halted()) {              
  
                                  string instruction = myProg.getLine(myCPU.getPC());
                                  myCPU.execute(instruction);
                                  if(option=='1') {
                                    myCPU.print();
                                  }
                        
       } 
    

    return 0;
}


