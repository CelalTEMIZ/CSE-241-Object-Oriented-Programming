
#ifndef CPUPROGRAM_H__
#define CPUPROGRAM_H__

#include <iostream>
#include<string>
#include<sstream>



using namespace std;
using std::string;


class CPUProgram {
    
    public:
        
        CPUProgram(string inputFileName);
        int size(ifstream *inputFile);        
        void readFile(string inputFileName);
        string getLine(int returnProgLine);
        
   
    private:
        
        string storeAllRegisters[200];
};


#endif
