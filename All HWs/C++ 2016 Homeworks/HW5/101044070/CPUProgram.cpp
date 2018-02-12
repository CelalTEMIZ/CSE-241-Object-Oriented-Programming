
#include<iostream>
#include<string>
#include<fstream>


#include "CPUProgram.h"


using namespace std;

CPUProgram::CPUProgram()
{
}

CPUProgram::CPUProgram(int option)
{

    chooseOption = option;
}

CPUProgram::CPUProgram(string inputFileName)
{
    ReadFile(inputFileName);
}


void CPUProgram::ReadFile(string inputFileName)
{
   
    string line;
   
    const char *cInputFile = inputFileName.c_str();
    
    ifstream inputFile (cInputFile);  
 
    int i=0,flag=0;
    while (!inputFile.eof()) 
    {
            getline(inputFile, line);
            
            string newLine;
            for(int j=0;j<line.length();j++)
            {
                if(line[j]==';')
                {
                    for(int k=0;k<j;k++)
                    {
                            
                    flag=1;        
                    newLine+=line[k];
                    
                    }
                    break;
                    
                }
                
                
            }

            ++numberOfLine;
            if(flag==1)
            storeAllRegisters.push_back(newLine);
            else
            storeAllRegisters.push_back(line);
           
            
            
            ++i;
            flag=0;
        }       
       // cout<<storeAllRegisters[3]<<storeAllRegisters[4];
    
    inputFile.close();   
}

int CPUProgram::size()
{

  return storeAllRegisters.size();
}

string CPUProgram::getLine(int returnProgLine)
{
    return storeAllRegisters[returnProgLine];
}



// Stream extraction operator overload
// Print the program

ostream& operator <<(ostream& outputStream,const CPUProgram& object)
{
    
    for (int i=0; i<object.storeAllRegisters.size(); ++i) {
    
        outputStream << object.storeAllRegisters[i] << endl;
   
    }
    
    return outputStream;

}

// Prefix OPERATOR
CPUProgram CPUProgram::operator--()
{

  storeAllRegisters.pop_back();     
  numberOfLine--;
  
  return *this;
}

// POstfix OPERATOR
CPUProgram CPUProgram::operator--(int ignoreMe)
{
    CPUProgram cpuProg;
    for(int i=0;i<storeAllRegisters.size();i++)
    {
    cpuProg.storeAllRegisters.push_back(storeAllRegisters.at(i));
    }
    numberOfLine--;

    storeAllRegisters.pop_back();     
    
    return cpuProg;
}

// Index OPerator
string CPUProgram::operator[](int index)
{
    //BAKILACAK
    if(index>=storeAllRegisters.size())
    {
      cout<<"Program terminated";  
      return "";
    }
    
    return storeAllRegisters[index];
}

// " < " OPERATOR
bool CPUProgram::operator <(const CPUProgram& object)
{

    if ( numberOfLine < object.numberOfLine)

        return true;
    
    else 
    
        return false;
      
}

// " > " OPERATOR
bool CPUProgram::operator >(const CPUProgram& object )
{

    if (numberOfLine > object.numberOfLine)

        return true;
    
    else 
    
        return false;
    
}

// " <= " OPERATOR
bool CPUProgram::operator <=(const CPUProgram& object)
{

    if ( numberOfLine <= object.numberOfLine)

        return true;
      
    else 
    
        return false;

}

// " >= " OPERATOR
bool CPUProgram::operator >=(const CPUProgram& object)
{

    if ( numberOfLine >= object.numberOfLine)

        return true;
       
    else 
    
        return false;
    
}

// " == " OPERATOR
bool CPUProgram::operator ==(const CPUProgram& object)
{

   if (numberOfLine == object.numberOfLine)

        return true;
    
   else 
    
        return false;
 
}

// " != " OPERATOR
bool CPUProgram::operator !=(const CPUProgram& object)
{

   if (numberOfLine != object.numberOfLine )

        return true;
        
   else 
    
        return false;
}
CPUProgram& CPUProgram::operator +(CPUProgram& object)
{
    for(int k=0;k<object.storeAllRegisters.size();k++)
    {
        storeAllRegisters.push_back(object.storeAllRegisters.at(k));
    }
        
    return *this;
    
}

CPUProgram& CPUProgram::operator+(const string addNewLine)
{
      storeAllRegisters.push_back(addNewLine);
      
      return *this;
}
CPUProgram& CPUProgram::operator +=(const string addNewLine)
{
     storeAllRegisters.push_back(addNewLine);
      
      return *this;
}

CPUProgram CPUProgram::operator()(int firstPosition, int lastPosition)
{
    CPUProgram newProgram; 
    
    for(int i=0;i<storeAllRegisters.size();i++)
    newProgram.storeAllRegisters.push_back(storeAllRegisters.at(i));
  
    
    for(int i=0;i<firstPosition;i++)
    {
        newProgram.storeAllRegisters.erase(newProgram.storeAllRegisters.begin());
    }
    
    for(int i=lastPosition;i<storeAllRegisters.size()-1;i++)
    {
        newProgram.storeAllRegisters.pop_back();
    }

    return newProgram;
    
}