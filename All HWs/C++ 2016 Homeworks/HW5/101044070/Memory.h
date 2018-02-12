
#ifndef MEMORY_H__
#define MEMORY_H__

#include<iostream>
#include<string>
#include<sstream>


using namespace std;
using std::string;


class Memory {
    
    public:
        
        Memory();
        Memory(int option);
        
        void setMem(int indexValue, int integerValue) { address[indexValue]=integerValue;}
        int getMem(int indexValue) {return address[indexValue];}
        
        void printAll();
        void prnAddressContent(int prnAddress);
   
    private:
        
        unsigned int address[50];
        int choseOption;
};

#endif