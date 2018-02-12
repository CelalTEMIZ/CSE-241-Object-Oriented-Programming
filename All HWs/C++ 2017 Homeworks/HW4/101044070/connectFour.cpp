#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <fstream>
#include <string>
#include "connectFour.h"

using namespace std;

// Static member initializations
int ConnectFour::livingCellAll=0;
int ConnectFour::livingCellUser1=0;
int ConnectFour::livingCellUser2=0;
int ConnectFour::livingCellInFile=0;
int ConnectFour::order=0;
bool ConnectFour::winner=false;
bool ConnectFour::winner2=false;



// No parameter constructor creates a 5x5 game
ConnectFour::ConnectFour():currentWidth(5),currentHeight(5)
{   
    Cell** gameBoard = new Cell*[getCurrentHeight()]; // Row number
    for(int i=0; i<getCurrentHeight(); ++i)
        gameBoard[i] = new Cell[getCurrentWidth()];   // Column Number
}

//Contructor takes number of rows and columns as parameters
ConnectFour::ConnectFour(int newCurrentHeight, int newCurrentWidth)
 {     
    setCurrentWidth(newCurrentWidth);
    setCurrentHeight(newCurrentHeight);
     
    Cell** gameBoard = new Cell*[getCurrentHeight()]; // Row number
    for(int i=0; i<getCurrentHeight(); ++i)
        gameBoard[i] = new Cell[getCurrentWidth()];   // Column Number
 }

// Constructor to some given game parameters
ConnectFour::ConnectFour(int newCurrentWidth,int newCurrentHeight,char newgameMode,char newgameSelection)
{
    setCurrentWidth(newCurrentWidth);
    setCurrentHeight(newCurrentHeight);
    setGameMode(newgameMode);
    setGameSelection(newgameSelection);

    Cell** gameBoard = new Cell*[getCurrentHeight()]; // Row number  
    for(int i=0; i<getCurrentHeight(); ++i)
        gameBoard[i] = new Cell[getCurrentWidth()];   // Column Number
}


// Constructor takes a text file as a parameter
ConnectFour::ConnectFour(string inputFile)
{ 
     readInputFile(inputFile);
}

// Copy Constructor
ConnectFour::ConnectFour(const ConnectFour& newConnectFourObject)
{
  // Copy the all game parameters
  gameMode = newConnectFourObject.getGameMode();
  boardFileName = newConnectFourObject.getBoardFileName();
  currentWidth = newConnectFourObject.getCurrentWidth();
  currentHeight = newConnectFourObject.getCurrentHeight();
  gameSelection = newConnectFourObject.getGameSelection();
  order = newConnectFourObject.order;
  livingCellAll = newConnectFourObject.getNumberOfLivingCell();
  livingCellUser1 = newConnectFourObject.getLivingCellUser1();
  livingCellUser2 = newConnectFourObject.getLivingCellUser2();
  livingCellInFile = newConnectFourObject.getLivingCellInFile();
  winner = newConnectFourObject.getWinner();
  winner2= newConnectFourObject.getWinner2();

  Cell** gameBoard = new Cell*[getCurrentHeight()]; // Row number
    for(int i=0; i<getCurrentHeight(); ++i)
        gameBoard[i] = new Cell[getCurrentWidth()];   // Column Number


  for(int i=0; i<getCurrentHeight(); ++i)
    for(int j=0; j<getCurrentWidth(); ++j)
      gameBoard[i][j]=newConnectFourObject.gameBoard[i][j];


}

// Assignment operator overload
ConnectFour& ConnectFour::operator =(const ConnectFour& rightSide)
{
  if(getCurrentHeight() != rightSide.getCurrentHeight())
  {
    // Delete older board
    for(int i=0; i<getCurrentHeight(); ++i)
        delete [] gameBoard[i];
        delete [] gameBoard;

   // Create new board
    Cell** gameBoard = new Cell*[rightSide.getCurrentHeight()]; // Row number
    for(int i=0; i<rightSide.getCurrentHeight(); ++i)
        gameBoard[i] = new Cell[rightSide.getCurrentWidth()];   // Column Number
  }


    // Assign all game parameters
    gameMode = rightSide.getGameMode();
    boardFileName = rightSide.getBoardFileName();
    currentWidth = rightSide.getCurrentWidth();
    currentHeight = rightSide.getCurrentHeight();
    gameSelection = rightSide.getGameSelection();
    order = rightSide.order;
    livingCellAll = rightSide.getNumberOfLivingCell();
    livingCellUser1 = rightSide.getLivingCellUser1();
    livingCellUser2 = rightSide.getLivingCellUser2();
    livingCellInFile = rightSide.getLivingCellInFile();
    winner = rightSide.getWinner();
    winner2= rightSide.getWinner2();

  for(int i=0; i<rightSide.getCurrentHeight(); ++i)
    for(int j=0; j<rightSide.getCurrentWidth(); ++j)
      gameBoard[i][j]=rightSide.gameBoard[i][j];

    return *this;

}

// Destructor
ConnectFour::~ConnectFour()
{
    for(int i=0; i<getCurrentHeight(); ++i)
        delete [] gameBoard[i];
        delete [] gameBoard;

   gameBoard = NULL;
}

// Operator== to compare two ConnectFour objects
bool ConnectFour::operator ==(ConnectFour& other) const
{
    // Compare all game parameters
    return (getCurrentWidth()==other.getCurrentWidth() &&
            getCurrentHeight()==other.getCurrentHeight() &&
            getGameMode()==other.getGameMode() &&
            getGameSelection()==other.getGameSelection() &&
            getBoardFileName()==other.getBoardFileName() &&
            getNumberOfLivingCell()==other.getNumberOfLivingCell() &&
            getLivingCellUser1()==other.getLivingCellUser1()&&
            getLivingCellUser2()==other.getLivingCellUser2()&&
            order == other.order &&
            livingCellInFile && other.livingCellInFile &&
            winner == other.winner &&
            winner2==other.winner2 ) ;

}

// Operator!= to compare two ConnectFour objects
bool ConnectFour::operator !=(ConnectFour& other) const
{
    return !(*this == other) ;
}

// Set current game width
inline void ConnectFour::setCurrentWidth(const int& newCurrentWidth)
{
    if(newCurrentWidth< 4 || newCurrentWidth>=30 ){
            cerr <<endl << "Invalid Game Board Width !!" << endl;
            exit(1);
    }
    else{
            currentWidth = newCurrentWidth;
    }
}
// Set current game height
inline void ConnectFour::setCurrentHeight(const int& newCurrentHeight)
{
    if(newCurrentHeight < 4){
            cerr << endl << "Invalid Game Board Height !!" << endl;
            exit(1);
    }
    else {
            currentHeight = newCurrentHeight;
    }
}

// Set the current game mode
inline void ConnectFour::setGameMode(const char& newGameMode)
{   
     if(newGameMode =='S' || newGameMode == 'M') {
         gameMode = newGameMode;
     }else{
         cerr << endl << "Game Mode must be S or M " << endl;
         exit(1);
     }
}
 

// Set the current game selection 
inline void ConnectFour::setGameSelection(const char& newGameSelection)
{
     if(newGameSelection =='P' || newGameSelection == 'C') {
         gameSelection= newGameSelection;
     }else{
         cerr << endl << "Game Mode must be P or C " << endl;
         exit(1);
     }     
 }

// Set the current game board file name
void ConnectFour::setBoardFileName(string newBoardFileName)
{
  boardFileName = newBoardFileName;
}

// Get the current game board file name
inline string ConnectFour::getBoardFileName() const
{
  return boardFileName;
}


// Get the current game mode
inline char ConnectFour::getGameMode() const 
{
    return gameMode;   
}

// Get the current game selection
char ConnectFour::getGameSelection() const 
{
    return gameSelection;   
}
  
// Get the current game board width - row number
inline int ConnectFour::getCurrentWidth() const 
{
    return currentWidth;  
}

// Get the current game board height - column number
inline int ConnectFour::getCurrentHeight() const
{
    return currentHeight;
}

// Load command function
void ConnectFour::load(string  inputFileName)
{
  ifstream fin;
  int  flagGameSelection=1;

  fin.open(inputFileName,ios::in | ios::binary);
 

  if(fin.fail()){
          cerr << "Input file opening failed" << endl;
          exit(1);
  }
    
  // Read all parameters about game board

    char nextInputChar;
    
    while(flagGameSelection==1){
          fin.get(nextInputChar);
          if(nextInputChar == 'S' || nextInputChar == 'M'){
                  setGameMode(nextInputChar);
                  flagGameSelection=0;
          }
    }


    string boardFile;
    fin >> boardFile;

    
    // This array holds the user input characters 
    char * charArray = new char [getCurrentWidth()*getCurrentHeight()];
    
    //resizeNewBoard(getCurrentWidth(),getCurrentHeight());
    

    flagGameSelection=1;
    while(flagGameSelection==1){
                    fin.get(nextInputChar);
                    if(nextInputChar == 'P' || nextInputChar == 'C'){
                          setGameSelection(nextInputChar);
                            flagGameSelection=0;
                    }
    }
    

   // Read user inputs to load command and save the array
    int i=0,availableInputNumber=0;
    char letter = 'A';
    while(!fin.eof()) {
      
                nextInputChar = fin.get();
                        
                // Check available characters in text file
                if(nextInputChar != '\n' && nextInputChar !='\0' && nextInputChar >='A' && nextInputChar<='Z')
                {                                                              
                    // Second character and others will load game board
                    if(nextInputChar >='A' && nextInputChar<(getCurrentWidth()))
                    { 
                      charArray[i] = nextInputChar; 
                      ++i;
                      ++availableInputNumber;
                      ++livingCellInFile;
                    }
                }      
    }                    
      
   // Put available chars to game board 
    if(availableInputNumber != 0)  
    {
        for(int i=0; i<availableInputNumber; ++i)
        {
            if(i%2==0){
                order = 0;
                movement(letterToBoardPosition(charArray[i]));
            }
            else{
                order = 1;
                movement(letterToBoardPosition(charArray[i]));
            }
         }   
    }

    fin.close();   
}

// Create new board to new input file
void ConnectFour::resizeNewBoard(int rowNumber, int columnNumber)
{   
    Cell** gameBoard = new Cell*[getCurrentHeight()]; // Row number
    
    for(int i=0; i<getCurrentHeight(); ++i)
        gameBoard[i] = new Cell[getCurrentWidth()];   // Column Number  
}

// Convert the input file characters to int values.
int ConnectFour::letterToBoardPosition(char& inputData)
{
    char letter = 'A';  
    int  intValue=0;

    for(intValue=0,letter='A'; letter<='Z'; ++letter,++intValue) 
            if(letter == inputData)
                    return intValue;  
}

// Display board situation during the game
// CellState
// User1(X)=1,User2(O)=2,Computer(O)=3,Empty( )=4,Asteriks(*)=5
// Little User1(x)=6
// Little User2(o)=7
void  ConnectFour::display() const
{ 
         
  char boardCharacter = 'A';  
  
  cout << endl;
  
  for(int i = 0; i<getCurrentWidth(); i++)
        cout << " " <<static_cast<char>(boardCharacter + i) << " " ;
    cout << "\n";
                       
    int j=0;

    for(int i=0; i<getCurrentHeight(); ++i){

        if(j==getCurrentWidth())
                cout << endl;

            for(j=0; j<getCurrentWidth(); ++j){
                                                                    // Every integer number is equal to game character
                    if(gameBoard[i][j].getCellState() == 1)     
                            cout << " " << "X" << " ";
                    else if (gameBoard[i][j].getCellState() == 2) 
                            cout << " " << "O" << " ";
                    else if (gameBoard[i][j].getCellState() == 3)
                            cout << " " << "O" << " ";
                    else if (gameBoard[i][j].getCellState() == 4)
                            cout << " " << " " << " ";
                    else if(gameBoard[i][j].getCellState() == 5)
                            cout << " " << "*" << " ";
                    else if(gameBoard[i][j].getCellState() == 6)
                            cout << " " << "x" << " ";
                    else if(gameBoard[i][j].getCellState() == 7)
                            cout << " " << "o" << " ";
                    else
                            cout << " " << " " << " ";
                }
  }
  cout << endl;  
}

// Prompt the user to input data
void ConnectFour::printBoardStepRange() const
{
    char boardCharacter = 'A';  
    for(int i = 0; i<getCurrentWidth(); i++)
       cout << static_cast<char>(boardCharacter + i) << "." ;  
}

// String parse to load and save commands
string ConnectFour:: partition(string userInput, int& index)
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

// Is the cell is live ?
bool ConnectFour::isLivingUser1Cells(ConnectFour::Cell cell)
{ 
 // User 1 = 1
    for(int i=0;i<getCurrentHeight(); ++i)
    {  
        for(int j=0; j<getCurrentWidth(); ++j )
            
        if(gameBoard[i][j].getCellState() == 1 && cell.getCellState() == 1)
        {
            return true;
        }
    }
    return false;
}
// Is the cell is live ?
bool ConnectFour::isLivingUser2Cells(ConnectFour::Cell cell)
{  
    // User 2 = 2
    for(int i=0;i<getCurrentHeight(); ++i)
    {  
        for(int j=0; j<getCurrentWidth(); ++j )
            
        if(gameBoard[i][j].getCellState() == 2 && cell.getCellState() == 2)
        {
            return true;
        }
    }   
    return false;
}

// Put the step characters to game board
// User1(X)=1,User2(O)=2,Computer(O)=3,Empty( )=4,Asteriks(*)=5
// Little User1(x)=6
// Little User2(o)=7
bool ConnectFour::movement(int yPosition)
{      

  bool inputState = true;

    for(int i=getCurrentHeight()-1; i>=0; --i)
    {
        if(gameBoard[i][yPosition].getCellState() == 5) // If the cell is asteriks,put the game cell 
        {  
          // User 1 movement paramaters set the game board
          if(order==0)
          {
             gameBoard[i][yPosition].setCellPosition(yPosition+'A');                     
             gameBoard[i][yPosition].setRowPosition(i);
             gameBoard[i][yPosition].setCellState(1);
             ++livingCellAll;
             inputState = true;     // If the movement is valid, it will return true
             break;
          }
          else
          {  
             // User 2 and Computer movement paramaters set the game board
             gameBoard[i][yPosition].setCellPosition(yPosition+'A');  
             gameBoard[i][yPosition].setRowPosition(i);
             gameBoard[i][yPosition].setCellState(2);
             ++livingCellAll;
             inputState = true;
             break; 
          }
          
       }  

       // Check the available board positions
       // If the movement is İnvalid, it will return false
      else if(gameBoard[i][yPosition].getCellState() == 4 || 
                    (gameBoard[0][yPosition].getCellState() == 1 || gameBoard[0][yPosition].getCellState() == 2))
        {
          cerr << endl<< endl << "> Column is full or all of them are empty.Invalid Step !!!"<<endl<<endl;
          inputState = false;
          break;

        }
  
    }  
    
    return inputState;      
}

// Smart computer move
// The character will put left to right end of the board
void ConnectFour::computerSmartMove()
{
  bool flag = false;
  char computerStepChar='A';
  int i=0,j=0;

  for(i=getCurrentHeight()-1; (i>=0) && !flag; --i)
    for(j=0; (j<getCurrentWidth()) && !flag; ++j)
      if(gameBoard[i][j].getCellState() == 5){
        gameBoard[i][j].setCellState(2);
        flag = true;
      }

  ++livingCellAll;
  cout << endl << "Smart Computer (O) Movement: ";
  cout << static_cast<char>(computerStepChar + (j-1)) << endl ;
}

// Multiple mode play function to user 1
void ConnectFour::play(char& cellPosition)
{

  char letter = 'A';  
  int  intValue=0; 

// Check the input data
  // If it is fail, re-enter new step
  if(cellPosition >'A'+(getCurrentWidth()-1) || !(cellPosition>='A' && cellPosition<='Z'))
  {
    char repeatChar='\0';
    while(1){
        cerr << endl << "> Wrong character.Invalid Step !" << endl;
        cout << endl << "Re-Enter Movement: ";
        cin >> repeatChar;
        
        if(repeatChar<'A'+getCurrentWidth() && (repeatChar>='A' && repeatChar<='Z') ){
            cellPosition = repeatChar;
            break; 
        }        
    }   
  }

// Check the input data
// If it is fail, re-enter new step
 if(isLivingUser1Cells(Cell(cellPosition,0))|| isLivingUser2Cells(Cell(cellPosition,0)))
 {
    char repeatChar='\0';
    while(1){
        cerr << endl << "> Column is full.Invalid Step !" << endl;
        cout << endl << "Re-Enter Movement: ";
        cin >> repeatChar;
        
        if(!isLivingUser1Cells(Cell(repeatChar,0)) && !isLivingUser2Cells(Cell(repeatChar,0))){
            cellPosition = repeatChar;
            break; 
        }        
    }    
 }  
  
 
  // If the cell is dead,put the step.
  // If the cell is live,re-enter new step 
  if(!isLivingUser1Cells(Cell(cellPosition,0)) && !isLivingUser2Cells(Cell(cellPosition,0)))
  {    
    // User 1 state  
      if (order==0)
      {
            for(intValue=0,letter='A'; letter<='Z'; ++letter, ++intValue) 
            {
                if(letter == cellPosition)
                {
                  // Fail user 1 step
                  if(movement(intValue) == false) 
                  {
                        while(1)
                        {
                          cout << "Re-Enter Movement: ";
                          char reStep;
                          cin >> reStep;

                          // Success user 1 step 
                          if((movement(letterToBoardPosition(reStep))) == true)
                          {
                            order=0;
                            break;
                          }
                        }
                    
                  }
                  // Success user 1 step
                  ++livingCellUser1;
                  display();
                  user1Win(); 
                  order=1;
                  if(gameEnded())
                       cout<<endl<<endl<<"Board Filled !"<<endl<<endl;
                  return ; 
                }
            }  
      } 
      
      // User 2 state
      if(order==1 && getGameSelection()=='P') {
          for(intValue=0,letter='A'; letter<='Z'; ++letter, ++intValue) 
            {
                if(letter == cellPosition)
                {              
                  order=1;
                  
                  // Fail user 2 step
                  if(movement(intValue) == false) 
                  {
                        while(1)
                        {
                          cout << "Re-Enter Movement: ";
                          char reStep;
                          cin >> reStep;

                          // Success user 2 step
                          if((movement(letterToBoardPosition(reStep))) == true)
                          {
                            order=0;
                            break;
                          }
                        }
                    
                  }

                  // Success user 2 step
                  ++livingCellUser2;
                  display();
                  user2OrComputerWin(); 
                  order=0;
                  if(gameEnded())
                       cout<<endl<<endl<<"Board Filled !"<<endl<<endl;
                  return ;
                }
            } 
      }   
  } 
}

// Multiple mode computer step
// If the any step is fail,it will make smart move in this way
void ConnectFour::play()
{

  int computerStep= (rand() % getCurrentWidth());
  order=1;

  if(movement(computerStep) == false) 
  {
    computerSmartMove();
    order=0;
    ++livingCellUser2;
    display();                     
    user2OrComputerWin(); 
  } 
  else 
  {
    order=0;
    ++livingCellUser2; 
    cout << endl << "Computer Step : " << static_cast<char>(computerStep+'A') << endl << endl;
    display();                    
    user2OrComputerWin(); 
  }                 
}


// Save the current game inputs to the given file
void ConnectFour::save(string outputFileName, char* userInputs, int& numberOfUserInputs)
{
    
    ofstream fout;

    fout.open(outputFileName);

    if(fout.fail()) {
            cerr << "Output file opening failed" << endl;
            exit(1);
    }
  
    // Write to file some input file parameters
    fout  << getGameMode() << endl;
    fout  << getBoardFileName() << endl;

    if(getGameSelection()=='P')
            fout <<'P'<<endl;
    else 
            fout <<'C'<< endl;
    
    // Write user inputs to given file
    for(int i=0; i<numberOfUserInputs; ++i)  
      fout << userInputs[i]<<endl;

    fout.close();  

    cout << endl << "> The current game status is written to "<< outputFileName << " file." <<endl<<endl;     
}
 
 // Read given board file,then put the cells on the board
void ConnectFour::readInputFile(string gameFile)
{
    
    int rowNumber=0,columnNumber=0;
    
    resizeBoard(gameFile,rowNumber,columnNumber);
   
    ifstream fin;
    fin.open(gameFile);
    
    if(fin.fail()){
            cerr << "Input file opening failed" << endl;
            exit(1);
    }
     
    
    gameBoard = new Cell*[rowNumber]; // Row number
    for(int i=0; i<rowNumber; ++i)
        gameBoard[i] = new Cell[columnNumber];   // Column Number
        

    int i=0,j=0;
    char nextChar;
   
    // Read all input file characters 
     fin.get(nextChar);

     while(!fin.eof()) {

                  // Put the given board file characters to game board
                  if(nextChar == '*')
                  {      
                      gameBoard[i][j].setAllPosition(j+'A',i);
                      gameBoard[i][j].setCellState(5);    // Asteriks Char
                  }
                  if(nextChar == ' '){
                      gameBoard[i][j].setAllPosition(j+'A',i);
                      gameBoard[i][j].setCellState(4);       // Empty Char
                  }


                  if(nextChar=='\n')
                  {
                    ++i;
                    if(i==rowNumber)
                    {
                      j=0;
                      break;
                    }
                    j=-1;
                  }

                  ++j;

        fin.get(nextChar);

      }
  

  fin.close(); 
    
}

// When the given any input file, compute row and column number
void ConnectFour::resizeBoard(string gameFile, int& rowNumber, int& columnNumber)
{
  int characters=0;
  
  ifstream fin;
  fin.open(gameFile);

  if(fin.fail()) {
    cerr << "Input file opening failed" << endl;
    exit(1);
 }

  char nextChar;
  int row=0,column=0;

  while(!fin.eof())
  {

        // COmpute the max column number
        if(nextChar != '\n' && fin.peek() != fin.eof())
        {
          ++characters;
        }

        
        if(characters > columnNumber)
          column = characters;

        // Row number
        if(nextChar == '\n'){
          characters=0;
          ++row; 
        }

        nextChar = fin.get();

  }

  rowNumber = row;
  columnNumber = column;
   
  // Rewind for input file to read characters
  //fin.clear();
  //fin.seekg(0);

  // Set current game parameters
  setCurrentHeight(rowNumber);               // Row Number
  setCurrentWidth(columnNumber);            // Column Number
      
  fin.close();
}

// Get the multuple mode game selection
void ConnectFour::multipleModeGameSelection()
{
    char  gameChoice='\0';
    cout << endl<< "P - User1 vs User2" << endl;
    cout << "C - User  vs Computer" << endl;
    cout << endl<< "Enter Game Selection : ";
    cin >> gameChoice;
    setGameSelection(gameChoice); 
}

// Single step play function to users and computer
void ConnectFour::playGame()
{
 
    int lastPosition=0;
    char choice;
    
    string step="";
    string alphabetOrder = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    cin.ignore(1000, '\n'); 
    
    cout << endl<< "P - User1 vs User2" << endl;
    cout << "C - User  vs Computer" << endl;
    cout << endl<< "Enter Game Selection : ";
    cin >> choice;
    
    cin.ignore(1000, '\n'); 
    cout<<endl;
    
    setGameSelection(choice); 
    
    // Collect the user inputs from the keyboard
    char *userInputs = new char [getCurrentHeight()*getCurrentWidth()];
    int  count =0;
      
    while(winner==false && winner2==false)
    {   
            
        cout << endl;
        display();
        
        // Print living cell number 
        if(livingCellAll % 2 == 0)
        cout<<endl<<"LivingCell: "<<ConnectFour::getNumberOfLivingCell()<<endl;
        
        cout << endl << "> Enter the 'LOAD yourTextFile' command to load the new game." << endl;
        cout << "> Enter the 'SAVE yourTextFile' command to save the current game." << endl;
        cout << "> Continue the game use positions such as ";
        
        printBoardStepRange();

        if(order==0)
          cout << endl << endl << "User 1 (X) Movement : ";
        else
          cout << endl << endl << "User 2 (O) Movement : ";
         

        // Get the user step  
        getline(cin,step);  
        
        if(step.length() == 0)
        {
             exit (EXIT_SUCCESS);
        }

        string command="", outFile="";
        lastPosition=0;
        command = partition(step,lastPosition);
        
        // Save command
        if(command == "SAVE") 
        {
            outFile = partition(step,lastPosition);
            save(outFile,userInputs,count);
        }
        //LOad command
        if(command == "LOAD")
        {  
            string newInputFile = partition(step,lastPosition);
            load(newInputFile);
            livingCellAll = livingCellAll - livingCellInFile;        
        }

        // Put the player step
        else 
        {
              for(int i=0; i<26; ++i)
              {
                 if(alphabetOrder[i] == command[0])
                 {  
                    if(i<getCurrentWidth())
                    {   
                        if(order==0)   // Player 1
                        { 
                            userInputs[count] = command[0];   //Collect the user inputs from the keyboard
                            ++count;

                            if(movement(i) == false) {        // If the user movement is fail,repeat the step
                              order=0;
                              break;
                            }

                            ++livingCellUser1;                
                            user1Win();                       // Check user 1 game state
                            if(getGameSelection()=='P')
                            {
                                order=1;  // Player 2   
                            }
                            if(getGameSelection()=='C') 
                            { 
                                int computerStep= (rand() % getCurrentWidth());
                                order=1;

                                userInputs[count] = static_cast<char>(computerStep+'A');
                                ++count;

                                if(movement(computerStep) == false) {
                                  computerSmartMove();
                                  order=0;
                                  ++livingCellUser2;                     
                                  user2OrComputerWin(); 
                                  break;
                                }

                                cout << endl << "Computer Movement (O) : " << static_cast<char>(computerStep+'A') << endl << endl;
                                order=0;
                                ++livingCellUser2;
                                                        
                                user2OrComputerWin(); 
                                break;
                            }
                         
                         break;
                        }
                        
                        else if(order == 1 && getGameSelection() !='C')
                        {  

                         userInputs[count] = command[0];
                         ++count;

                         if(movement(i) == false) {
                            order=1;
                            break;
                         }
                         order=0;
                         ++livingCellUser2;
                     
                         user2OrComputerWin();
                         break;
                        }
                    }

                    else 
                    {
                        if(i > getCurrentWidth()-1 && command !="SAVE" && command !="LOAD")
                        {
                            cerr << endl << "> Wrong character or Incomplete command.Invalid Step !" << endl << endl;   
                        }
                         
                    }
                 }
            }    
        }
                        if(gameEnded())
                        {
                             cout<<"FINISH";
                             return ;
                        }            
        } // end while
    
}

bool ConnectFour::gameEnded()
{
    if(livingCellAll < getCurrentWidth()*getCurrentHeight())
        return false;   
    else
        return true;
}

ConnectFour::Cell::Cell()
{
    cellPosition = ' ';
    rowPosition  =  0;
    cellState = 0;
}

ConnectFour::Cell::Cell(const char& newCellPosition)
{
   cellPosition = newCellPosition;
   rowPosition = 0;
   cellState = 0;
}
ConnectFour::Cell::Cell(const int& newRowPosition)
{
   cellPosition = ' ';
   rowPosition = newRowPosition;
   cellState = 0;
}

ConnectFour::Cell::Cell(const char& newCellPosition, const int& newRowPosition)
{
    cellPosition = newCellPosition;
    rowPosition =  newRowPosition;  
    cellState = 0;
}


// Operator== to compare two cells
bool ConnectFour::Cell::operator ==(const ConnectFour::Cell& cellObject) const
{
    return (getCellPosition() == cellObject.getCellPosition() && 
            getRowPosition() == cellObject.getRowPosition() );
}

// https://stackoverflow.com/questions/8082190/overloading-operator-for-a-nested-private-class-possible
//Stream insertion operator for cell.
std::ostream& operator <<(std::ostream& outputStream, ConnectFour::Cell const& cellObject)
{   
    outputStream << "The Cell position : " << cellObject.getCellPosition() << endl;
    outputStream << "The Row position  : " << cellObject.getRowPosition()  << endl; 
    
    return outputStream;
}

//Stream extraction operator for cell.
std::istream& operator >>(std::istream& inputStream, ConnectFour::Cell & cellObject)
{
    char tempCellPosition;
    int  tempRowPosition;
    
    cout << "Enter cell position of cell: ";
    inputStream >> tempCellPosition;
  
    cout << "Enter row position of  cell: ";
    inputStream >> tempRowPosition;

    cellObject.setCellPosition(tempCellPosition);
    cellObject.setRowPosition(tempRowPosition);

    return inputStream;

}

ConnectFour::Cell::Cell(const int& newCellState,const char& newCellPosition, const int& newRowPosition)
{
    cellState = newCellState;
    cellPosition = newCellPosition;
    rowPosition =  newRowPosition;  
}

ConnectFour::Cell ConnectFour::Cell::operator ++() // Pre-Increment
{
   ++cellState;
   return Cell(cellState,cellPosition,rowPosition);
}


ConnectFour::Cell ConnectFour::Cell::operator ++(int ignoreMe) // Post-Increment
{
   int tempCellState = cellState;
   ++cellState;
   
   return Cell(tempCellState,cellPosition,rowPosition );
}

ConnectFour::Cell ConnectFour::Cell::operator --() // Pre-Decrement
{
   --cellState;
   return Cell(cellState,cellPosition,rowPosition);
}

ConnectFour::Cell ConnectFour::Cell::operator --(int ignoreMe) // Post-Decrement
{
    int tempCellState = cellState;
    --cellState;
    
   return Cell(tempCellState,cellPosition,rowPosition);
}


void ConnectFour::Cell::setCellPosition(const char& newCellPosition)
{
    if(newCellPosition > 'Z')
    {
        cout << "Invalid position of the cell " << endl;
        exit(1);
    }
    else {
        cellPosition = newCellPosition;   
    }    
}

void ConnectFour::Cell::setRowPosition(const int& newRowPosition)
{
    if(newRowPosition < 0)
    {
        cout << "Invalid Row Position " << endl;
        exit(1);
    }
    else
        rowPosition = newRowPosition;
}


void ConnectFour::Cell::setCellState(const int& newCellState)
{
    cellState = newCellState;
}


int  ConnectFour::Cell::getCellState() const
{
    return cellState;    
}


 void ConnectFour::Cell::setAllPosition(const char& newCellPosition,const int& newRowPosition)
 {
      cellPosition = newCellPosition;
      rowPosition =  newRowPosition;  
 }

char  ConnectFour::Cell::getCellPosition() const
{
    return cellPosition;
    
}

int ConnectFour::Cell::getRowPosition() const
{
    return rowPosition;
}

// User 1 game state
// If the four cell is same, user 1 will win the game
void ConnectFour::user1Win()
{
    
    for(int i=0; i<getCurrentHeight(); ++i)
    {         
        for(int j=0; j<getCurrentWidth(); ++j)
        {     
            if(gameBoard[i][j].getCellState() == 1)
            {    
                // UP TO DOWN 
                if(i+3<getCurrentHeight())
                {
  
                 if(gameBoard[i+1][j].getCellState() == 1 && gameBoard[i+2][j].getCellState() == 1 && gameBoard[i+3][j].getCellState() == 1)  
                    {
                    winner=true;
                      
                    gameBoard[i][j].setCellState(6);
                    gameBoard[i+1][j].setCellState(6);
                    gameBoard[i+2][j].setCellState(6);
                    gameBoard[i+3][j].setCellState(6);
                      
                      display();
                      cout << endl <<"Game Over .." << endl;
          cout << "Winner --> User 1 (X)"<<endl;
                      
      }
                }
                // LEFT TO RIGHT
    if(j + 3 <getCurrentWidth())
                { 

                    if(gameBoard[i][j+1].getCellState() == 1 && gameBoard[i][j+2].getCellState() == 1 && gameBoard[i][j+3].getCellState() == 1)
                    { 
                     winner=true;
                     
                     gameBoard[i][j].setCellState(6);
                     gameBoard[i][j+1].setCellState(6);
                     gameBoard[i][j+2].setCellState(6);
                     gameBoard[i][j+3].setCellState(6);
                     display();
                     cout << endl <<"Game Over .." << endl;
         cout << "Winner --> User 1 (X)"<<endl;
                     
                    }
                }
                
                // DIAGONAL LEFT TO RIGHT
                if(i  < getCurrentHeight()- 3 && j<getCurrentWidth()-3)
                {
                    if(gameBoard[i+1][j+1].getCellState() == 1 && gameBoard[i+2][j+2].getCellState() == 1 && gameBoard[i+3][j+3].getCellState() == 1)
                    {  
                     winner=true;
                     gameBoard[i][j].setCellState(6);
                     gameBoard[i+1][j+1].setCellState(6);
                     gameBoard[i+2][j+2].setCellState(6);
                     gameBoard[i+3][j+3].setCellState(6);

                     display();
                     cout << endl <<"Game Over .." << endl;
         cout << "Winner --> User 1 (X)"<<endl;
                     
        }
                     
                }
                
                // DIAGONAL RIGHT TO LEFT
                if(i  < getCurrentHeight()- 3 && j - 3 >= 0 )
                {

                  if(gameBoard[i+1][j-1].getCellState() == 1 && gameBoard[i+2][j-2].getCellState() == 1 && gameBoard[i+3][j-3].getCellState() == 1)
                  {
                     winner=true;
                     gameBoard[i][j].setCellState(6);
                     gameBoard[i+1][j-1].setCellState(6);
                     gameBoard[i+2][j-2].setCellState(6);
                     gameBoard[i+3][j-3].setCellState(6);
                     display();
                     cout << endl <<"Game Over .." << endl;
         cout << "Winner --> User 1 (X)"<<endl;
                     
                  } 
                }                           
            }         
        }             
    } 
     
    
    
 }

// User 2 and Computer game state
// If the four cell is same, user 2 or computer will win the game
void ConnectFour::user2OrComputerWin()
{
    
    for(int i=0; i<getCurrentHeight(); ++i)
    {
        for(int j=0; j<getCurrentWidth(); ++j)
        {
            if(gameBoard[i][j].getCellState() == 2)
            {   
                // UP TO DOWN 
                if(i+3<getCurrentHeight())
                {
                  if(gameBoard[i+1][j].getCellState() == 2 && gameBoard[i+2][j].getCellState() == 2 && gameBoard[i+3][j].getCellState() == 2)  
                  {
                      winner2=true;
                      
                      
                    gameBoard[i][j].setCellState(7);
                    gameBoard[i+1][j].setCellState(7);
                    gameBoard[i+2][j].setCellState(7);
                    gameBoard[i+3][j].setCellState(7);
                      
                      
                      display();
                   if(getGameSelection() == 'P'){
                        cout << endl <<"Game Over .." << endl;
                        cout << "Winner --> User 2 (O)"<<endl;  
                        
                   }
                   if(getGameSelection() == 'C') {
                        cout << endl <<"Game Over .." << endl;
                        cout << "Winner --> Computer (O)" << endl;
                        
                    }
                  }
                }
                // LEFT TO RIGHT
    if(j+ 3 < getCurrentWidth())
                {
                     if(gameBoard[i][j+1].getCellState() == 2 && gameBoard[i][j+2].getCellState() == 2 && gameBoard[i][j+3].getCellState() == 2) 
                     {
                        winner2=true;
                        gameBoard[i][j].setCellState(7);
                        gameBoard[i][j+1].setCellState(7);
                        gameBoard[i][j+2].setCellState(7);
                        gameBoard[i][j+3].setCellState(7);
                        display();
                      
                        if(getGameSelection() == 'P'){
                            cout << endl <<"Game Over .." << endl;
                            cout << "Winner --> User 2 (O)"<<endl;
                            
                         }
                        if(getGameSelection() == 'C') {
                            cout << endl <<"Game Over .." << endl;
                            cout << "Winner --> Computer (O)" << endl;
                            
                         }
                     }
                }
                
                // DIAGONAL LEFT TO RIGHT
                  if(i  < getCurrentHeight()- 3 && j<getCurrentWidth()-3)
                {
                     if(gameBoard[i+1][j+1].getCellState() == 2 && gameBoard[i+2][j+2].getCellState() == 2 && gameBoard[i+3][j+3].getCellState() == 2)
                    {
                        winner2=true;
                        gameBoard[i][j].setCellState(7);
                        gameBoard[i+1][j+1].setCellState(7);
                        gameBoard[i+2][j+2].setCellState(7);
                        gameBoard[i+3][j+3].setCellState(7);
                        display();

                       if(getGameSelection() == 'P'){
                           cout << endl <<"Game Over .." << endl;
                           cout << "Winner --> User 2 (O)"<<endl;
                           
                       }
                       if(getGameSelection() == 'C') {
                           cout << endl <<"Game Over .." << endl;
                           cout << "Winner --> Computer (O)" << endl;
                           
                       }
                    }
                }
                // DIAGONAL RIGHT TO LEFT
                if(i  < getCurrentHeight()- 3 && j - 3 >= 0  )
                {
                  if(gameBoard[i+1][j-1].getCellState() == 2 && gameBoard[i+2][j-2].getCellState() == 2 && gameBoard[i+3][j-3].getCellState() == 2)   
                  {
                       winner2=true;
                       gameBoard[i][j].setCellState(7);
                       gameBoard[i+1][j-1].setCellState(7);
                       gameBoard[i+2][j-2].setCellState(7);
                       gameBoard[i+3][j-3].setCellState(7);
                       display();
                        if(getGameSelection() == 'P')
                        {
                            cout << endl <<"Game Over .." << endl;
                            cout << "Winner --> User 2 (O)"<<endl;                          
                        }
                        if(getGameSelection() == 'C') 
                        {
                            cout << endl <<"Game Over .." << endl;
                            cout << "Winner --> Computer (O)" << endl;  
                        }
                    }                           
                  }         
            }             
        }   
    } 
}
  
// My test function with all objects
// Single mode and multiple mode games
void testFunction()
{
    char gameMode='\0';
    int  objectNumber=0;
    char movement='\0';

    string inputFileName;
   
    while(gameMode !='S' || gameMode!='M')
    {
      cout << endl << "Single Mode Game : S , Multiplayer Game Mode : M"<<endl<<"Select Game Mode : ";
      cin >> gameMode;
      
      if(gameMode=='S' || gameMode=='M')
          break;
    }
        
    if(gameMode=='S')
    {
        cout << endl<< "Enter Game File  : ";
        cin  >> inputFileName;
        ConnectFour singleModeGame1(inputFileName);  
        singleModeGame1.setBoardFileName(inputFileName);    
        singleModeGame1.setGameMode(gameMode);
        singleModeGame1.playGame(); 
    }
    
    
    else if(gameMode=='M') 
    {
        // Create 5 Connect Four Objects
        cout << endl << "Object 1: " << endl;
        cout << endl<< "Enter Game File  : ";
        cin  >> inputFileName;     
        ConnectFour MultipleModeGame1(inputFileName);    
        MultipleModeGame1.multipleModeGameSelection();
        
        cout << endl << "Object 2: " << endl;
        cout << endl<< "Enter Game File  : ";
        cin  >> inputFileName;
        ConnectFour MultipleModeGame2(inputFileName);   
        MultipleModeGame2.multipleModeGameSelection();       
          
        cout << endl << "Object 3: " << endl;
        cout << endl<< "Enter Game File  : ";
        cin  >> inputFileName;
        ConnectFour MultipleModeGame3(inputFileName);      
        MultipleModeGame3.multipleModeGameSelection();
             
        cout << endl << "Object 4: " << endl;
        cout << endl<< "Enter Game File  : ";
        cin  >> inputFileName;
        ConnectFour MultipleModeGame4(inputFileName);      
        MultipleModeGame4.multipleModeGameSelection();
             
        cout << endl << "Object 5: " << endl;
        cout << endl<< "Enter Game File  : ";
        cin  >> inputFileName;
        ConnectFour MultipleModeGame5(inputFileName);      
        MultipleModeGame5.multipleModeGameSelection(); 
       
        
        while(1)
        {
            // Compare object 1 and object 2
            if(MultipleModeGame1 == MultipleModeGame2)
                cout <<endl<<"Object 1 is equal to Object2"<<endl;
            else
                cout <<endl<<"Object 1 is not equal to Object 2"<<endl;
            

            // Select object
            cout << "\nSelect Object : ";
            cin  >> objectNumber;
            cin.ignore(1000, '\n');
            if(cin.eof()) exit (EXIT_SUCCESS);
                       
            while (!cin >> objectNumber) {
                    cout << "\nObject Selection Between 1 And 6 : ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cin  >> objectNumber;
                    if(cin.eof()) exit (EXIT_SUCCESS);
            } 
                         
            switch(objectNumber)
            {
                case 1:
                    if(MultipleModeGame1.getGameSelection()=='C')	// Step by step object 1 operation
                    {                        
                        MultipleModeGame1.display();
                        cout << "Enter Movement P1 : ";           // Get the user1 step
                        cin >> movement;                          
                        if(cin.eof()) exit (EXIT_SUCCESS);        // Check the user input size
                                                                  // If it is end of file, exit the game
                        MultipleModeGame1.play(movement);         // Make user 1 step
                        MultipleModeGame1.play();                 // Make computer step
                        cout<< "Living Cell : "<< ConnectFour::getNumberOfLivingCell()<<endl;
                        break; 
                    }
                    else if(MultipleModeGame1.getGameSelection()=='P') 
                    {   
                        MultipleModeGame1.display();
                        cout << "Enter Movement P1 : ";          // Get the user1 step
                        cin >> movement;
                        if(cin.eof()) exit (EXIT_SUCCESS);
                        
                      	cout << movement<<endl;
                        MultipleModeGame1.play(movement);        // Make the user 1 step             
                        cin.ignore(1000, '\n');                  // Ignore newline characters
                        cin.clear();                     
                     
                        cout << "Enter Movement P2 : ";
                        cin >> movement;                         // Get the user 2 step
                        cin.ignore(1000, '\n');
                        if(cin.eof()) exit (EXIT_SUCCESS);
                        
                        MultipleModeGame1.play(movement);       // Make the user 2 step
                        cout<< "Living Cell : "<< ConnectFour::getNumberOfLivingCell()<<endl;
                        break;   
                    }
               
                case 2:                   
                    if(MultipleModeGame2.getGameSelection()=='C')			// Step by step object 2 operation
                    { 
                        MultipleModeGame2.display();
                        cout << "Enter Movement P1 : ";
                        cin >> movement;
                        cin.ignore(1000, '\n');
                        if(cin.eof()) exit (EXIT_SUCCESS);

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
                        if(cin.eof()) exit (EXIT_SUCCESS);


                        MultipleModeGame2.play(movement);
                        cin.ignore(1000, '\n');
                        cin.clear();

                        cout << "Enter Movement P2 : ";
                        cin >> movement;
                        cin.ignore(1000, '\n');
                        if(cin.eof()) exit (EXIT_SUCCESS);
                        
                        MultipleModeGame2.play(movement); 
                        cout<< "Living Cell : "<< ConnectFour::getNumberOfLivingCell()<<endl;
                        break;   
                    }
                 
                   
                case 3:
                    if(MultipleModeGame3.getGameSelection()=='C')		// Step by step object 3 operation
                    {
                        MultipleModeGame3.display();
                        cout << "Enter Movement P1 : ";
                        cin >> movement;
                        cin.ignore(1000, '\n');
                        if(cin.eof()) exit (EXIT_SUCCESS);

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
                        if(cin.eof()) exit (EXIT_SUCCESS);

                        MultipleModeGame3.play(movement);
                        cin.ignore(1000, '\n');
                        cin.clear();

                        cout << "Enter Movement P2 : ";
                        cin >> movement;
                        cin.ignore(1000, '\n');
                        if(cin.eof()) exit (EXIT_SUCCESS);
                        
                        MultipleModeGame3.play(movement); 
                        cout<< "Living Cell : "<< ConnectFour::getNumberOfLivingCell()<<endl;
                        break;   
                    }
                   
                case 4:
                    if(MultipleModeGame4.getGameSelection()=='C')		// Step by step object 4 operation
                    {    
                        MultipleModeGame4.display();
                        cout << "Enter Movement P1 : ";
                        cin >> movement;
                        cin.ignore(1000, '\n');
                        if(cin.eof()) exit (EXIT_SUCCESS);

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
                        if(cin.eof()) exit (EXIT_SUCCESS);

                        MultipleModeGame4.play(movement);
                        cin.ignore(1000, '\n');
                        cin.clear();

                        cout << "Enter Movement P2 : ";
                        cin >> movement;
                        cin.ignore(1000, '\n');
                        if(cin.eof()) exit (EXIT_SUCCESS);
                        
                        MultipleModeGame4.play(movement); 
                        cout<< "Living Cell : "<< ConnectFour::getNumberOfLivingCell()<<endl;
                        break;   
                    }
                case 5:
                     if(MultipleModeGame5.getGameSelection()=='C')		// Step by step object 5 operation
                    {                      
                        MultipleModeGame5.display();
                        cout << "Enter Movement P1 : ";
                        cin >> movement;
                        cin.ignore(1000, '\n');
                        if(cin.eof()) exit (EXIT_SUCCESS);

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
                     
                        if(cin.eof()) exit (EXIT_SUCCESS);

                        MultipleModeGame5.play(movement);
                        cin.ignore(1000, '\n');
                        cin.clear();

                        cout << "Enter Movement P2 : ";
                        cin >> movement;
                        cin.ignore(1000, '\n');
                        if(cin.eof()) exit (EXIT_SUCCESS);
                        
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
}    
        
        

       
