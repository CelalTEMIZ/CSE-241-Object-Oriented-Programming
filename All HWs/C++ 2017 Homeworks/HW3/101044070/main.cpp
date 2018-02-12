
/*
 
 CELAL TEMIZ 101044070
 
 CSE 241 - HW03

 Connect Four Game C++ Implementation


 */


#include <cstdlib>

#include "connectFour.h"

using namespace std;

int main(int argc, char** argv) 
{
    char gameMode='\0';
    int  objectNumber=0;
    char movement='\0';
    
    ConnectFour singleModeGame1;
    
    ConnectFour MultipleModeGame1;
    ConnectFour MultipleModeGame2;
    ConnectFour MultipleModeGame3;
    ConnectFour MultipleModeGame4;
    ConnectFour MultipleModeGame5;
    
   
    while(gameMode !='S' || gameMode!='M')
    {
      cout << endl << "Single Mode Game : S , Multiplayer Game Mode : M"<<endl<<"Select Game Mode : ";
      cin >> gameMode;

      if(gameMode=='S' || gameMode=='M')
          break;
    }
    
    
    if(gameMode=='S')
    {
        singleModeGame1.playGame();
    }
    
    else if(gameMode=='M') 
    {
        cout << endl << "Object 1: " << endl;
        MultipleModeGame1.getData();       
             
        cout << endl << "Object 2: " << endl;
        MultipleModeGame2.getData();          
        
         
        cout << endl << "Object 3: " << endl;
        MultipleModeGame3.getData();
             
        cout << endl << "Object 4: " << endl;
        MultipleModeGame4.getData();
             
        cout << endl << "Object 5: " << endl;
        MultipleModeGame5.getData(); 
       
          
        while(1)
        {
            cout << "\nSelect Object : ";
            cin  >> objectNumber;
                       
            while (!cin >> objectNumber) {
                    cout << "\nObject Selection Between 1 And 6 : ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cin  >> objectNumber;
            } 
                         
                
            switch(objectNumber)
            {
                case 1:
                    if(MultipleModeGame1.getGameSelection()=='C')
                    {   
                        if(ConnectFour::getWinner()== true) break;
                        if(ConnectFour::getWinner2()==true) break;
                        
                        MultipleModeGame1.display();
                        cout << "Enter Movement P1 : ";
                        cin >> movement;

                        MultipleModeGame1.play(movement); 
                        MultipleModeGame1.play(); 
                        cout<< "Living Cell : "<< ConnectFour::getNumberOfLivingCell()<<endl;
                        break; 
                    }
                    else if(MultipleModeGame1.getGameSelection()=='P') 
                    {   

                        MultipleModeGame1.display();
                        cout << "Enter Movement P1 : ";
                        cin >> movement;
                          
                       
                        MultipleModeGame1.play(movement);                  
                        
                        cin.ignore(1000, '\n');
                        cin.clear();                     

                        if(ConnectFour::getWinner()== true) break;
                        cout << "Enter Movement P2 : ";
                        cin >> movement;
                        
                        MultipleModeGame1.play(movement); 
                        cout<< "Living Cell : "<< ConnectFour::getNumberOfLivingCell()<<endl;
                        break;   
                    }
               
                case 2:
                    
                    if(MultipleModeGame2.getGameSelection()=='C')
                    { 
                        MultipleModeGame2.display();
                        cout << "Enter Movement P1 : ";
                        cin >> movement;

                        MultipleModeGame2.play(movement); 
                        MultipleModeGame2.play(); 
                        cout<< "Living Cell : "<< ConnectFour::getNumberOfLivingCell()<<endl;
                        break; 
                    }
                    else if(MultipleModeGame2.getGameSelection()=='P') 
                    {   
                        MultipleModeGame2.display();
                        cout << "Enter Movement P1 : ";
                        cin >> movement;

                        MultipleModeGame2.play(movement);
                        cin.ignore(1000, '\n');
                        cin.clear();

                        if(ConnectFour::getWinner()==true) break;
                        cout << "Enter Movement P2 : ";
                        cin >> movement;
                        
                        MultipleModeGame2.play(movement); 
                        cout<< "Living Cell : "<< ConnectFour::getNumberOfLivingCell()<<endl;
                        break;   
                    }
                    
                case 3:
                    if(MultipleModeGame3.getGameSelection()=='C')
                    {
                        MultipleModeGame3.display();
                        cout << "Enter Movement P1 : ";
                        cin >> movement;

                        MultipleModeGame3.play(movement); 
                        MultipleModeGame3.play(); 
                        cout<< "Living Cell : "<< ConnectFour::getNumberOfLivingCell()<<endl;
                        break; 
                    }
                    else if(MultipleModeGame3.getGameSelection()=='P') 
                    {   
                        MultipleModeGame3.display();
                        cout << "Enter Movement P1 : ";
                        cin >> movement;

                        MultipleModeGame3.play(movement);
                        cin.ignore(1000, '\n');
                        cin.clear();

                        if(ConnectFour::getWinner()==true) break;
                        cout << "Enter Movement P2 : ";
                        cin >> movement;
                        
                        MultipleModeGame3.play(movement); 
                        cout<< "Living Cell : "<< ConnectFour::getNumberOfLivingCell()<<endl;
                        break;   
                    }
                   
                case 4:
                    if(MultipleModeGame4.getGameSelection()=='C')
                    {               
                        MultipleModeGame4.display();
                        cout << "Enter Movement P1 : ";
                        cin >> movement;

                        MultipleModeGame4.play(movement); 
                        MultipleModeGame4.play(); 
                        cout<< "Living Cell : "<< ConnectFour::getNumberOfLivingCell()<<endl;
                        break; 
                    }
                    else if(MultipleModeGame4.getGameSelection()=='P') 
                    {   
                        MultipleModeGame4.display();
                        cout << "Enter Movement P1 : ";
                        cin >> movement;

                        MultipleModeGame4.play(movement);
                        cin.ignore(1000, '\n');
                        cin.clear();

                        if(ConnectFour::getWinner()==true) break;
                        cout << "Enter Movement P2 : ";
                        cin >> movement;
                        
                        MultipleModeGame4.play(movement); 
                        cout<< "Living Cell : "<< ConnectFour::getNumberOfLivingCell()<<endl;
                        break;   
                    }
                case 5:
                     if(MultipleModeGame5.getGameSelection()=='C')
                    {
                        MultipleModeGame5.display();
                        cout << "Enter Movement P1 : ";
                        cin >> movement;

                        MultipleModeGame5.play(movement); 
                        MultipleModeGame5.play(); 
                        cout<< "Living Cell : "<< ConnectFour::getNumberOfLivingCell()<<endl;
                        break; 
                    }
                    else if(MultipleModeGame5.getGameSelection()=='P') 
                    {   
                        MultipleModeGame5.display();
                        cout << "Enter Movement P1 : ";
                        cin >> movement;

                        MultipleModeGame5.play(movement);
                        cin.ignore(1000, '\n');
                        cin.clear();

                        if(ConnectFour::getWinner()==true) break;
                        cout << "Enter Movement P2 : ";
                        cin >> movement;
                        
                        MultipleModeGame5.play(movement); 
                        cout<< "Living Cell : "<< ConnectFour::getNumberOfLivingCell()<<endl;
                        break;   
                    }
              
                default:
                    cerr << endl << "Invalid Object Number !" << endl;
                    
            } // End Switch Case 
            
        }// End While
    }
    
    else {
        cerr << endl << "Invalid Game Mode ! " << endl;
    }

    
    return 0;
}

