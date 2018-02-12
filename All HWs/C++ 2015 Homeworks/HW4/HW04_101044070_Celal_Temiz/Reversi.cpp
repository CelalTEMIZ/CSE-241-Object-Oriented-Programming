#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include "Reversi.h"

using namespace std;

#define GAME_BOARD_SIZE 6

Reversi::Reversi()
{
  x = 0;  
  y = '0';  
}

Reversi::Reversi(int xCoordinate)
{
    x = xCoordinate;
}

Reversi::Reversi(int xCoordinate, int yCoordinate)
{
  x = xCoordinate;
  y = yCoordinate;
}

 int Reversi::readFile(FILE* inp)
 {
     
    int boardSize;
    
    fscanf(inp, "%d", &boardSize );
      
    return boardSize;
 }


void Reversi::initialAllGameBoard(char gameBoard[][GAME_BOARD_SIZE],int boardRow,int boardColumn)
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

void Reversi::showGameBoard(char gameBoard[][GAME_BOARD_SIZE])
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
 
 
  void Reversi:: writeFile(FILE* outp, char gameBoard[][GAME_BOARD_SIZE], int board_row, int board_column)
  {
      
     
    
    char alphabeticOrder = 'a'; 
    int i;
    
     fprintf(outp,"%s", "Your Initial Board");
     fprintf(outp,"\n");
    
    fprintf(outp, "  ");
  
  
        for(int gameColumn = 0; gameColumn<GAME_BOARD_SIZE; gameColumn++)
            
            fprintf(outp,"%c ",static_cast<char>(alphabeticOrder + gameColumn), " ");
            fprintf(outp,"\n");
            
                 // Show Board
                for(i  = 0; i < GAME_BOARD_SIZE; ++i) {
                    
                    fprintf(outp, "%d ", i+1);                   
                    for(int j=0; j<board_column; ++j) {        
                                fprintf(outp, "%c ", gameBoard[i][j]);
                                }
                                fprintf(outp,"\n");                      
                }
                                                             
  }
  
  
 
 
int  Reversi::widthBoard(char gameBoard[][GAME_BOARD_SIZE], FILE* inp)
{
    int counter=0;
    for(int i=0; i<GAME_BOARD_SIZE; ++i)
        for(int j=0; j<GAME_BOARD_SIZE; ++j)
        {
            if (gameBoard[i][j] == '.' || gameBoard[i][j] == 'X'  || gameBoard[i][j] =='O')
                counter++;
        }
        
    return counter/readFile(inp) ;
    
}
  

int Reversi::heightBoard(FILE* inp)
{   
    rewind(inp);
    return readFile(inp);
}

void Reversi::userStep(char gameBoard[][GAME_BOARD_SIZE],char userOrComputer,int boardRow,int boardColumn)
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
int Reversi:: status(char gameBoard[][GAME_BOARD_SIZE], char userOrComputer, int step[][GAME_BOARD_SIZE])
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


void Reversi::computerStep(char gameBoard[][GAME_BOARD_SIZE],char userOrComputer,int step[][GAME_BOARD_SIZE])
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
                                      
                                      status(copyGameBoard,otherPlayer,emptyCells); 
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








