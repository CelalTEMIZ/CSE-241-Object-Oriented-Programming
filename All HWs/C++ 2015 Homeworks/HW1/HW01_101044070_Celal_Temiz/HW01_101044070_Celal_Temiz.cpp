/*******************************************************************/
/*	Object Oriented Programming							           */
/*	Fall 2015									                   */
/*	Homework # 1									               */
/*	                                                               */
/*  CELAL TEMİZ                                                    */
/* 	101044070											           */
/*																   */
/*  A C++ program that will play the classical game reversi        */
/*  The game of reversi is played by two players(computer and user)*/ 
/*  on a two dimentional board (2D array) with rectangular cells.  */
/*  Each cell is either computer, user, or empty.                  */
/*  where . represents the empty cells, X repesents the computer   */
/*  cells and O represents the user cells. The players take turns  */
/*  the play the game. For the above board, the user can play      */ 
/*  positions at 4c, 3d, 5f, or 6e.                                */ 
/*******************************************************************/

#include<iostream>
#include<cstdio>

using namespace std;

// Size of Board

#define GAME_BOARD_SIZE 6 

// Board initial cells
void initialAllGameBoard(char gameBoard[][GAME_BOARD_SIZE],int boardRow,int boardColumn);
// Show initial board character
void showGameBoard(char gameBoard[][GAME_BOARD_SIZE]);
// Computer step during the game
void computerStep(char gameBoard[][GAME_BOARD_SIZE],char userOrComputer,int step[][GAME_BOARD_SIZE]); 
// User step during the game 
void userStep(char gameBoard[][GAME_BOARD_SIZE],char userOrComputer,int boardRow,int boardColumn); 
// Check empty cells for user and computer steps
int  status(char gameBoard[][GAME_BOARD_SIZE],char userOrComputer,int step[][GAME_BOARD_SIZE]); 


int main()
{

  int  step[GAME_BOARD_SIZE][GAME_BOARD_SIZE],userOrComputer,stepFirstChar,aliveCell=0,playerOrder=0;  
  char gameBoard[GAME_BOARD_SIZE][GAME_BOARD_SIZE],stepSecondChar,choice; 
        
         
   while(choice != 'q'){
   
        // User = 1 
        // Initial alive cells number for all size game board       
        aliveCell = 4;
        userOrComputer = ++playerOrder%2 ;
        // Start Game
         initialAllGameBoard(gameBoard,GAME_BOARD_SIZE,GAME_BOARD_SIZE);
 
      
        // Control alive cell number in the game
          while(aliveCell<GAME_BOARD_SIZE*GAME_BOARD_SIZE ) {
                
                showGameBoard(gameBoard);
                
        // User step and get step inputs from the user
                     if(userOrComputer++ % 2) {     
                             if(status(gameBoard,'O',step)) {
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
                                           userStep(gameBoard,'O',stepFirstChar,stepSecondChar);
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
                           if(status(gameBoard,'X',step )) {                                            
                               computerStep(gameBoard,'X',step );
                               cout << endl << "     Computer .." << endl;             
                               aliveCell++;                          
                             }
                     }
        
         }        
         // Final Board 
          
         showGameBoard(gameBoard);  
                
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
         cin >> choice;                         
       }              
        return 0;    
}
// Show Game Board for all size game board
void showGameBoard(char gameBoard[][GAME_BOARD_SIZE])
{                
   char alphabeticOrder = 'a';  
    cout << endl;
    cout << "  ";
    
        for(int gameColumn = 0; gameColumn<GAME_BOARD_SIZE; gameColumn++)
               cout << static_cast<char>(alphabeticOrder + gameColumn) << "  " ;
               cout << endl;
                 // Show Board
                for(int gameRow  = 0; gameRow < GAME_BOARD_SIZE; gameRow++)
                {            
                    cout << gameRow+1;
                 // cout << endl;
                    for(int gameColumn = 0; gameColumn<GAME_BOARD_SIZE; gameColumn++)
                            cout << " " << gameBoard[gameRow][gameColumn] << " ";
                            cout << endl;   
                }                 
}
// User steps
void userStep(char gameBoard[][GAME_BOARD_SIZE],char userOrComputer,int boardRow,int boardColumn)
{
   char otherPlayer;
   int  firstPositionIndex,secondPositionIndex,rangeRowLine,rangeColumnLine,i=0,j=0;
                                                                      
   if (userOrComputer == 'X')
         otherPlayer = 'O';
   else
         otherPlayer = 'X';

   gameBoard[boardRow][boardColumn] = userOrComputer;             
   
   // Line Points:  Previous = -1 Center = 0 Next = 1 
   for(rangeRowLine = -1; rangeRowLine <= 1; rangeRowLine++)  
         for(rangeColumnLine = -1; rangeColumnLine <= 1; rangeColumnLine++)
         { 
            i = boardRow + rangeRowLine;
            j = boardColumn + rangeColumnLine; 
            
   // Control cell points         
           if( i < 0 || i >= GAME_BOARD_SIZE || 
               j < 0 || j >= GAME_BOARD_SIZE || 
               (rangeRowLine == 0 && rangeColumnLine == 0)) continue;
              
                       if(gameBoard[i][j] == otherPlayer)
                       {                               
                             firstPositionIndex = i;        
                             secondPositionIndex = j;  
   // Change user step and new step changing control      
         while(1)
         {
           firstPositionIndex  = firstPositionIndex + rangeRowLine; 
                         
           secondPositionIndex = secondPositionIndex + rangeColumnLine;           

               if(gameBoard[firstPositionIndex][secondPositionIndex] == '.') break;
             
                       if(firstPositionIndex < 0 || firstPositionIndex >= GAME_BOARD_SIZE ) break;
 
                           if(secondPositionIndex < 0 || secondPositionIndex >= GAME_BOARD_SIZE) break;
                             
                               if(gameBoard[firstPositionIndex][secondPositionIndex] == userOrComputer)
                               {
                                 while(gameBoard[firstPositionIndex-=rangeRowLine][secondPositionIndex-=rangeColumnLine]==otherPlayer)
                                   gameBoard[firstPositionIndex][secondPositionIndex] = userOrComputer;    
                                 break;                    
                               } 
         }
       }
     }
}

// Board initial cells for all game board size 
void initialAllGameBoard(char gameBoard[][GAME_BOARD_SIZE],int boardRow,int boardColumn)
{

 for(int gameRow = 0; gameRow < GAME_BOARD_SIZE; gameRow++)
               for(int gameColumn = 0; gameColumn < GAME_BOARD_SIZE; gameColumn++)
                        gameBoard[gameRow][gameColumn] = '.';
  
                // Initial alive cells for all games
                gameBoard[GAME_BOARD_SIZE/2 - 1][GAME_BOARD_SIZE/2 - 1] = 'X';                
                gameBoard[GAME_BOARD_SIZE/2 - 1][GAME_BOARD_SIZE/2] = 'O';
                gameBoard[GAME_BOARD_SIZE/2][GAME_BOARD_SIZE/2 - 1] = 'O';                
                gameBoard[GAME_BOARD_SIZE/2][GAME_BOARD_SIZE/2] = 'X';
}
// Computer Step 
void computerStep(char gameBoard[][GAME_BOARD_SIZE],char userOrComputer,int step[][GAME_BOARD_SIZE])
{

   char copyGameBoard[GAME_BOARD_SIZE][GAME_BOARD_SIZE],otherPlayer;             
   int  emptyCells[GAME_BOARD_SIZE][GAME_BOARD_SIZE],
        nextRowStep,nextColumnStep,aliveCellNumber,allCellNumber=400; 
                                         
// Initialize other player               
   if (userOrComputer == 'X')
        otherPlayer = 'O';
    else
        otherPlayer = 'X';
          
       for(int boardRow = 0; boardRow < GAME_BOARD_SIZE; boardRow++)
            for( int boardColumn = 0; boardColumn < GAME_BOARD_SIZE; boardColumn++) {
            
// Update Board          
                if(step[boardRow][boardColumn] == 0) continue;
                
                    for(int i = 0; i < GAME_BOARD_SIZE; i++)                   
                            for(int j = 0; j < GAME_BOARD_SIZE; j++)
                            
// User step and then control empty cells                           

                                      copyGameBoard[i][j] = gameBoard[i][j];
                                     
                                      userStep(copyGameBoard,userOrComputer,boardRow,boardColumn); 
                                      
                                      status(copyGameBoard,otherPlayer,emptyCells );
// Update new board cells                                     
                                      if(aliveCellNumber < allCellNumber){                                  
                                         allCellNumber=aliveCellNumber;         
                                                            nextRowStep=boardRow;  
                                                            nextColumnStep=boardColumn;   
           }
     }
// Call user to continue game
   userStep(gameBoard,userOrComputer,nextRowStep,nextColumnStep); 
}

// Check empty cells for user and computer steps
int status(char gameBoard[][GAME_BOARD_SIZE], char userOrComputer, int step[][GAME_BOARD_SIZE])
{
   char otherPlayer;
   int rangeRowLine,rangeColumnLine,boardRow,boardColumn,firstPositionIndex,secondPositionIndex,stepNumber = 0,i=0, j=0; 

    if (userOrComputer == 'O')
        otherPlayer = 'X';
    else
        otherPlayer = 'O';

    // Initialize first empty board 
           for(boardRow = 0; boardRow < GAME_BOARD_SIZE; boardRow++)           
                 for(boardColumn = 0; boardColumn < GAME_BOARD_SIZE; boardColumn++)             
                        step[boardRow][boardColumn] = 0;
   // Control all board range - line range           
                       for(boardRow = 0; boardRow < GAME_BOARD_SIZE; boardRow++)
                             for(boardColumn = 0; boardColumn < GAME_BOARD_SIZE; boardColumn++) {  
                                    if(gameBoard[boardRow][boardColumn] != '.')continue;
                                    
                                        for(rangeRowLine = -1; rangeRowLine <= 1; rangeRowLine++)
                                            for(rangeColumnLine = -1; rangeColumnLine <= 1; rangeColumnLine++) { 
                                                i = boardRow + rangeRowLine;
                                                j = boardColumn + rangeColumnLine;
   // Control alive cell neighbor                                               
                        if(i < 0 || i >= GAME_BOARD_SIZE || j < 0 ||
                         j >= GAME_BOARD_SIZE  || (rangeRowLine==0 && rangeColumnLine==0))continue;
                        
             if(gameBoard[boardRow + rangeRowLine][boardColumn + rangeColumnLine] == otherPlayer) {
                         firstPositionIndex = boardRow + rangeColumnLine;                
                         secondPositionIndex = boardColumn + rangeColumnLine;                         
             while(1)
             {
               firstPositionIndex  = firstPositionIndex + rangeRowLine;                 
               secondPositionIndex = secondPositionIndex + rangeColumnLine;                  
  // Control board size            
             if(gameBoard[firstPositionIndex][secondPositionIndex] == ' ') break;
                if(firstPositionIndex < 0 || firstPositionIndex >= GAME_BOARD_SIZE ) break;
                    if( secondPositionIndex < 0 || secondPositionIndex >= GAME_BOARD_SIZE) break;
                        
                            if(gameBoard[firstPositionIndex][secondPositionIndex] == userOrComputer) {
                                    step[boardRow][boardColumn] = 1;   
                                    stepNumber++;         
                                    break;                 
                            }
             } 
           } 
         }  
     }       
   return stepNumber; 
}




