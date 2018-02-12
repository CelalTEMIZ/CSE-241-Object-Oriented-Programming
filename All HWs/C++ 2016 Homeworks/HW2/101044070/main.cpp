/********************************************************************************/
/*	Object Oriented Programming							                        */
/*	Fall 2016									                                */
/*	Homework # 2									                            */
/*	                                                                            */
/*  CELAL TEMİZ                                                                 */
/* 	101044070											                        */
/*                                                                              */
/* if option is 0,program will run and finish by executing each instruction     */
/*                                                                              */
/* if option is 1,program will execute each instruction after displaying        */ 
/* the instruction first. It also will print the contents of all the registers. */
/*                                                                              */
/* If option is 2,program will execute each instruction just like the           */
/* option 1. This option will also print the contents of the memory after each  */
/* instruction execution.                                                        */
/********************************************************************************/


// Run program
//
//  make
// ./yourProg filename option


#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

// Global Variables
string tokenRegister, tokenInstruction , 
       token2Register, addressPart, movSecondOperandRegister,movSecondOperandConstant,
       movSecondOperandAddress, addSecondOperandAddress, subSecondOperandAddress;

int integerValue, integerAddress, movAddressConstant, addAddress, subAddress,
    prnAddress, addressFirst;

char option;


// Registers
int R1=0, R2=0, R3=0, R4=0, R5=0;
int firstAddressOperand;

size_t pos=0;

string delimeter = " ";
string delimeterSharp = "#";
string delimeterSpaceSharp =" #";

// Memory Addressses
unsigned int address[50];

// Operations
void addOperation(char option);
void subOperation(char option);
void movOperation(string tokenInstruction, char option);
void prnOperation(char option);
void jmpOperation(ifstream *inputFile, string tokenConstantOrRegister,int value, char option);

// Address Operations
int addressParser(string addressPart);
void movRegToAddress(string movSecondOperandAddress, char option);
void movAddressToReg(int firstAddressOperand, string movSecondOperandRegister, char option);
void movConstantToAddress(int firstAddressOperand, string movSecondOperandConstant, char option);
void addRegToAddress(string tokenRegister, string addSecondOperandAddress, char option);
void subRegToAddress(string tokenRegister, string subSecondOperandAddress, char option); 
void prnAddressContent(int prnAddress, char option);
void jpnOperation(ifstream *inputFile, string tokenConstantOrRegister,int value, char option);

int main(int argc, char **argv)
{

  string line, copyLine;

  string tokenConstantOrRegister, MOV="MOV", PRN="PRN", SUB="SUB",ADD ="ADD",JMP="JMP", HLT="HLT", JPN="JPN";

  // File Operation
  
  ifstream inputFile (argv[1]);
  
  // Program Usage
        if(argc < 3 || argc > 3) {        
            cout << "Usage : ./yourProg filename option\n";
            return -1;
        }
 
  
  // Check program option 
  if(argv[2][0]!='0' && argv[2][0]!='1' && argv[2][0]!='2') {
  
    cout << "Program option must be 0, 1, 2" << endl;
    return -1;
  }

    // Option assignment
    option = argv[2][0];

    if (inputFile.is_open()) {
  
          while( !inputFile.eof()) {
          
                        while (getline (inputFile,line) ) {                     // Read line from sample input file
                                        
                                  
                                  if(line == "") {
                                                                                // If first line is empty then break
                                    break;
                                  }
                                  
                                  else {                                       
                                                                                 // Pars operation
                                   while((pos=line.find(delimeter)) !=std::string::npos) {
                                    
                                           // Finding instruction                                
                                           tokenInstruction = line.substr(0,pos);                                      

                                           if(tokenInstruction=="") {break; }
                                                                                  
                                           else {
                                               line.erase(0,pos+delimeter.length());

                                                // Finding register to mov
                                               if (tokenInstruction==MOV) { 

                                               tokenRegister = line.substr(0,pos); 
                                                  // If first operand is address to mov instruction
                                                  if(tokenRegister[0]=='#') { 
                                                       firstAddressOperand = addressParser(tokenRegister);
                                                       movSecondOperandRegister = line;
                                                       pos=movSecondOperandRegister.find(delimeter);
                                                       movSecondOperandRegister.substr(0,pos);
                                                       movSecondOperandRegister.erase(0,pos+delimeter.length());

                                                       // If second operand is register to mov instruction
                                                       if(movSecondOperandRegister[0]=='R') {
                                                            movAddressToReg(firstAddressOperand, movSecondOperandRegister,option); 
                                                       }
                                                       else {
                                                            // If second operand is constant to mov instruction
                                                            movSecondOperandConstant = movSecondOperandRegister; 
                                                            movConstantToAddress(firstAddressOperand,movSecondOperandConstant,option);
                                                       }     
                                                  }
                                               // Last part
                                               line.erase(0,pos+delimeter.length());
                                               }
                                               // Finding register to prn
                                               else if (tokenInstruction==PRN) {                                                 
                                                    tokenRegister = line.substr(0,pos);
                                         
                                                  if(tokenRegister[0]=='#') { 
                                                      prnAddress = addressParser(tokenRegister);
                                                      prnAddressContent(prnAddress,option);     
                                                  }
                                                line.erase(0,pos+delimeter.length());                                                
                                               }
                                              // Finding register to sub
                                               else if (tokenInstruction==SUB) { 
                                                    tokenRegister = line.substr(0,pos);
                                                    line.erase(0,pos+delimeter.length());
                                                    // If second operand is address to sub instruction
                                                     if(line[0]=='#') {
                                                       subSecondOperandAddress = line;
                                                       delimeterSharp = "#";
                                                       pos=subSecondOperandAddress.find(delimeterSharp);
                                                       subSecondOperandAddress.substr(0,pos);
                                                       subSecondOperandAddress.erase(0,pos+delimeterSharp.length());
                                                       subRegToAddress(tokenRegister,subSecondOperandAddress,option); 
                                                     }
                                               }
                                               // Finding register to add
                                                else if (tokenInstruction==ADD) { 
                                                    tokenRegister = line.substr(0,pos);
                                                    // R2,
                                                    line.erase(0,pos+delimeter.length());
                                                    // #10 
                                                    // If second operand is address to add instruction
                                                    if(line[0]=='#') {
                                                       addSecondOperandAddress = line;
                                                       delimeterSharp = "#";
                                                       pos=addSecondOperandAddress.find(delimeterSharp);
                                                       addSecondOperandAddress.substr(0,pos);
                                                       addSecondOperandAddress.erase(0,pos+delimeterSharp.length());
                                                       addRegToAddress(tokenRegister,addSecondOperandAddress,option); 
                                                    }
                                               }

                                               // Finding register to jmp
                                               else if (tokenInstruction==JMP) {                            
                                                        tokenConstantOrRegister = line.substr(0,pos);       
                                                    if(tokenConstantOrRegister[0] == 'R') {
                                                        line.erase(0,pos+delimeter.length());
                                                    
                                                    }
                                               }
                                               
                                                else if (tokenInstruction==JPN) {                            
                                                        tokenConstantOrRegister = line.substr(0,pos);       
                                                            if(tokenConstantOrRegister[0] == 'R') {
                                                                 line.erase(0,pos+delimeter.length());
                                                    }
                                               }
                                           }
                                   // HLT Operation
                                   if(line[0]==' ') {
                                        if(tokenInstruction==HLT) {
                                            if(option=='1' || option=='2') {
                                                cout << "HLT "<< "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
                                                     << " R4=" << R4 << "," " R5=" << R5 << endl;}
                                              }
                                   }
                                   else {
                                       
                                       if(line==HLT) {cout << "HLT" << endl;}
                                       else if(line[0]=='R') {
                                            token2Register = line.substr(0,pos);
                                       }
                                   
                                       // If second operand is address to mov instruction
                                       else if (line[0]=='#') {
                                           movSecondOperandAddress = line;
                                           delimeterSharp = "#";
                                           pos=movSecondOperandAddress.find(delimeterSharp);
                                           movSecondOperandAddress.substr(0,pos);
                                           movSecondOperandAddress.erase(0,pos+delimeterSharp.length());
                                           movRegToAddress(movSecondOperandAddress,option);
                                       }
                                       else if(line[0]!='R') {
                                       }  
                                   }                                   
                                   // Convert string to integer
 
                                   stringstream ss(line);                                                      
                                   ss >> integerValue;
       
                                  // Operation functions without address
                                                if (tokenInstruction==ADD) {                                                    
                                                    if(line[0]!='#') {
                                                        addOperation(option);
                                                    }
                                                } 
                                       
                                                if (tokenInstruction==SUB ) {                                               
                                                    if(line[0]!='#') {
                                                        subOperation(option);
                                                    }
                                                   
                                                }     
                                                if (tokenInstruction==MOV ) {                                               
                                                    if(line[0]!='#') {
                                                        if(tokenRegister[0] == 'R') {
                                                            movOperation(token2Register,option); 
                                                        }           
                                                    }
                                                                
                                                }        
                                                if (tokenInstruction==PRN ) {
                                                     if (tokenRegister[0]!='#') {
                                                      prnOperation(option);            
                                                    }    
                                                }
                                                  
                                                if (tokenInstruction==JMP) {
                                                    jmpOperation(&inputFile,tokenConstantOrRegister,integerValue,option);
                                                }
                                               
                                                if (tokenInstruction==JPN) {
                                                    jpnOperation(&inputFile,tokenConstantOrRegister,integerValue,option);
                                                }  
                                               
                                      token2Register.clear();
                                   }                                     
                                 }       
          
     } 
     }
  }

 // File error message
  else {  
    cout << "Unable to open file";  
  }

  // Close input file
  inputFile.close();


    return 0;
}

// If first operand is address, make parse
int addressParser(string addressPart)
{
   delimeterSharp = "#";
   pos=addressPart.find(delimeterSharp);
   addressPart.substr(0,pos);
   addressPart.erase(0,pos+delimeterSharp.length());
     
   stringstream ss(addressPart);                                                      
   ss >> addressFirst; 
    
   return addressFirst;
}

// Add Operation, from register to address
void addRegToAddress(string tokenRegister, string addSecondOperandAddress, char option)
{
   stringstream ss(addSecondOperandAddress);                                                      
   ss >> addAddress; 
   
    if(tokenRegister[0]=='R' && tokenRegister[1]=='1') {R1 = R1 + address[addAddress];}          
      else if(tokenRegister[0]=='R' && tokenRegister[1]=='2') {R2 = R2 + address[addAddress];}         
      else if(tokenRegister[0]=='R' && tokenRegister[1]=='3') {R3 = R3 + address[addAddress];}                   
      else if(tokenRegister[0]=='R' && tokenRegister[1]=='4') {R4 = R4 + address[addAddress];}                            
      else if(tokenRegister[0]=='R' && tokenRegister[1]=='5') {R5 = R5 + address[addAddress];} 
      
      if(option=='1' || option=='2') {
        cout << "ADD " << tokenRegister<< " #" << addAddress <<  "-" << "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
             << " R4=" << R4 << "," " R5=" << R5 <<" -Memory[" << addAddress << "] " << endl;   
      }    
}

// Sub operation, from register to address
void subRegToAddress(string tokenRegister, string subSecondOperandAddress, char option)
{
   stringstream ss(subSecondOperandAddress);                                                      
   ss >> subAddress; 
   

    if(tokenRegister[0]=='R' && tokenRegister[1]=='1') {R1 = R1 - address[subAddress];}          
      else if(tokenRegister[0]=='R' && tokenRegister[1]=='2') {R2 = R2 - address[subAddress];}         
      else if(tokenRegister[0]=='R' && tokenRegister[1]=='3') {R3 = R3 - address[subAddress];}                   
      else if(tokenRegister[0]=='R' && tokenRegister[1]=='4') {R4 = R4 - address[subAddress];}                            
      else if(tokenRegister[0]=='R' && tokenRegister[1]=='5') {R5 = R5 - address[subAddress];} 
     
     if(option=='1' || option=='2') {
     
         cout << "SUB " << tokenRegister<< " #" << subAddress <<  "-" << "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
             << " R4=" << R4 << "," " R5=" << R5 << " -Memory[" << integerAddress << "] " << endl;  
    }
}


// Operation ADD without address
void addOperation(char option)
{
   
    // ADD R1, 5         
    if(integerValue!=0){
        if(tokenRegister[0]=='R' && tokenRegister[1]=='1') { R1 = R1 + integerValue;}               
        else if(tokenRegister[0]=='R' && tokenRegister[1]=='2') { R2 = R2 + integerValue;}         
        else if(tokenRegister[0]=='R' && tokenRegister[1]=='3') { R3 = R3 + integerValue;}               
        else if(tokenRegister[0]=='R' && tokenRegister[1]=='4') { R4 = R4 + integerValue;}                             
        else if(tokenRegister[0]=='R' && tokenRegister[1]=='5') { R5 = R5 + integerValue;} 
    } else {
      
     // ADD R1, R2
     if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='2') { R1 = R1+R2;}        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='3') { R1 = R1+R3;}      
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='4') { R1 = R1+R4;}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='5') { R1 = R1+R5;}
                
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='1') { R2 = R2+R1;}        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='3') { R2 = R2+R3;} 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='4') { R2 = R2+R4;}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='5') { R2 = R2+R5;} 
       
       
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='1') {R3=R3+R1;}        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='2') {R3 = R3+R2;} 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='4') {R3 = R3+R4;}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]!='5') {R3 = R3+R5;} 
           
       
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='1') {R4=R4+R1;}        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='2') {R4 = R4+R2; } 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='3') { R4 = R4+R3;}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='5') {R4 = R4+R5; }
         
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='1') {R5=R5+R1; }        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='2') {R5 = R5+R2; } 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='3') {R5 = R5+R3;}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='4') {R5 = R5+R4; }     

}

 if(option=='1' || option=='2') {

    // Print result for instruction and register
    if(token2Register[0]=='R') {
        cout << "ADD " << tokenRegister<< " " << token2Register << "-" << "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
             << " R4=" << R4 << "," " R5=" << R5 << endl;   
       }
       
    else {   
        cout << "ADD " << tokenRegister<< " " << integerValue << "-" << "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
             << " R4=" << R4 << "," " R5=" << R5 << endl;
    }
    
    }   
}

// Operation SUB without address
void subOperation(char option)
{  
     if(integerValue!=0){                                  
        if(tokenRegister[0]=='R' && tokenRegister[1]=='1') {R1 = R1 - integerValue; }      
        else if(tokenRegister[0]=='R' && tokenRegister[1]=='2') { R2 = R2 - integerValue;}     
        else if(tokenRegister[0]=='R' && tokenRegister[1]=='3') {R3 = R3 - integerValue;}    
        else if(tokenRegister[0]=='R' && tokenRegister[1]=='4') {R4 = R4 - integerValue; }                     
        else if(tokenRegister[0]=='R' && tokenRegister[1]=='5') {R5 = R5 - integerValue;}        
     }

    else { 
       if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='2') {R1 = R1-R2; }           
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='3') {R1 = R1-R3;} 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='4') {R1 = R1-R4;}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='5') {R1 = R1-R5;} 

         else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='1') {R2=R2-R1;}        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='3') {R2 = R2-R3;} 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='4') {R2 = R2-R4;}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='5') {R2 = R2-R5;} 
                     
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='1') {R3=R3-R1;}        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='2') {R3 = R3-R2;} 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='4') {R3 = R3-R4;}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]!='5') {R3 = R3-R5;} 
                
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='1') {R4=R4-R1;}        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='2') {R4 = R4-R2;} 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='3') {R4 = R4-R3;}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='5') {R4 = R4-R5;}
             
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='1') {R5=R5-R1;}        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='2') {R5 = R5-R2;} 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='3') {R5 = R5-R3;}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='4') {R5 = R5-R4;}     
   }    

 if(option=='1' || option=='2') {
    // Print results
    if(token2Register[0]=='R') {
        cout << "SUB " << tokenRegister<< " " << token2Register << "-" << "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
             << " R4=" << R4 << "," " R5=" << R5 << endl;   
    }       
    else {
        cout << "SUB " << tokenRegister<< " " << integerValue << "-" << "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
             << " R4=" << R4 << "," " R5=" << R5 << endl;
    }
  }
}

// Mov operation, from register to address
void movRegToAddress(string movSecondOperandAddress, char option)
{ 
   stringstream ss(movSecondOperandAddress);                                                      
   ss >> integerAddress; 
  
    if(tokenRegister[0]=='R' && tokenRegister[1]=='1') {address[integerAddress] = R1;}          
      else if(tokenRegister[0]=='R' && tokenRegister[1]=='2') {address[integerAddress] = R2;}         
      else if(tokenRegister[0]=='R' && tokenRegister[1]=='3') {address[integerAddress] = R3;}                   
      else if(tokenRegister[0]=='R' && tokenRegister[1]=='4') {address[integerAddress] = R4;}                            
      else if(tokenRegister[0]=='R' && tokenRegister[1]=='5') {address[integerAddress] = R5;}  

     if(option=='1' || option=='2') {
     
      cout << "MOV " << tokenRegister<< " #" << integerAddress <<  "-" << "R1=" << R1 << "," << 
              " R2=" << R2 << "," << " R3=" << R3 <<"," 
                << " R4=" << R4 << "," " R5=" << R5 << " -Memory[" << integerAddress << "] " << endl;  
    }
}

// Mov operation, put constant value into memory address
void movConstantToAddress(int firstAddressOperand, string movSecondOperandConstant, char option)
{

    stringstream ss(movSecondOperandConstant);                                                      
    ss >> movAddressConstant;  

    address[firstAddressOperand] = movAddressConstant;
    
 if(option=='1' || option=='2') {
     cout << "MOV " <<"#" << firstAddressOperand <<  ", " << movAddressConstant << 
        " -R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<","  << " R4=" << 
        R4 << "," " R5=" << R5 << " -Memory[" << firstAddressOperand << "] " << endl;  
    }
}
// Mov operation, from address to register
void movAddressToReg(int firstAddressOperand, string movSecondOperandRegister, char option)
{
   
if(movSecondOperandRegister[0]=='R' && movSecondOperandRegister[1]=='1') { R1 = address[firstAddressOperand];}          
else 
    if(movSecondOperandRegister[0]=='R' && movSecondOperandRegister[1]=='2') {R2 = address[firstAddressOperand];}              
else
    if(movSecondOperandRegister[0]=='R' && movSecondOperandRegister[1]=='3') {R3 = address[firstAddressOperand];}                         
else 
if(movSecondOperandRegister[0]=='R' && movSecondOperandRegister[1]=='4') {R4 = address[firstAddressOperand];}                                
 else if(movSecondOperandRegister[0]=='R' && movSecondOperandRegister[1]=='5') {R5 = address[firstAddressOperand];}
    
    if(option=='1' || option=='2') {
   cout << "MOV " <<"#" << firstAddressOperand <<  ", " << movSecondOperandRegister << 
       " -R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," << " R4=" << R4 << "," " R5=" << R5 <<
       " -Memory[" << firstAddressOperand << "] " << endl;   
   }       
}

// OPeration mov without address
void movOperation(string token2Register, char option)
{
 
    // MOV R1, 10   
    if(tokenRegister[0]=='R' && tokenRegister[1]=='1'&& token2Register[0]!='R') {R1 = integerValue;}  
               
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='2'&& token2Register[0]!='R') {R2 = integerValue;}        
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='3'&& token2Register[0]!='R') {R3 = integerValue;}                  
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='4'&& token2Register[0]!='R') {R4 = integerValue;}                            
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='5'&& token2Register[0]!='R') {R5 = integerValue;}
           
    // MOV R1, R2           
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='2') {R1 = R2;} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='3') {R1 = R3;} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='4') {R1 = R4;}
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='5') {R1 = R5;} 
    
    
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='1') {R2 = R1;} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='3') {R2 = R3;} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='4') {R2 = R4;}
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='5') {R2 = R5;} 
    
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='1') {R3 = R1;} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='2') {R3 = R2;} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='4') {R3 = R4;}
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='5') {R3 = R5;} 
    
    
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='1') {R4 = R1;} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='2') {R4 = R2;} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='3') {R4 = R3;}
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='5') {R4 = R5;} 
    
     
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='1') {R5 = R1;} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='2') {R5 = R2;} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='3') {R5 = R3;}
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='4') {R5 = R4;} 
   
    if(option=='1' || option=='2') {  
     
   // Print result    
   if(token2Register[0]=='R') {
        cout << "MOV " << tokenRegister<< " " << token2Register << "-" << "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
             << " R4=" << R4 << "," " R5=" << R5 << endl;   
   }
       
    else {   
        cout << "MOV " << tokenRegister<< " " << integerValue << "-" << "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
             << " R4=" << R4 << "," " R5=" << R5 << endl;
    }
  } 
}

// PRN operation without address
void prnOperation(char option) 
{
     if(option=='1' || option=='2') {
    cout << "PRN " << tokenRegister<< " " << "-" << "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
         << " R4=" << R4 << "," " R5=" << R5 << endl;  
 }
}

// PRN operation with address
void prnAddressContent(int prnAddress, char option)
{
  if(option=='2') {
    cout << "PRN " << "#" << prnAddress << "  -Memory["<<prnAddress<<"] = "<<address[prnAddress] << endl;  
 }
}

// Operation jump 
void jmpOperation(ifstream *inputFile, string tokenConstantOrRegister, int value, char option)
{
    string line;
    int i=0;  
    
// Return input file beginning and Get lines
    if(R1 == 0 &&tokenConstantOrRegister[0]=='R'&&tokenConstantOrRegister[1]=='1') {  
        inputFile->seekg (0, inputFile->beg);
        for(i=0;i<value-1;i++)  {
            getline (*inputFile,line);
        }
    }
    else if(R2 == 0 &&tokenConstantOrRegister[0]=='R'&&tokenConstantOrRegister[1]=='2'){   
        inputFile->seekg (0, inputFile->beg);
        for(i=0;i<value-1;i++)  {
            getline (*inputFile,line);
        }
    }
    else if(R3 == 0&&tokenConstantOrRegister[0]=='R'&&tokenConstantOrRegister[1]=='3') {   
        inputFile->seekg (0, inputFile->beg);
        for(i=0;i<value-1;i++)  {
            getline (*inputFile,line);
        }
    }
    else if(R4 == 0&&tokenConstantOrRegister[0]=='R'&&tokenConstantOrRegister[1]=='4') {   
        inputFile->seekg (0, inputFile->beg);
        for(i=0;i<value-1;i++)  {
            getline (*inputFile,line);
        }
    }
    else if(R5 == 0&& tokenConstantOrRegister[0]=='R'&&tokenConstantOrRegister[1]=='5') { 
        inputFile->seekg (0, inputFile->beg);
        for(i=0;i<value-1;i++)  {
            getline (*inputFile,line);
        }
    }
    else if(tokenConstantOrRegister[0]!='R'){        
        inputFile->seekg (0, inputFile->beg);
        for(i=0;i<value-1;i++)  {
            getline (*inputFile,line);
        }   
    }
     
   
    if(option=='1' || option=='2') {
    
    // Print Results  
    if(tokenConstantOrRegister[0]=='R') {
      cout << "JMP " << tokenConstantOrRegister << " " << value << "-" << "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
       << " R4=" << R4 << "," " R5=" << R5 << endl; 
    }    
    else {
    cout << "JMP" << " " << value << "-" << "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
       << " R4=" << R4 << "," " R5=" << R5 << endl; 
    }
  }    
}

void jpnOperation(ifstream *inputFile, string tokenConstantOrRegister, int value, char option)
{
    string line;
    int i=0;  
    
// Return input file beginning and Get lines
    if((R1 == 0 || R1<0) &&tokenConstantOrRegister[0]=='R'&&tokenConstantOrRegister[1]=='1') {  
        inputFile->seekg (0, inputFile->beg);
        for(i=0;i<value-1;i++)  {
            getline (*inputFile,line);
        }
    }
    else if((R2 == 0 || R2<0)&&tokenConstantOrRegister[0]=='R'&&tokenConstantOrRegister[1]=='2'){   
        inputFile->seekg (0, inputFile->beg);
        for(i=0;i<value-1;i++)  {
            getline (*inputFile,line);
        }
    }
    else if((R3 == 0|| R3<0)&&tokenConstantOrRegister[0]=='R'&&tokenConstantOrRegister[1]=='3') {   
        inputFile->seekg (0, inputFile->beg);
        for(i=0;i<value-1;i++)  {
            getline (*inputFile,line);
        }
    }
    else if((R4 == 0 || R4 <0 )&&tokenConstantOrRegister[0]=='R'&&tokenConstantOrRegister[1]=='4') {   
        inputFile->seekg (0, inputFile->beg);
        for(i=0;i<value-1;i++)  {
            getline (*inputFile,line);
        }
    }
    else if((R5 == 0 || R5<0)&& tokenConstantOrRegister[0]=='R'&&tokenConstantOrRegister[1]=='5') { 
        inputFile->seekg (0, inputFile->beg);
        for(i=0;i<value-1;i++)  {
            getline (*inputFile,line);
        }
    }
    else if(tokenConstantOrRegister[0]!='R'){        
        inputFile->seekg (0, inputFile->beg);
        for(i=0;i<value-1;i++)  {
            getline (*inputFile,line);
        }   
    }
    
  if(option=='1' || option=='2') {

    // Print Results  
    if(tokenConstantOrRegister[0]=='R') {
      cout << "JPN " << tokenConstantOrRegister << " " << value << "-" << "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
       << " R4=" << R4 << "," " R5=" << R5 << endl; 
    }    
    else {
    cout << "JPN" << " " << value << "-" << "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
       << " R4=" << R4 << "," " R5=" << R5 << endl; 
    }  
  }    
}



