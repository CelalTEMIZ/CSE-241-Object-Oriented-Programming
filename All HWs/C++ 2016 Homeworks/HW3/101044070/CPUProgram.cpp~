#include<iostream>
#include<string>
#include<fstream>

#include "CPUProgram.h"


using namespace std;



CPUProgram::CPUProgram(string inputFileName)
{
    readFile(inputFileName);
}



void CPUProgram::readFile(string inputFileName)
{
   
    string line;
   
    int numberOfLines;
    const char *cInputFile = inputFileName.c_str();
    
    ifstream inputFile (cInputFile);   
    
    numberOfLines = size(&inputFile);
      
    
    inputFile.clear();
    inputFile.seekg (0, inputFile.beg);
 
 
    if (inputFile.is_open()) {
        for(int i=0; i<numberOfLines; ++i) {
            getline(inputFile, line);
            storeAllRegisters[i] = line;
            
        }         
   }
  
   inputFile.close();   
}

int CPUProgram::size(ifstream *inputFile)
{

  string newLine;
  int lineNumber=0;
  
  while (getline(*inputFile, newLine)) {
        ++lineNumber;
  } 
   
  return lineNumber;
}

string CPUProgram::getLine(int returnProgLine)
{
    return storeAllRegisters[returnProgLine];
}




