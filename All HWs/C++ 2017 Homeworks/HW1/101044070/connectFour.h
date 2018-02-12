#ifndef CONNECTFOUR_H__
#define CONNECTFOUR_H__

// Function Prototypes

const int maxBoardSize = 20;

bool boardSizeCheck(int boardSize);
void twoPlayers(int boardSize);
void userVersusComputer(int boardSize);
void printBoardStepRange(int boardSize);
void initialBoard(char gameBoard[][maxBoardSize], int boardSize);
void displayBoard(char gameBoard[][maxBoardSize], int boardSize);
void movement(char gameBoard[][maxBoardSize], int boardSize, int yPosition, char whichUser);
void user1Move(char gameBoard[][maxBoardSize],int xPosition);
void user2AndComputerMove(char gameBoard[][maxBoardSize],int xPosition,int userVsComputerFlag); 
// UserVsUser = 0, UserVsComputer = 1

#endif
