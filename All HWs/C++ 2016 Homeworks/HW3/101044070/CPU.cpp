#include<iostream>
#include<string>

#include "CPU.h"


using namespace std;



CPU::CPU()
{
    registers[1]=0; registers[2]=0; registers[3]=0; registers[4]=0; registers[5]=0;
    PC=1;  
}

CPU::CPU(int oneValue)
{
    registers[1] = oneValue;
}

CPU::CPU(int oneValue, int secondValue)
{
  registers[1]=oneValue;   registers[2]=secondValue;  
}

CPU::CPU(int oneValue, int secondValue, int thirdValue)
{
  registers[1]=oneValue;   registers[2]=secondValue;  registers[3]=thirdValue;   
}

CPU::CPU(int oneValue, int secondValue, int thirdValue, int fourthValue)
{
  registers[1]=oneValue;   registers[2]=secondValue;  registers[3]=thirdValue;  registers[4]=fourthValue;
}

CPU::CPU(int oneValue, int secondValue, int thirdValue, int fourthValue, int fifthValue)
{
   registers[1]=oneValue;   registers[2]=secondValue;  registers[3]=thirdValue;  registers[4]=fourthValue; registers[5]=fifthValue;
}

void CPU::print()
{

    cout << "R1=" << getRegister(1) << "," << " R2="  << getRegister(2) << "," 
         << " R3=" << getRegister(3)  <<","  << " R4=" << getRegister(4) << "," 
            " R5=" << getRegister(5)  <<"," 
            " PC=" << getPC() << endl;
}

bool CPU::halted()
{
	if(flag==1)
    return true;
    else 
    return false;
}

void CPU::execute(string instructionLine)
{

    
    string tokenInstruction, tokenConstantOrRegister, token2Register,tokenRegister;
    string MOV="MOV", PRN="PRN", SUB="SUB",ADD ="ADD",JMP="JMP", HLT="HLT";
    int integerValue;
    
    
    size_t pos=0;
    string delimeter = " ";

    if(instructionLine[0]=='H'&&instructionLine[1]=='L'&&instructionLine[2]=='T') {setPC(getPC()+1); flag=1;}

       else if(instructionLine == "") {}
                                  
                                  else {                                       
                                                                                 // Pars operation
                                   while((pos=instructionLine.find(delimeter)) !=std::string::npos) {
                                    
                                           // Finding instruction                                
                                           tokenInstruction = instructionLine.substr(0,pos);
                                                                                    
                                           
                                           if(tokenInstruction=="") {
                                            break;
                                           }
                                                                                   
                                           else {
                                               
                                               instructionLine.erase(0,pos+delimeter.length());
                                               if (tokenInstruction==MOV) {
                                                
                                                    
                                             // Finding register to mov
                                                tokenRegister = instructionLine.substr(0,pos);
                                                instructionLine.erase(0,pos+delimeter.length());
                                               }
                                               // Finding register to prn
                                               else if (tokenInstruction==PRN) { 
                                            tokenRegister = instructionLine.substr(0,pos);                                        
                                            instructionLine.erase(0,pos+delimeter.length());                                                
                                               }
                                              // Finding register to sub
                                               else if (tokenInstruction==SUB) { 
                                                tokenRegister = instructionLine.substr(0,pos);
                                                instructionLine.erase(0,pos+delimeter.length());
                                               }
                                               
                                               // Finding register to add
                                               
                                                else if (tokenInstruction==ADD) { 
                                                tokenRegister = instructionLine.substr(0,pos);
                                                instructionLine.erase(0,pos+delimeter.length());                                          
                                               }

                                               // Finding register to jmp
                                               
                                               else if (tokenInstruction==JMP) {                            
                                                        tokenConstantOrRegister = instructionLine.substr(0,pos);       
                                                    if(tokenConstantOrRegister[0] == 'R') {
                                                        instructionLine.erase(0,pos+delimeter.length());   
                                                   }
                                               }
                                           }
                                    // Finding second register like MOV R1, R2
                                   if(instructionLine[0]==' ') {  
                                     if(tokenInstruction==HLT) {
                                     /* cout << "HLT "<< "R1=" << R1 << "," << " R2=" << R2 << "," << " R3=" << R3 <<"," 
             << " R4=" << R4 << "," " R5=" << R5 << endl;} */
                                   }
                                   }
                                   
                                   
                                   else {
                                          
                                       if(instructionLine==HLT) {cout << "***HLT" << endl;}
                                       else if(instructionLine[0]=='R') {
                                       token2Register = instructionLine.substr(0,pos);
                                       }
                                       else if(instructionLine[0]!='R') {
                                       }  
                                   }                                   
                                   // Convert string to integer

                                   stringstream ss(instructionLine);                                                      
                                   ss >> integerValue;
                                             
                                  // Operation functions 
                                                if (tokenInstruction==ADD ) {
                                                    addOperation(tokenRegister, integerValue,  token2Register);
                                                    setPC(getPC()+1);
                                                  } 
                                       
                                                if (tokenInstruction==SUB ) {
                                                    subOperation(tokenRegister, integerValue,  token2Register);
                                                    setPC(getPC()+1);
                                                  }     
                                                if (tokenInstruction==MOV ) {
                                                    movOperation(tokenRegister, integerValue,  token2Register);
                                                    setPC(getPC()+1);                       
                                                  }
                                                  
                                                  if (tokenInstruction==PRN ) {
                                                    prnOperation(tokenRegister); 
                                                    setPC(getPC()+1);      
                                                  }        

                                                if (tokenInstruction==JMP) {
                                                    jmpOperation(tokenConstantOrRegister,integerValue);
                                                } 
                                               
                                      token2Register.clear();
                                   }                                     
                                 }       



}


void CPU::prnOperation(string tokenRegister)
{
   

    if(tokenRegister[1]=='1') {cout << "PRN "<< tokenRegister;}  
    else if(tokenRegister[1]=='2') {cout <<"PRN "<<  tokenRegister <<" " ;}
    else if(tokenRegister[1]=='3') {cout <<"PRN "<<  tokenRegister <<" " ;}
    else if(tokenRegister[1]=='4') {cout <<"PRN "<<  tokenRegister <<" " ;}
    else if(tokenRegister[1]=='5') {cout <<"PRN "<<  tokenRegister <<" " ;}
}


void CPU::addOperation(string tokenRegister, int integerValue, string token2Register)
{


    // ADD R1, 5         
    if(integerValue!=0) {
        if(tokenRegister[0]=='R' && tokenRegister[1]=='1') {setRegisters((integerValue+getRegister(1)),1); }           
        else if(tokenRegister[0]=='R' && tokenRegister[1]=='2'){ setRegisters((integerValue+getRegister(2)),2);}         
        else if(tokenRegister[0]=='R' && tokenRegister[1]=='3'){ setRegisters((integerValue+getRegister(3)),3);}               
       else if(tokenRegister[0]=='R' && tokenRegister[1]=='4') { setRegisters((integerValue+getRegister(4)),4);}                             
        else if(tokenRegister[0]=='R' && tokenRegister[1]=='5'){ setRegisters((integerValue+getRegister(5)),5);} 
    } else {
      
     // ADD R1, R2
     if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='2')
        { setRegisters(getRegister(1)+getRegister(2), 1); }     
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='3') 
         { setRegisters(getRegister(1)+getRegister(3), 1);}      
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='4') 
         {setRegisters(getRegister(1)+getRegister(4), 1);}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='5') 
         {setRegisters(getRegister(1)+getRegister(5), 1);}
                
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='1')
         {setRegisters(getRegister(2)+getRegister(1), 2);}        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='3') 
         {setRegisters(getRegister(2)+getRegister(3), 2);} 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='4') 
         {setRegisters(getRegister(2)+getRegister(4), 2);}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='5') 
         {setRegisters(getRegister(2)+getRegister(5), 2);} 
       
       
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='1')
          {setRegisters(getRegister(3)+getRegister(1), 3);}        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='2')
          {setRegisters(getRegister(3)+getRegister(2), 3);} 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='4') 
         {setRegisters(getRegister(3)+getRegister(4), 3);}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]!='5') 
         {setRegisters(getRegister(3)+getRegister(5), 3);} 
           
       
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='1') 
         {setRegisters(getRegister(4)+getRegister(1), 4);}        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='2') 
         {setRegisters(getRegister(4)+getRegister(2), 4);} 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='3') 
         {setRegisters(getRegister(4)+getRegister(3), 4);}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='5')
          {setRegisters(getRegister(4)+getRegister(5), 4);}
         
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='1') 
         {setRegisters(getRegister(5)+getRegister(1), 5); }        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='2') 
         {setRegisters(getRegister(5)+getRegister(2), 5); } 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='3') 
         {setRegisters(getRegister(5)+getRegister(3), 5);}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='4')
         {setRegisters(getRegister(5)+getRegister(4), 5); }     

    }
    
    
    if(token2Register[0]=='R') {
        cout << "ADD " << tokenRegister<< " " << token2Register;   
    }
       
    else {   
        cout << "ADD " << tokenRegister<< " " << integerValue; 
    }
    
   
}
   
void CPU::subOperation(string tokenRegister, int integerValue, string  token2Register)
{

    // SUB R1, 10
     if(integerValue!=0){                                  
        if(tokenRegister[0]=='R' && tokenRegister[1]=='1') { setRegisters(getRegister(1)-integerValue, 1); }      
        else if(tokenRegister[0]=='R' && tokenRegister[1]=='2') {setRegisters(getRegister(2)-integerValue, 2);}     
        else if(tokenRegister[0]=='R' && tokenRegister[1]=='3') {setRegisters(getRegister(3)-integerValue, 3);}    
        else if(tokenRegister[0]=='R' && tokenRegister[1]=='4') {setRegisters(getRegister(4)-integerValue, 4); }                     
        else if(tokenRegister[0]=='R' && tokenRegister[1]=='5') {setRegisters(getRegister(5)-integerValue, 5);}        
     }

    else {  // SUB R1, R2
       if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='2') 
       { setRegisters(getRegister(1)-getRegister(2), 1); }           
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='3') 
         { setRegisters(getRegister(1)-getRegister(3), 1);} 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='4') 
         { setRegisters(getRegister(1)-getRegister(4), 1);}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='5') 
         { setRegisters(getRegister(1)-getRegister(5), 1);} 

         else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='1') 
         { setRegisters(getRegister(2)-getRegister(1), 2);}        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='3') 
         {setRegisters(getRegister(2)-getRegister(3), 2);} 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='4') 
         {setRegisters(getRegister(2)-getRegister(4), 2);}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='5') 
         {setRegisters(getRegister(2)-getRegister(5), 2);} 
                     
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='1') 
         { setRegisters(getRegister(3)-getRegister(1), 3);}        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='2') 
         { setRegisters(getRegister(3)-getRegister(2), 3);} 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='4')
         { setRegisters(getRegister(3)-getRegister(4), 3);}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]!='5') 
         { setRegisters(getRegister(3)-getRegister(5), 3);} 
      
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='1') 
         {setRegisters(getRegister(4)-getRegister(1), 4);}        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='2') 
         {setRegisters(getRegister(4)-getRegister(2), 4);} 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='3') 
         {setRegisters(getRegister(4)-getRegister(3), 4);}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='5') 
         {setRegisters(getRegister(4)-getRegister(5), 4);}
             
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='1') 
         { setRegisters(getRegister(5)-getRegister(1), 5);}        
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='2') 
         {setRegisters(getRegister(5)-getRegister(2), 5);} 
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='3') 
         {setRegisters(getRegister(5)-getRegister(3), 5);}
         else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='4') 
         {setRegisters(getRegister(5)-getRegister(4), 5);}     
   } 
   
   
   
   
    if(token2Register[0]=='R') {
        cout << "SUB " << tokenRegister << " " << token2Register << "";   
    }       
    else {
        cout << "SUB " << tokenRegister<< " " << integerValue << "-";
    }
     

}

void CPU::movOperation(string tokenRegister, int integerValue, string  token2Register)
{

 // MOV R1, 10   
    if(tokenRegister[0]=='R' && tokenRegister[1]=='1'&& token2Register[0]!='R') {setRegisters(integerValue,1);}  
               
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='2'&& token2Register[0]!='R') {setRegisters(integerValue,2);}        
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='3'&& token2Register[0]!='R') {setRegisters(integerValue,3);}                  
 else if(tokenRegister[0]=='R' && tokenRegister[1]=='4'&& token2Register[0]!='R') {setRegisters(integerValue,4);}                            
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='5'&& token2Register[0]!='R') {setRegisters(integerValue,5);}
           
    // MOV R1, R2           
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='2') {setRegisters(getRegister(2),1);} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='3') {setRegisters(getRegister(3),1);} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='4') {setRegisters(getRegister(4),1);}
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='1' && token2Register[1]=='5') {setRegisters(getRegister(5),1);} 
    
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='1') {setRegisters(getRegister(1),2);} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='3') {setRegisters(getRegister(3),2);} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='4') {setRegisters(getRegister(4),2);}
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='2' && token2Register[1]=='5') {setRegisters(getRegister(5),2);} 
    
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='1') {setRegisters(getRegister(1),3);} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='2') {setRegisters(getRegister(2),3);} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='4') {setRegisters(getRegister(4),3);}
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='3' && token2Register[1]=='5') {setRegisters(getRegister(5),3);}    
    
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='1') {setRegisters(getRegister(1),4);} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='2') {setRegisters(getRegister(2),4);} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='3') {setRegisters(getRegister(3),4);}
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='4' && token2Register[1]=='5') {setRegisters(getRegister(5),4);} 
    
     
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='1') {setRegisters(getRegister(1),5);} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='2') {setRegisters(getRegister(2),5);} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='3') {setRegisters(getRegister(3),5);} 
    else if(tokenRegister[0]=='R' && tokenRegister[1]=='5' && token2Register[1]=='4') {setRegisters(getRegister(4),5);} 
    
    if(token2Register[0]=='R') {
        cout << "MOV " << tokenRegister<< " " << token2Register;    
    }
       
    else {   
        cout << "MOV " << tokenRegister<< " " << integerValue << "-"; 
    }
     
    
}

void CPU::jmpOperation(string tokenConstantOrRegister, int integerValue)
{
	int temp=0;
	//cout<<tokenConstantOrRegister<<endl<<integerValue<<endl;
	

	if(tokenConstantOrRegister[0]=='R') {
			if(tokenConstantOrRegister[1]=='1'){
				if(getRegister(1)==0){
				setPC(integerValue-1);
				temp=1;
				}
			}
			if(tokenConstantOrRegister[1]=='2'){
				if(getRegister(2)==0){
				setPC(integerValue-1);
				temp=2;
				}
			}
			if(tokenConstantOrRegister[1]=='3'){
				if(getRegister(3)==0){
				setPC(integerValue-1);
				temp=3;
				}
			}
			if(tokenConstantOrRegister[1]=='4'){
				if(getRegister(4)==0){
				setPC(integerValue-1);
				temp=4;
				}
			}
			if(tokenConstantOrRegister[1]=='5'){
				if(getRegister(5)==0){
				setPC(integerValue-1);
				temp=5;
				}	
			}
			if(temp==0)
			setPC(getPC()+1);	
	}
	else {
		setPC(integerValue-1);
	}
	
	
	
	  if(tokenConstantOrRegister[0]=='R') {
      cout << "JMP " << tokenConstantOrRegister << " " << integerValue<<"-"; 
     }    
    else {
    cout << "JMP" << " " << integerValue <<"   "; 
    }
}



