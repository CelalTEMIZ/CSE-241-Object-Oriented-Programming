
#ifndef CPU_H__
#define CPU_H__

#include <iostream>
#include<string>
#include<sstream>

using namespace std;
using std::string;


class CPU {

    public:
    
        // Constructors for all register and PC
        CPU();
        CPU(int oneValue);
        CPU(int oneValue, int secondValue);
        CPU(int oneValue, int secondValue, int thirdValue);
        CPU(int oneValue, int secondValue, int thirdValue, int fourthValue);
        CPU(int oneValue, int secondValue, int thirdValue, int fourthValue, int fifthValue);
        
        
    
        // Setter functions
        void setRegisters(int registerValue, int newIndexOfRegister) {registers[newIndexOfRegister]=registerValue;}   
        void setPC(int newProgramCounter) {PC = newProgramCounter;}
        void setFlag(int newFlagValue) {flag = newFlagValue;}
       
        // Getter functions 
        const int getRegister(int newIndexOfRegister) const {return registers[newIndexOfRegister];}
        const int getPC() const {return PC;}
        
        void print(); 
        bool halted();
        void execute(string instructionLine);
        
        void addOperation(string tokenRegister, int integerValue, string token2Register);
        void subOperation(string tokenRegister, int integerValue, string token2Register);
        void movOperation(string tokenRegister, int integerValue, string token2Register);
        void jmpOperation(string tokenConstantOrRegister,int integerValue);
        void prnOperation(string tokenRegister);
        
    private:
    
        // Register Array and PC
        int registers[6];
        int PC;
	    int flag; 
};




#endif

