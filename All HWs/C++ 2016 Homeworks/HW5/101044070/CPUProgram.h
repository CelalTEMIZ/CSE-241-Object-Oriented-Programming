
#ifndef CPUPROGRAM_H__
#define CPUPROGRAM_H__

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<stdlib.h>


using namespace std;
using std::string;



class CPUProgram {
    
    public:
        CPUProgram();
        CPUProgram(int option);
        CPUProgram(string inputFileName);
        int size();        
        void ReadFile(string inputFileName);
        string getLine(int returnProgLine);
       
        void setSizeOfFile() {numberOfLine=0;}
        
        int getNumberOfLine() {return numberOfLine;}
        void setNumberOfLine(int lineOfInput) {numberOfLine = lineOfInput; }
        
        bool operator <(const CPUProgram& object);
        bool operator >(const CPUProgram& object);
        bool operator >=(const CPUProgram& object);
        bool operator <=(const CPUProgram& object);
        bool operator ==(const CPUProgram& object);
        bool operator !=(const CPUProgram& object);
        
        CPUProgram& operator+(CPUProgram & object);
        CPUProgram& operator+(const string addNewLine);
        CPUProgram& operator+=(const string addNewLine);
        
        
        CPUProgram operator()(int firstPosition, int lastPosition);
        string operator[](int index);
        
        friend ostream& operator <<(ostream& outputStream, const CPUProgram& object);
       
        
        CPUProgram operator --();             //Prefix
        CPUProgram operator --(int);          //Postfix
        
        
    private: 
        
        vector<string>storeAllRegisters;
        int numberOfLine;
        int chooseOption;
      
};




#endif
