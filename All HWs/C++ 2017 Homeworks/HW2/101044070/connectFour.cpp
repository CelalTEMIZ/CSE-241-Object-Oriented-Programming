#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <fstream>
#include <string>

#include "connectFour.h"

using namespace std;


int initialCellNumber=0;
// Check the validity of the input.
// If the user enter the wrong size,terminate the program with exit message.
bool boardSizeCheck(const int& boardSize)
{

	if(boardSize % 2 == 0 && boardSize >= 4 && boardSize <=20)
	{
		return boardSize;
	} 
	else if(boardSize == 2 || boardSize==0 || boardSize % 2 == 1 ) 
	{
		cerr << endl << "Invalid Board Size !! " << endl << "Board size must be even number 4x4, 6x6, 8x8, ... 20x20 !\n"<< endl;
		return false;
	}
	else 
	{
		cerr << endl << "Invalid Board Size !!" << endl << "Board size could not be character !!!!\n"<< endl;
		return false;
	}
}

// Fill initial board with empty cells.
void initialBoard(char gameBoard[][maxBoardSize], const int&  boardSize, char emptyCellChar)
{
	for(auto i=0; i<boardSize; ++i) 
		for(auto j=0; j<boardSize; ++j) 
				gameBoard[i][j]=emptyCellChar;
		
}

// Display board during the game positions.
void displayBoard(char gameBoard[][maxBoardSize], const int&  boardSize)
{

	// C++11 features.
	auto boardCharacter = 'a';  

    decltype(boardCharacter) letter = boardCharacter + 0;

	cout << endl;
	cout << ' ';

    for(int i = 0; i<boardSize; i++)
       cout << static_cast<char>(letter + i) << "  " ;
       cout << endl;
            for(int j  = 0; j < boardSize; j++){            
                for(int i = 0; i< boardSize; i++){
                        cout << " " << gameBoard[j][i] << " ";
                }
        		cout << endl;   
    		}  

}

// Convert user input string to lower case
string stringToLowerCase(string userInput) 
{
   int i = 0;
 
   while (userInput[i] != '\0') {
      if (userInput[i] >= 'A' && userInput[i] <= 'Z') {
         userInput[i] = userInput[i] + 32;
      }
      ++i;
   }

   return userInput;
}

// Display board step range to prompt the players.
void printBoardStepRange(const int& boardSize)
{
	auto boardCharacter = 'A';  
    for(auto i = 0; i<boardSize; i++)
       cout << static_cast<char>(boardCharacter + i) << "." ;
}

// Convert the input file characters to int values.
int letterToBoardPosition(char& inputData)
{
	char letter = 'A';	
	int  intValue=0;
	
	for(intValue=0,letter='A'; letter<='Z'; ++letter,++intValue) 
		if(letter == inputData)
			return intValue;	
}

// Divide user inputs to partitions
// Ignore all unnecessary parts.
string partition(string userInput, int& index) 
{
    int i=0,firstCharPosition = index;
    string token = "";

    i = firstCharPosition;
    int inputSize = userInput.length();

    while(i<=inputSize){
    	if (userInput[i] == ' ' || userInput[i] == '\0' || userInput[i] == '\t') {
            token = userInput.substr(firstCharPosition, i - index);
            index = i;
            break;
        }
        ++i;
    }

    while(index <= inputSize && (token == " " || token == "\0" || token == "\t")) {
        index++;
        return partition(userInput, index);
    }

    return token;
}


void startGame(string firstUserCommand)
{

	ifstream fin;
	int lastPosition=0, size=0;
	char choice = '\0';

	string load="",inpFile="";

	load = partition(firstUserCommand,lastPosition);

    if(load == "LOAD") 
    {
		inpFile=partition(firstUserCommand,lastPosition);
		fin.open(inpFile);

		if(fin.fail()){
			cerr << "Input file opening failed" << endl;
			exit(1);
		}

		size = loadCommandContinue(inpFile,choice);
	}

	else {

		cerr << "Wrong user command !" << endl;
		exit(1);
	}

	if(boardSizeCheck(size)){

		switch(choice)
		{
			case 'P':
				twoPlayers(inpFile,size);
				break;

			case 'C':
				userVersusComputer(inpFile,size);
				break;

			default:
				cerr << "Wrong Input.Exit The Game !" << endl;
		}

	}
	
	fin.close();

}


// Two players game function.
// When the user enter 'P' character to game selection,process this function.
void twoPlayers(string inputFile,const int& boardSize)
{
	int successInput=0,lastPosition=0,user2StepStop=0;
	static int addNewCell=0;
	int gameStatus=0;
	char board[maxBoardSize][maxBoardSize];

	string user1Step="",user2Step="",loadFileName="";

	string alphabetOrder = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


	char newGameSelection='\0';


	char userFileInput[maxCharNumber];
	char userInputChars[maxCharNumber];
	int  index=0;

	cout << endl << "Game: User 1 (X) Vs User 2 (O)"<<endl;
	cout << "Board Size: " << boardSize << endl;

	initialBoard(board, boardSize);

	addNewCell = loadCommandInitial(board,boardSize,inputFile,userFileInput);


	initialCellNumber = addNewCell;

	if(addNewCell>=boardSize*boardSize){
		cout << endl << "Game board is already full !" << endl;
		gameStatus=1;

	}
	
	displayBoard(board,boardSize);
	
	while(addNewCell < boardSize*boardSize && gameStatus==0) {
		
		if(successInput == 0)
		{

			cout << endl << "> Enter the 'LOAD yourTextFile' command to load the new game." << endl;
			cout << "> Enter the 'SAVE yourTextFile' command to save the current game." << endl;

			cout << "> Continue the game use positions such as ";
			printBoardStepRange(boardSize);
			cout << endl << endl << "Enter User 1 (X) Movement: ";

			getline(cin,user1Step);

			string command="", outFile="";
			lastPosition=0;
			command = partition(user1Step,lastPosition);


			if(command == "SAVE") {
				outFile = partition(user1Step,lastPosition);
				saveCommand(boardSize,outFile,'P',userFileInput,userInputChars,index);

			}


			if(command == "LOAD")
			{
				string newInputFile = partition(user1Step,lastPosition);

				int newBoardSize = loadCommandContinue(newInputFile,newGameSelection);

				if(newGameSelection=='C')
				{
					userVersusComputer(newInputFile,newBoardSize);
					break;
				}
				if(newGameSelection=='P')
				{
					twoPlayers(newInputFile,newBoardSize);
					break;
				}

			}

			else {
				for(int i=0; i<26; ++i){
					if(alphabetOrder[i] == command[0]){
						if(board[0][i] == '.' && i<boardSize )
						{
							movement(board,boardSize,i,'X');
							gameStatus=user1Move(board,boardSize-1);
							++addNewCell;


							userInputChars[index] = command[0];
							++index;



							if(gameStatus==0){
								displayBoard(board, boardSize);
								successInput=1;	
							}
						}

						else 
						{
							if(i > boardSize-1 && command !="SAVE" && command !="LOAD")
							{
							
								cerr << endl << "> Wrong character or Incomplete command.Invalid Step !" << endl;
								successInput=0;
							}
							if(board[0][i] != '.' && i<boardSize)
							{
								cerr << endl << "> Column is full.Invalid Step !" << endl;
								successInput=0;
							}	
						}

						if(addNewCell==boardSize*boardSize)
							user2StepStop=1;
					}


				}
			}
		}
				
		if(successInput == 1 && user2StepStop !=1 && gameStatus==0) {

				cout << endl << "> Enter the 'LOAD yourTextFile' command to load the new game." << endl;
				cout <<"> Enter the 'SAVE yourTextFile' command to save the current game." << endl;
				cout <<"> Continue the game use positions such as ";
				printBoardStepRange(boardSize);
				cout << endl << endl << "Enter User 2 (O) Movement: ";

				getline(cin,user2Step);
	
				string command="",outFile="";
				lastPosition=0;
				command = partition(user2Step,lastPosition);


				if(command == "LOAD")
				{

					string newInputFile = partition(user2Step,lastPosition);


					int newBoardSize = loadCommandContinue(newInputFile,newGameSelection);

					if(newGameSelection=='C')
					{
						userVersusComputer(newInputFile,newBoardSize);
						break;
					}
					if(newGameSelection=='P')
					{
						twoPlayers(newInputFile,newBoardSize);
						break;
					}

				}


				if(command == "SAVE") {
					outFile = partition(user2Step,lastPosition);
					saveCommand(boardSize,outFile,'P',userFileInput,userInputChars,index);
					
				}

				else {
					for(int i=0; i<26; ++i){
						if(alphabetOrder[i] == command[0]){
							if(board[0][i] == '.' && i<boardSize){
								movement(board,boardSize,i,'O');
								gameStatus=user2AndComputerMove(board,boardSize-1);
								++addNewCell;

								// User valid inputs
								userInputChars[index] = command[0];
								++index;

								if(gameStatus == 0){
									displayBoard(board, boardSize);
									successInput=0;	
								}
							}
							else {


								if(i > boardSize-1 && command !="SAVE" && command !="LOAD")
								{
									cerr << endl << "> Wrong character or Incomplete command.Invalid Step !" << endl;
									successInput=1;
								}

								if(board[0][i] != '.' && i<boardSize)
								{
									cerr << endl << "> Column is full.Invalid Step !" << endl;
									successInput=1;
								}

							}
						}
					}
				}		
		}							
			if(addNewCell == boardSize*boardSize && gameStatus==0) {
				cerr << endl << "Board Filled.Start Again !" << endl;	
			}		
		}	
}

// User Vs Computer function.
// When the user enter 'C' character to game selection,process this function.
void userVersusComputer(string inputFile,const int& boardSize)
{

	int  computerYposition=0,lastPosition=0;
	char computerStepChar='A';
	int successInput=0;
	static int addNewCell=0;
	char board[maxBoardSize][maxBoardSize];
	string user1Step="",loadFileName="";

	string alphabetOrder = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	int computerStepStop=0;
	static int gameStatus = 0;

	char newGameSelection='\0';


	char userFileInput[maxCharNumber];
	char userInputChars[maxCharNumber];
	int  index=0;

	srand((unsigned)time(0)); 

	cout << endl << "Game: User(X) Vs Computer(O)"<<endl;
	cout << "Board Size: " << boardSize << endl;
	initialBoard(board, boardSize);

	//addNewCell = loadCommandInitial(board,boardSize,inputFile);

	addNewCell = loadCommandInitial(board,boardSize,inputFile,userFileInput);
	initialCellNumber = addNewCell;


	if(addNewCell>=boardSize*boardSize)
	{
		cout << endl << "Game board is already full !" << endl;
		gameStatus=1;
	}
	

	displayBoard(board, boardSize);	

	
	while(addNewCell < boardSize*boardSize && gameStatus==0) {

		if(successInput == 0){

			cout << endl << "> Enter the 'LOAD yourTextFile' command to load the new game." << endl;
			cout <<"> Enter the 'SAVE yourTextFile' command to save the current game."<< endl;
			cout <<"> Continue the game use positions such as ";
			printBoardStepRange(boardSize);
			cout << endl << endl << "Enter User (X) Movement: ";

			getline(cin,user1Step);
	
			string command="";
			lastPosition=0;
			command = partition(user1Step,lastPosition);


			if(command == "LOAD")
			{
				string newInputFile = partition(user1Step,lastPosition);

				int newBoardSize = loadCommandContinue(newInputFile,newGameSelection);

				if(newGameSelection=='C')
				{
					userVersusComputer(newInputFile,newBoardSize);
					break;
				}
				if(newGameSelection=='P')
				{
					twoPlayers(newInputFile,newBoardSize);
					break;
				}

			}


			if(command == "SAVE") 
			{
				string outFile = partition(user1Step,lastPosition);
				//saveCommand(board,boardSize,outFile,'C');

				saveCommand(boardSize,outFile,'C',userFileInput,userInputChars,index);

			}

			else {

					for(int i=0; i<26; ++i)
					{
						if(alphabetOrder[i] == command[0])
						{
							if(board[0][i] != '.' && i<boardSize)
							{
								cerr << endl << "> Column is full.Invalid Step !" << endl;
								successInput=0;

							}

							if(board[0][i] == '.' && i<boardSize)
							{
								movement(board,boardSize,i,'X');
								gameStatus = user1Move(board,boardSize-1);
								++addNewCell;	

								// User valid inputs
								userInputChars[index] = command[0];
								++index;

								if(gameStatus == 0)
								{
									displayBoard(board, boardSize);
									successInput=1;
								}
							}

			
							if(i > boardSize-1 && command !="SAVE" && command !="LOAD"){
								cerr << endl << "> Wrong character or Incomplete command.Invalid Step !" << endl;
								successInput=0;
							}

							if(addNewCell==boardSize*boardSize)
								computerStepStop=1;
							
						}
					}
			}
		}	

	if(successInput == 1 && computerStepStop != 1 && gameStatus!=1) {

	    computerYposition = (rand()%boardSize); 

	    // If computer step is success,load the cell to game board
	    if(board[0][computerYposition] == '.'){
	    	cout << endl << "Computer (O) Movement: ";
	    	cout << static_cast<char>(computerStepChar + computerYposition) << endl ;
			movement(board,boardSize,computerYposition,'O');
		    gameStatus = user2AndComputerMove(board,boardSize-1,1);
		    ++addNewCell;

		    // User valid inputs
			userInputChars[index] = static_cast<char>(computerYposition + 'A');
			++index;
		
		    if(gameStatus==0){
				displayBoard(board, boardSize);
				successInput=0;	
			}
		} 
		else {
			// If computer step is fail, my algorithm will load the cell
			
			userInputChars[index] = movementComputer(board,boardSize);
			++index;


			gameStatus = user2AndComputerMove(board,boardSize-1,1);
			
			++addNewCell;
			if(gameStatus==0){
				displayBoard(board, boardSize);	
				successInput=0;
			}
		}

	}
		if(addNewCell == boardSize*boardSize && gameStatus==0) {
			cerr << endl << "Board Filled.Start Again !" << endl;
		}
	} // End while
}


// Return new input file's board size during the game
int loadCommandContinue(string newInputFile, char& newGameSelection)
{

	ifstream fin;
	
	int flagGameSelection=1;


	fin.open(newInputFile);

	if(fin.fail()){
		cerr << "Input file opening failed" << endl;
		exit(1);
	}


	int readSize;

	while(fin >> readSize){
		if(readSize>=0 && readSize<=20)
			break;
	}

	char nextInputChar;
	while(flagGameSelection==1){
			fin.get(nextInputChar);
			if(nextInputChar == 'P' || nextInputChar == 'C'){
				newGameSelection = nextInputChar;
				flagGameSelection=0;
			}
		}


	fin.close();

	return readSize;

}


// When the user enters the command LOAD text file,
// Program will load the game board from this file.
int loadCommandInitial(char gameBoard[][maxBoardSize],const int& boardSize, 
			string inputFile,char readBoard[maxCharNumber])
{

	ifstream fin;
	//char readBoard[maxCharNumber];
	char nextInputChar='\0';
	int  i=0,availableInputNumber=0;

	int gameSelectionCounter=0;
	char letter = 'A';


	fin.open(inputFile,ios::in | ios::binary);


	if(fin.fail()){
		cerr << "Input file opening failed" << endl;
		exit(1);
	}

	fin.get(nextInputChar);

	while(!fin.eof()) {
	
		// Check available characters in text file
		if(nextInputChar != '\n' && nextInputChar !='\0' && nextInputChar >='A' && nextInputChar<='Z'){

										// First character is user's game selection.Ignore this character.
										// P or C
			++gameSelectionCounter;

			// Second character and others will load game board
			if(gameSelectionCounter !=1 && nextInputChar >='A' && nextInputChar<(letter+boardSize)){
					readBoard[i] = nextInputChar;
					//cout << readBoard[i] <<endl;
					++i;
					++availableInputNumber;	


			}
		}
		
	fin.get(nextInputChar);

	}

	if(availableInputNumber!=0)
	{
			
			// Put available characters to game board in order
			for(int i=0; i<availableInputNumber; ++i){
				if(i%2==0)
					movement(gameBoard,boardSize,letterToBoardPosition(readBoard[i]),'X');
				else
					movement(gameBoard,boardSize,letterToBoardPosition(readBoard[i]),'O');
			}
	}
	
	fin.close();

	return availableInputNumber;
}
// When the user enters the command SAVE text file,
// Program will save the current game status to this file.
void saveCommand(const int& boardSize, string outputFile, char gameSelection,
							char readBoard[maxCharNumber],char userInputChars[maxCharNumber],int userInputNumber)
{

     /*auto boardCharacter = 'P';  

    decltype(boardCharacter) letter = boardCharacter + 0;

    auto boardCharacter2 = 'C';  

    decltype(boardCharacter) letter2 = boardCharacter2 + 0; */

    ofstream fout;

	fout.open(outputFile);

	if(fout.fail()) {
		cerr << "Input file opening failed" << endl;
		exit(1);
	}
    

	fout  << boardSize << endl;

	if(gameSelection=='P')
		fout << 'P'<<endl;
	else 
		fout <<'C'<< endl;


	for(int i=0; i<initialCellNumber; ++i)
			fout << readBoard[i] << endl;

	
	for(int j=0; j<userInputNumber; ++j)
			fout << userInputChars[j] << endl;
	

    fout.close();  

    cout << endl << "> The current game status is written to "<< outputFile << " file." <<endl<<endl;     
}


// If the game has any movement,program will fill the empty cells from down to up
void movement(char gameBoard[][maxBoardSize], const int&  boardSize, int yPosition, char whichUser)
{

	int flag=1;
	
		for(int i=boardSize; i>=0; --i){
				if(gameBoard[i][yPosition] == '.'){
					gameBoard[i][yPosition] = whichUser;
					break;
				}
				if(gameBoard[i][yPosition] != '.' ){
						for(int j=1; j<=boardSize; ++j){
									if(gameBoard[i-j][yPosition] == '.') {
										gameBoard[i-j][yPosition] = whichUser;
										
										break;
									}
						}	
				} 
		}
}

// If the computer has invalid step,any valid step will load the game board.
char movementComputer(char gameBoard[][maxBoardSize], const int& boardSize)
{
	bool flag = false;
	char letter='A';
	int i=0,j=0;

	char computerStep='\0';

	for(i=boardSize; (i>=0) && !flag; --i)
		for(j=0; (j<=boardSize) && !flag; ++j)
			if(gameBoard[i][j] == '.'){
				gameBoard[i][j] = 'O';
				flag = true;
			}


		computerStep = static_cast<char>(letter + (j-1));

		cout << endl << "Computer (O) Movement: ";
	    cout << computerStep << endl ;

	return computerStep;

}

// User 1 Movement Function and control game status for connected cells
int user1Move(char gameBoard[][maxBoardSize], int xPosition)
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
						return 1;
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
						return 1;
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
						return 1;
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
						return 1;
					}
				}	
			}	
		}
	}


	return 0;
}

// User 2 Movement Function and control game status for connected cells
int user2AndComputerMove(char gameBoard[][maxBoardSize],int xPosition, int userVsComputerFlag)
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
							return 1;
						}
						if(userVsComputerFlag == 1) {
							cout << endl <<"Game Over .." << endl;
							cout << "Winner --> Computer (O)" << endl;
							return 1;
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
							return 1;
						}
						if(userVsComputerFlag == 1) {
							cout << endl <<"Game Over .." << endl;
							cout << "Winner --> Computer (O)" << endl;
							return 1;
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
							return 1;
						}
						if(userVsComputerFlag == 1) {
							cout << endl <<"Game Over .." << endl;
							cout << "Winner --> Computer (O)" << endl;
							return 1;
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
							return 1;
						}
						if(userVsComputerFlag == 1) {
							cout << endl <<"Game Over .." << endl;
							cout << "Winner --> Computer (O)" << endl;
							return 1;
						}
					}
				}
			}	
		}
	}

	return 0;	
}






