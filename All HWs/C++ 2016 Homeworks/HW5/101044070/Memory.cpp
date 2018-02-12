
#include<iostream>
#include<string>
#include<fstream>


#include "Memory.h"


using namespace std;



Memory::Memory() 
{
  
}

Memory::Memory(int option)
{
   for(int i=0; i<50; ++i) {
        address[i] = 0;
   }
        
    choseOption = option;   
}  

void Memory::printAll()
{

    for(int i=0; i<50; ++i)
        cout << "[" << i << "] " << "-> " << address[i] << endl;
}


void Memory::prnAddressContent(int prnAddress)
{
 
    cout << "PRN " << "#" << prnAddress << "  -Memory["<<prnAddress<<"] = "<< getMem(prnAddress) << endl;  

}

