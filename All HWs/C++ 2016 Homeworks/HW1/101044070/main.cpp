/*******************************************************************/
/*	Object Oriented Programming							           */
/*	Fall 2016									                   */
/*	Homework # 1									               */
/*	                                                               */
/*  CELAL TEMİZ                                                    */
/* 	101044070											           */
/*																   */ 
/*******************************************************************/


// Run program
//
//  make
// ./yourProg filename option



#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

// Global Variables to string parse
string tokenRegister, tokenInstruction , token2Register;
int integerValue;

// Registers
int R1=0, R2=0, R3=0, R4=0, R5=0;

// Operations
void addOperation(void);
void subOperation(void);
void movOperation(string tokenInstruction);
void prnOperation(void);
void jmpOperation(ifstream *inputFile, string tokenConstantOrRegister,int value);

int main(int argc, char **argv)
{

  string line;

  size_t pos=0;
  string tokenConstantOrRegister, MOV="MOV", PRN="PRN", SUB="SUB",ADD ="ADD",JMP="JMP", HLT="HLT";

  
  string delimeter = " ";
 
  // File Operation
  
  ifstream inputFile (argv[1]);
  
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

  if(argv[2][0]=='1') {
  
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
                                          
                                       
                                           if(tokenInstruction=="") {
                                            break;
                                           }
                                                                                   
                                           else {
                                               
                                               line.erase(0,pos+delimeter.length());

                                               if (tokenInstruction==MOV) { 
                                                    
                                             // Finding register to mov
                                              
                                                tokenRegister = line.substr(0,pos);

                                                line.erase(0,pos+delimeter.length());

                                               }
                                               // Finding register to prn
                                               else if (tokenInstruction==PRN) { 
                                                
                                                tokenRegister = line.substr(0,pos);
                                         
                                                line.erase(0,pos+delimeter.length());                                                
                                               
                                               }
                                              // Finding register to sub
                                               else if (tokenInstruction==SUB) { 
                                                
                                                tokenRegister = line.substr(0,pos);
                                        
                                                line.erase(0,pos+delimeter.length());
                                               
                                               }
                                               
                                               // Finding register to add
                                               
                                                else if (tokenInstruction==ADD) { 
                                                
                                                tokenRegister = line.substr(0,pos);
                                          
                                                line.erase(0,pos+delimeter.length());
                                               }

                                               // Finding register to jmp
                                               else if (tokenInstruction==JMP) {                            
                                                        tokenConstantOrRegister = line.substr(0,pos);       
                                                    if(tokenConstantOrRegister[0] == 'R') {
                                                        line.erase(0,pos+delimeter.length());
                                                    
                                                    }

                                               }
                                          
                                           }
                                    // Finding second register like MOV R1, R2
                                 
                                    
                                   if(line[0]==' ') {
                                     if(tokenInstruction==HLT) {cout << "HLT "<< "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
             << " R4=" << R4 << "," " R5=" << R5 << endl;}
                                   }
                                   else {
                                       
                                       if(line==HLT) {cout << "HLT" << endl;}
                                       else if(line[0]=='R') {
                                       token2Register = line.substr(0,pos);
                                 
                                       }
                                       else if(line[0]!='R') {
                                       }  
                                   }                                   
                                   // Convert string to integer
                                  
                                   stringstream ss(line);                                                      
                                   ss >> integerValue;
                                                  
                                  // Operation functions 
                                                if (tokenInstruction==ADD ) {
                                                    addOperation();
                                                  } 
                                       
                                                if (tokenInstruction==SUB ) {
                                                    subOperation();
                                                  }     
                                                if (tokenInstruction==MOV ) {
                                                    movOperation(token2Register);                         
                                                  }        

                                                if (tokenInstruction==PRN ) {
                                                    prnOperation();       
                                                  }
                                                  
                                                if (tokenInstruction==JMP) {
                                                    jmpOperation(&inputFile,tokenConstantOrRegister,integerValue);
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
}
    return 0;
}


// Operation ADD
void addOperation(void)
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

// Operation SUB
void subOperation(void)
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

// OPeration mov
void movOperation(string token2Register)
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

// Operation PRN=PRINT
void prnOperation(void) 
{
    cout << "PRN " << tokenRegister<< " " << "-" << "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
         << " R4=" << R4 << "," " R5=" << R5 << endl;  
}

// Operation jump
void jmpOperation(ifstream *inputFile, string tokenConstantOrRegister, int value)
{
    string line;
    int i=0;  
    
// Return input file beginning and Get lines
    if(R1 == 0&&tokenConstantOrRegister[0]=='R'&&tokenConstantOrRegister[1]=='1') {  
        inputFile->seekg (0, inputFile->beg);
        for(i=0;i<value-1;i++)  {
            getline (*inputFile,line);
        }
    }
    else if(R2 == 0&&tokenConstantOrRegister[0]=='R'&&tokenConstantOrRegister[1]=='2'){   
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
