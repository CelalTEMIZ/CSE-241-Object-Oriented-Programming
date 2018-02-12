/*************************************/
/*	Object Oriented Programming  */
/*	Fall 2015                    */
/*	Homework 04                  */
/*   				     */
/*      CELAL TEMİZ                  */
/* 	101044070		     */
/*                                   */
/*************************************/


#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include"Cell.h"
#include"Reversi.h"


using namespace std;

#define GAME_BOARD_SIZE 6

int main(int argc, char** argv) {

     
   char initialize_fileName[20];
   char final_fileName[20];
   int  height, board_column, board_row;
   
   char gameBoard[GAME_BOARD_SIZE][GAME_BOARD_SIZE]; 
   
   
   int  step[GAME_BOARD_SIZE][GAME_BOARD_SIZE];
   int  userOrComputer,stepFirstChar,aliveCell=0,playerOrder=0;  
   char stepSecondChar,choice; 
   
   Reversi readObject,object1;
    
   FILE *inp;
   FILE *outp;


    // Get the name of initialize file and final file from the user 

	cout << "Enter your initialize board file name" << endl;
	cin >> initialize_fileName;
	cout << "Enter your final board file name" << endl;
	cin >> final_fileName;

    // Open file 

	inp = fopen(initialize_fileName, "r");	
     	outp = fopen(final_fileName, "w");
        
        
        while(choice != 'q'){
   
        // User = 1 
        // Initial alive cells number for all size game board       
        aliveCell = 4;
        userOrComputer = ++playerOrder%2 ;
        // Start Game
        readObject.initialAllGameBoard(gameBoard,GAME_BOARD_SIZE,GAME_BOARD_SIZE);
      
        // Control alive cell number in the game
          while(aliveCell<GAME_BOARD_SIZE*GAME_BOARD_SIZE ) {
                
                readObject.showGameBoard(gameBoard);  
                
        // User step and get step inputs from the user
                     if(userOrComputer++ % 2) {     
                            if(readObject.status(gameBoard,'O',step)) {
                                   while(1) { 
                                     cout << endl;                                                                 
                                     cout << "Enter your step > ";                                 
                                     cin >> stepFirstChar >> stepSecondChar;                                 
                                     stepFirstChar--;                                               
                                     stepSecondChar = tolower(stepSecondChar) - 'a';                                            
        // User input control
                                     if( stepFirstChar >= 0 && stepFirstChar < GAME_BOARD_SIZE && 
                                         stepSecondChar >= 0 && stepSecondChar < GAME_BOARD_SIZE && 
                                         step[stepFirstChar][stepSecondChar]) {
                                           readObject.userStep(gameBoard,'O',stepFirstChar,stepSecondChar);
        // Number of alive cell                                   
                                           aliveCell++;              
                                           break;
                                     } else
                                       cout << "False step! Enter your step again.\n";
                                     }
                               } 
                    }      
                      else {
                           
        // Computer Step
        // Computer = 0
                           if(readObject.status(gameBoard,'X',step )) {                                            
                               readObject.computerStep(gameBoard,'X',step );
                               cout << endl << "     Computer .." << endl;             
                               aliveCell++;                          
                             }
                     }
        
         }        
         // Final Board 
          
          readObject.showGameBoard(gameBoard);  
                
         // Show Game Result 
         
         int  scoreuser = 0;
         int  scoreComputer = 0;                    
          
         for(int gameRow = 0; gameRow < GAME_BOARD_SIZE; gameRow++)
               for(int gameColumn = 0; gameColumn < GAME_BOARD_SIZE; gameColumn++)
               {
                 scoreuser += gameBoard[gameRow][gameColumn] == 'O';
                 scoreComputer += gameBoard[gameRow][gameColumn] == 'X';   
               }
                        cout << endl << "Score" << endl;
                        if (scoreuser > scoreComputer)
                             cout << "User Won !" << endl;
                        else
                             cout << "Computer Won !" << endl;            
         cout << "User: " <<  scoreuser << endl;
         cout << "Computer: " << scoreComputer << endl;
         cout << endl << "Enter the 'q' for quit :";
         cin  >> choice;                         
       }              

        // Test function
        readObject.initialAllGameBoard(gameBoard,GAME_BOARD_SIZE,GAME_BOARD_SIZE);
        readObject.showGameBoard(gameBoard);
        
       
        // Test Write function for initial board
        readObject.writeFile(outp,gameBoard,GAME_BOARD_SIZE ,GAME_BOARD_SIZE);
        
        // Test current width and height of game board
        cout << object1.widthBoard(gameBoard,inp); 
        cout << object1.heightBoard(inp);
       
        
        fclose(inp);
        fclose(outp);
        
    return 0;
}

