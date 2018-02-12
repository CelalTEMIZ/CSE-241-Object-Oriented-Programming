#ifndef CONNECTFOUR_H__
#define CONNECTFOUR_H__

using namespace std;

const int maxBoardSize = 20;
const int maxCharNumber = 400;

void startGame(string firstUserCommand);
bool boardSizeCheck(const int& boardSize);
void twoPlayers(string inputFile,const int& boardSize);
void userVersusComputer(string inputFile,const int& boardSize);
void printBoardStepRange(const int& boardSize);
void initialBoard(char gameBoard[][maxBoardSize], const int& boardSize, char emptyCellChar = '.');
void displayBoard(char gameBoard[][maxBoardSize], const int& boardSize);
void movement(char gameBoard[][maxBoardSize], const int& boardSize, int yPosition, char whichUser);
char movementComputer(char gameBoard[][maxBoardSize],const int& boardSize);
int  user1Move(char gameBoard[][maxBoardSize],int xPosition);	// UserVsUser = 0, UserVsComputer = 1
int  user2AndComputerMove(char gameBoard[][maxBoardSize],int xPosition, int userVsComputerFlag=0); 
void saveCommand(const int& boardSize,string outputFile,char gameSelection,char readBoard[maxCharNumber],char userInputChars[maxCharNumber],int userInputNumber);
int  loadCommandInitial(char gameBoard[][maxBoardSize],const int& boardSize, string inputFile, char readBoard[maxCharNumber]);
int  loadCommandContinue(string newInputFile,char& newGameSelection);
int  letterToBoardPosition(char& inputData);
string partition(string userInput, int& index);
string stringToLowerCase(string userInput);

#endif