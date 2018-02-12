#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime> 
#include "connectFour.h"

using namespace std;


// Check the validity of the input
bool boardSizeCheck(int size)
{

	if(size % 2 == 0 && size >= 4 && size <=20){
		return size;
	} 
	else if(size == 2 || size==0 || size % 2 == 1 ) {
		cout << endl << "Invalid Board Size !! " << endl << "Board size must be even number 4x4, 6x6, 8x8, ... 20x20 !\n"<< endl;
		return false;
	}
	else {
		cout << endl << "Invalid Board Size !!" << endl << "Board size could not be character !!!!\n"<< endl;
		return false;
	}
}

// Fill initial board with empty cells
void initialBoard(char gameBoard[][maxBoardSize], int boardSize)
{
	for(int i=0; i<boardSize; ++i) {
		for(int j=0; j<boardSize; ++j) {
				gameBoard[i][j]='.';
			}
		}
}

// Display board during the game positions
void displayBoard(char gameBoard[][maxBoardSize], int boardSize)
{

	char boardCharacter = 'a';  
	cout << endl;
	cout << ' ';

    for(int i = 0; i<boardSize; i++)
       cout << static_cast<char>(boardCharacter + i) << "  " ;
       cout << endl;
            for(int j  = 0; j < boardSize; j++){            
                for(int i = 0; i< boardSize; i++){
                        cout << " " << gameBoard[j][i] << " ";
                }
        		cout << endl;   
    		}                 
}

// Display board step range to prompt the players
void printBoardStepRange(int boardSize)
{
	char boardCharacter = 'A';  
    for(int i = 0; i<boardSize; i++)
       cout << static_cast<char>(boardCharacter + i) << "." ;
}


// Two players game function.
void twoPlayers(int boardSize)
{
	
	int successInput=0;
	int yPosition=0;
	static int addNewCell=0;
	char board[maxBoardSize][maxBoardSize],user1Step='\0',user2Step='\0';

	initialBoard(board, boardSize);
	displayBoard(board, boardSize);
	
	while(addNewCell < boardSize*boardSize) {
		
				if(successInput == 0){

						cout << endl <<"Use positions such as ";
						printBoardStepRange(boardSize);
						cout << endl << "Enter User 1 (X) Movement: ";
						cin >> user1Step;

						for(char stepChar='A'; stepChar<='Z'; ++stepChar) {
							if(stepChar == user1Step && yPosition<boardSize){
									if(board[0][yPosition] == '.'){
										movement(board,boardSize,yPosition,'X');
										user1Move(board,boardSize-1);
										displayBoard(board, boardSize);
										++addNewCell;
										successInput=1;	
									}

									else {
										cout << endl << "> Column is full.Invalid Step !" << endl;
										successInput=0;
									}	

							}
								++yPosition;		
						}
						yPosition=0;
				}
				
				if(successInput == 1) {

					cout << endl <<"Use positions such as ";
					printBoardStepRange(boardSize);
					cout << endl <<"Enter User 2 (O) Movement: ";
					cin >> user2Step;

							for(char stepChar='A'; stepChar<='Z'; ++stepChar) {
								if(stepChar == user2Step && yPosition<boardSize){

									if(board[0][yPosition] == '.'){
										movement(board,boardSize,yPosition,'O');
										user2AndComputerMove(board,boardSize-1,0);
										displayBoard(board, boardSize);
										++addNewCell;
										successInput=0;	
									}
									else {
										cout << endl << "> Column is full.Invalid Step !" << endl;
										successInput=1;
									}
								}
									++yPosition;
							}
					yPosition=0;	
				}							

				if(addNewCell == boardSize*boardSize) {
					cout << endl << "Board Filled.Start Again !" << endl;	
				}	
		}	
}

void userVersusComputer(int boardSize)
{

	int successInput=0;
	int yPosition=0, computerYposition=0;
	static int addNewCell=0;
	char board[maxBoardSize][maxBoardSize],user1Step='\0';
	char computerStepChar='A';

	initialBoard(board, boardSize);
	displayBoard(board, boardSize);

	srand((unsigned)time(0)); 

		while(addNewCell < boardSize*boardSize) 
		{
				if(successInput == 0){
							
						cout << endl <<"Use positions such as ";
						printBoardStepRange(boardSize);
						cout << endl << "Enter User 1 (X) Movement: ";
						cin >> user1Step;

						for(char stepChar='A'; stepChar<='Z'; ++stepChar) {
							if(stepChar == user1Step && yPosition<boardSize){

									if(board[0][yPosition] == '.'){
										movement(board,boardSize,yPosition,'X');
										user1Move(board,boardSize-1);
										displayBoard(board, boardSize);
										++addNewCell;
										successInput=1;	
									}
									else {
										cout << endl << "> Column is full.Invalid Step !" << endl;
										successInput=0;
									}
							}
								++yPosition;		
						}
						yPosition=0;
				}

				if(successInput == 1) {

						cout << endl << "Computer (O) Movement: ";

					    computerYposition = (rand()%boardSize); 

					    cout << static_cast<char>(computerStepChar + computerYposition) << endl ;

					    if(board[0][computerYposition] == '.'){
							movement(board,boardSize,computerYposition,'O');
						    user2AndComputerMove(board,boardSize-1,1);
							displayBoard(board, boardSize);
							++addNewCell;
							successInput=0;
						} 
						else {
							cout << endl << "> Invalid Computer Step.Column is full !" << endl;
							successInput=1;
						}
				}

				if(addNewCell == boardSize*boardSize) {
					cout << endl << "Board Filled.Start Again !" << endl;
				}
		}
}

// If the game has any movement,fill the empty cells from down to up
void movement(char gameBoard[][maxBoardSize], int boardSize, int yPosition, char whichUser)
{

	int flag=1;
	
		for(int i=boardSize; i>=0; --i){
						if(gameBoard[i][yPosition] == '.'){
							gameBoard[i][yPosition] = whichUser;
							break;
						}
						if(gameBoard[i][yPosition] != '.' && flag ==0){
								for(int j=1; j<=boardSize; ++j){
											if(gameBoard[i-j][yPosition] == '.') {
												gameBoard[i-j][yPosition] = whichUser;
												flag = 1;
												break;
											}
								}	
						} 
				}
	
}



// User 1 Movement Function and control game status for connected cells
void user1Move(char gameBoard[][maxBoardSize], int xPosition)
{
	int i=0,j=0;

	for(i=0; i<=xPosition; ++i){
		for(j=0; j<=xPosition; ++j) {

			if(gameBoard[i][j] == 'X'){
				// UP TO DOWN 
				if(i + 3 < xPosition+1){
					if(gameBoard[i+1][j] == 'X' && gameBoard[i+2][j] == 'X' && gameBoard[i+3][j] == 'X') {
						gameBoard[i][j]   = 'x';
						gameBoard[i+1][j] = 'x';
						gameBoard[i+2][j] = 'x';
						gameBoard[i+3][j] = 'x';
						displayBoard(gameBoard, xPosition+1);
						cout << endl <<"Game Over .." << endl;
						cout << "Winner --> User 1 (X)"<<endl;
						exit(EXIT_SUCCESS);
					}	
				}
				// LEFT TO RIGHT
				if(j + 3 < xPosition+1){
					if(gameBoard[i][j+1] == 'X' && gameBoard[i][j+2] == 'X' && gameBoard[i][j+3] == 'X'){
						gameBoard[i][j]   = 'x';
						gameBoard[i][j+1] = 'x';
						gameBoard[i][j+2] = 'x';
						gameBoard[i][j+3] = 'x';
						displayBoard(gameBoard, xPosition+1);
						cout << endl <<"Game Over .." << endl;
						cout << "Winner --> User 1 (X)"<<endl;
						exit(EXIT_SUCCESS);
					}			
				}
				// DIAGONAL LEFT TO RIGHT
				if(j + 3 < xPosition+1){
					if(gameBoard[i+1][j+1] == 'X' && gameBoard[i+2][j+2] == 'X' && gameBoard[i+3][j+3] == 'X'){
						gameBoard[i][j]     = 'x';
						gameBoard[i+1][j+1] = 'x';
						gameBoard[i+2][j+2] = 'x';
						gameBoard[i+3][j+3] = 'x';
						displayBoard(gameBoard, xPosition+1);
						cout << endl <<"Game Over .." << endl;
						cout << "Winner --> User 1 (X)"<<endl;
						exit(EXIT_SUCCESS);
					}	
				}
				// DIAGONAL RIGHT TO LEFT
				if(j - 3 >= 0 ){
					if(gameBoard[i+1][j-1] == 'X' && gameBoard[i+2][j-2] == 'X' && gameBoard[i+3][j-3] == 'X'){
						gameBoard[i][j]     = 'x';
						gameBoard[i+1][j-1] = 'x';
						gameBoard[i+2][j-2] = 'x';
						gameBoard[i+3][j-3] = 'x';
						displayBoard(gameBoard, xPosition+1);
						cout << endl <<"Game Over .." << endl;
						cout << "Winner --> User 1 (X)"<<endl;
						exit(EXIT_SUCCESS);
					}
				}	
			}	
		}
	}
}

// User 2 Movement Function and control game status for connected cells
void user2AndComputerMove(char gameBoard[][maxBoardSize],int xPosition, int userVsComputerFlag)
{
	
	int i=0,j=0;

	for(i=0; i<=xPosition; ++i){
		for(j=0; j<=xPosition; ++j) {

			if(gameBoard[i][j] == 'O'){
				// UP TO DOWN
				if(i+3 < xPosition+1){
					if(gameBoard[i+1][j] == 'O' && gameBoard[i+2][j] == 'O' && gameBoard[i+3][j] == 'O'){
						gameBoard[i][j]   = 'o';
						gameBoard[i+1][j] = 'o';
						gameBoard[i+2][j] = 'o';
						gameBoard[i+3][j] = 'o';
						displayBoard(gameBoard, xPosition+1);
						if(userVsComputerFlag == 0){
							cout << endl <<"Game Over .." << endl;
							cout << "Winner --> User 2 (O)"<<endl;
							exit(EXIT_SUCCESS);
						}
						if(userVsComputerFlag == 1) {
							cout << endl <<"Game Over .." << endl;
							cout << "Winner --> Computer (O)" << endl;
							exit(EXIT_SUCCESS);
						}
					}
				}
				// LEFT TO RIGHT
				if(j+3 < xPosition+1){
					if(gameBoard[i][j+1] == 'O' && gameBoard[i][j+2] == 'O' && gameBoard[i][j+3] == 'O'){ 
						gameBoard[i][j]   = 'o';
						gameBoard[i][j+1] = 'o';
						gameBoard[i][j+2] = 'o';
						gameBoard[i][j+3] = 'o';
						displayBoard(gameBoard, xPosition+1);
						if(userVsComputerFlag == 0){
							cout << endl <<"Game Over .." << endl;
							cout << "Winner --> User 2 (O)"<<endl;
							exit(EXIT_SUCCESS);
						}
						if(userVsComputerFlag == 1) {
							cout << endl <<"Game Over .." << endl;
							cout << "Winner --> Computer (O)" << endl;
							exit(EXIT_SUCCESS);
						}
					}
				}
				// DIAGONAL - LEFT TO RIGHT
				if(j+3 < xPosition+1){
					if(gameBoard[i+1][j+1] == 'O' && gameBoard[i+2][j+2] == 'O' && gameBoard[i+3][j+3] == 'O'){ 
						gameBoard[i][j]     = 'o';
						gameBoard[i+1][j+1] = 'o';
						gameBoard[i+2][j+2] = 'o';
						gameBoard[i+3][j+3] = 'o';
						displayBoard(gameBoard, xPosition+1);
						if(userVsComputerFlag == 0){
							cout << endl <<"Game Over .." << endl;
							cout << "Winner --> User 2 (O)"<<endl;
							exit(EXIT_SUCCESS);
						}
						if(userVsComputerFlag == 1) {
							cout << endl <<"Game Over .." << endl;
							cout << "Winner --> Computer (O)" << endl;
							exit(EXIT_SUCCESS);
						}
					}
				}
				// DIAGONAL - RIGHT TO LEFT
				if(j-3 >= 0 ){
					if(gameBoard[i+1][j-1] == 'O' && gameBoard[i+2][j-2] == 'O' && gameBoard[i+3][j-3] == 'O'){
						gameBoard[i][j]     = 'o';
						gameBoard[i+1][j-1] = 'o';
						gameBoard[i+2][j-2] = 'o';
						gameBoard[i+3][j-3] = 'o';
						displayBoard(gameBoard, xPosition+1);
						if(userVsComputerFlag == 0){
							cout << endl <<"Game Over .." << endl;
							cout << "Winner --> User 2 (O)"<<endl;
							exit(EXIT_SUCCESS);
						}
						if(userVsComputerFlag == 1) {
							cout << endl <<"Game Over .." << endl;
							cout << "Winner --> Computer (O)" << endl;
							exit(EXIT_SUCCESS);
						}
					}
				}
			}	
		}
	}	
}






