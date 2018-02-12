#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <fstream>
#include <string>


#include "connectFour.h"

using namespace std;

int ConnectFour::livingCellAll=0;
int ConnectFour::livingCellUser1=0;
int ConnectFour::livingCellUser2=0;
int ConnectFour::livingCellInFile=0;
int ConnectFour::order=0;
bool ConnectFour::winner=false;
bool ConnectFour::winner2=false;


ConnectFour::ConnectFour():currentWidth(4),currentHeight(4),gameSelection('P'),gameMode('S')
{
    gameCells.resize(currentHeight*currentWidth);
    gameCells[0].resize(currentWidth*currentHeight);
    gameCells[1].resize(currentWidth*currentHeight);
}

ConnectFour::ConnectFour(const int& newCurrentWidth, const char& newgameMode, const char& newgameSelection)
{
    currentHeight = 4;
    setCurrentWidth(newCurrentWidth);
    setGameMode(newgameMode);
    setGameSelection(newgameSelection);
    gameCells.resize(currentHeight*currentWidth);
    gameCells[0].resize(currentWidth*currentHeight);
    gameCells[1].resize(currentWidth*currentHeight);
}


ConnectFour::ConnectFour(const int& newCurrentWidth,const int& newCurrentHeight,const char& newgameMode, const char& newgameSelection)
{

    setCurrentWidth(newCurrentWidth);
    setCurrentHeight(newCurrentHeight);
    setGameMode(newgameMode);
    setGameSelection(newgameSelection);
   
    gameCells.resize(currentHeight);
    gameCells[0].resize(currentWidth);
    gameCells[1].resize(currentWidth);
}

inline void ConnectFour::setCurrentWidth(const int& newCurrentWidth)
{
    if(newCurrentWidth< 4 || newCurrentWidth>=30 )
    {
            cerr <<endl << "Invalid Game Board Width !!" << endl;
            exit(1);
    }
    else
    {
            currentWidth = newCurrentWidth;
    }
}
inline void ConnectFour::setCurrentHeight(const int& newCurrentHeight)
{
    if(newCurrentHeight < 4){
            cerr << endl << "Invalid Game Board Height !!" << endl;
            exit(1);
    }
    else 
    {
            currentHeight = newCurrentHeight;
    }
}

 inline void ConnectFour::setGameMode(const char& newGameMode)
 {   
     if(newGameMode =='S' || newGameMode == 'M') 
     {
         gameMode = newGameMode;
     }else
     {
         cerr << endl << "Game Mode must be S or M " << endl;
         exit(1);
     }
 }
 
 
  inline void ConnectFour::setGameSelection(const char& newGameSelection)
 {
     if(newGameSelection =='P' || newGameSelection == 'C') 
     {
         gameSelection= newGameSelection;
     }else
     {
         cerr << endl << "Game Mode must be P or C " << endl;
         exit(1);
     }     
 }


inline char ConnectFour::getGameMode() const 
{
    return gameMode;   
}
 
char ConnectFour::getGameSelection() const 
{
    return gameSelection;   
}
  
  
inline int ConnectFour::getCurrentWidth() const 
{
    return currentWidth;  
}

inline int ConnectFour::getCurrentHeight() const
{
    return currentHeight;
}

void ConnectFour::read(string  inputFileName)
{
        
  ifstream fin;
  int  flagGameSelection=1;

 fin.open(inputFileName,ios::in | ios::binary);
 

    if(fin.fail()){
            cerr << "Input file opening failed" << endl;
            exit(1);
    }
     

    char nextInputChar;
    
    while(flagGameSelection==1){
                    fin.get(nextInputChar);
                    if(nextInputChar == 'S' || nextInputChar == 'M'){
                          setGameMode(nextInputChar);
                            flagGameSelection=0;
                    }
            }

    int width,height;
    
    fin >> width >> height;
    
    setCurrentWidth(width);
    setCurrentHeight(height);
     
    
    //char nextInputChar;
    flagGameSelection=1;
    while(flagGameSelection==1){
                    fin.get(nextInputChar);
                    if(nextInputChar == 'P' || nextInputChar == 'C'){
                          setGameSelection(nextInputChar);
                            flagGameSelection=0;
                    }
    }
    
 
    int  i=0,availableInputNumber=0;

    int gameSelectionCounter=0;
    char letter = 'A';

    char ch[getCurrentWidth()];
    int count=0;
    
    int widthArray[getCurrentWidth()];
    
    for(int i=0; i<getCurrentWidth(); ++i)
        widthArray[i] = getCurrentHeight()-1;
    
  
    fin.get(nextInputChar);
    int flag=0,lastVal=0;

    while(!fin.eof()) {
	
		// Check available characters in text file
        if(nextInputChar != '\n' && nextInputChar !='\0' && nextInputChar >='A' && nextInputChar<='Z'){
                                                                        
            // Second character and others will load game board
            if(nextInputChar >='A' && nextInputChar<(letter+getCurrentWidth()))
            {             

                for( int k=0;k<=count;k++)
                {                              
                    if(ch[k] != nextInputChar)
                    {
                        flag=0;
                    }
                    else
                    {
                        flag=1;
                        lastVal=k;
                        break;
                    }
                }

                 if(flag==0)
                 {
                        ch[count] = nextInputChar;

                        if(i%2==0)
                        {
                            gameCells[0][livingCellUser1].setCellPosition(ch[count]);
                            gameCells[0][livingCellUser1].setRowPosition(widthArray[count]--);

                            livingCellUser1++;
                            ++livingCellInFile; 
                        }
                        else
                        {
                            gameCells[1][livingCellUser2].setCellPosition(ch[count]);
                            gameCells[1][livingCellUser2].setRowPosition(widthArray[count]--);
                            livingCellUser2++;
                            ++livingCellInFile; 
                        }   
                        count++;
                 }

                 else
                 {
                         if(i%2==0)
                         {
                            gameCells[0][livingCellUser1].setCellPosition(ch[lastVal]);
                            gameCells[0][livingCellUser1].setRowPosition(widthArray[lastVal]--);

                            livingCellUser1++;
                            ++livingCellInFile;
                         }
                        else
                        {
                           gameCells[1][livingCellUser2].setCellPosition(ch[lastVal]);
                            gameCells[1][livingCellUser2].setRowPosition(widthArray[lastVal]--);
                            livingCellUser2++;
                            ++livingCellInFile;
                        }
                 }
               ++i;          
            }
        }

    fin.get(nextInputChar);
    }
    
    fin.close();   
}
void  ConnectFour::display()
{
    
    char boardCharacter = 'A';  
        for(int i = 0; i<getCurrentWidth(); i++)
            cout << " " <<static_cast<char>(boardCharacter + i) ;
    
        cout << "\n";
    
  for(int j=0;j<getCurrentHeight();j++)
  {   
   for(int i=0;i<getCurrentWidth();i++)
   {

        if(isLivingUser1Cells(ConnectFour::Cell(i+'A',j)))
        {
            if(!winner)
                cout<<" X";
            else
                cout<<" x";
        }
        else if(isLivingUser2Cells(ConnectFour::Cell(i+'A',j)))
        {
            if(!winner2)
                cout<<" O";
            else
                cout<<" o";    
        }
        else if(!isLivingUser1Cells(ConnectFour::Cell(i+'A',j))&&!isLivingUser2Cells(ConnectFour::Cell(i+'A',j)))
        {
            cout<<" .";
        }
                        
    }
        cout<<"\n";
        
   }
  
}

void ConnectFour::printBoardStepRange()
{
    char boardCharacter = 'A';  
    for(int i = 0; i<getCurrentWidth(); i++)
       cout << static_cast<char>(boardCharacter + i) << "." ;  
}

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

bool ConnectFour::isLivingUser1Cells(ConnectFour::Cell cell)
{
    for(int i=0;i<livingCellUser1;i++)
    {   
        if(gameCells[0][i].getCellPosition()==cell.getCellPosition()&& gameCells[0][i].getRowPosition()==cell.getRowPosition())
        {
            return true;
        }
    }
    
    return false;
}
bool ConnectFour::isLivingUser2Cells(ConnectFour::Cell cell)
{
    for(int i=0;i<livingCellUser2;i++)
    {
        if(gameCells[1][i].getCellPosition()==cell.getCellPosition()&& gameCells[1][i].getRowPosition()==cell.getRowPosition())
        {
            return true;
        }
    }
    
    return false;
}

void ConnectFour::getData()
{  
    char playerOrComputer='\0';
    int width=0,height=0;

    cout << endl << "Enter Board Width : ";
    cin >> width;
    
    setCurrentWidth(width);

    cout << endl << "Enter Board Height: ";
    cin >> height;
    
    setCurrentHeight(height);

    cout <<endl << "Player(P) | Computer(C): ";
    cin >> playerOrComputer;
    
    setGameSelection(playerOrComputer);
    
}
void ConnectFour::movement(int yPosition)
{   	
        for(int i=getCurrentHeight()-1; i>=0; --i)
        {
		if( !isLivingUser1Cells(Cell(yPosition+'A',i)) && !isLivingUser2Cells(Cell(yPosition+'A',i)))
                {                      
                     if(order==0)
                     {
			gameCells[0][livingCellUser1].setCellPosition(yPosition+'A');                     
                        gameCells[0][livingCellUser1].setRowPosition(i);
			break;
                     }
                     else
                     {  
                        gameCells[1][livingCellUser2].setCellPosition(yPosition+'A');  
                        gameCells[1][livingCellUser2].setRowPosition(i);
			break; 
                     }
                     
		}                   
        }        
}

void ConnectFour::play(char& cellPosition)
{
    
  char letter = 'A';	
  int  intValue=0; 

  if(getGameSelection()=='P' )
  {
    gameCells[0].resize(currentWidth*currentHeight);
    gameCells[1].resize(currentWidth*currentHeight); 
  }
  
  if(getGameSelection()=='C')
  {
    gameCells[0].resize(currentWidth*currentHeight);  
  }
 
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
  
  
  if(!isLivingUser1Cells(Cell(cellPosition,0)) && !isLivingUser2Cells(Cell(cellPosition,0)) && winner==false )
  {      
      if (order==0)
      {
            for(intValue=0,letter='A'; letter<='Z'; ++letter, ++intValue) 
            {
                if(letter == cellPosition)
                {
                  movement(intValue);
                  ++livingCellUser1;
                  ++livingCellAll;
                  display();
                  user1Win(); 
                  order=1;
                  if(gameEnded())
                       cout<<endl<<endl<<"Board Filled !"<<endl<<endl;
                  return ; 
                }
            }  
      } 
      
      if(order==1 && getGameSelection()=='P') {
          for(intValue=0,letter='A'; letter<='Z'; ++letter, ++intValue) 
            {
                if(letter == cellPosition)
                {              
                  order=1;
                  movement(intValue);
                  ++livingCellUser2;
                  ++livingCellAll;
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

void ConnectFour::play()
{
     
    gameCells[1].resize(currentWidth*currentHeight);
          
    //display();                  
    // Computer
    srand (time(NULL));   
    int computerStep = (rand() % getCurrentWidth());

    if(!isLivingUser1Cells(Cell(computerStep+'A',0)) && !isLivingUser2Cells(Cell(computerStep+'A',0)) && winner2==false && winner==false)
    {
        order=1;
        movement(computerStep);
        ++livingCellUser2;
        ++livingCellAll;
        cout << endl << "Computer Step : " << static_cast<char>(computerStep+'A') << endl << endl;
        display();
        user2OrComputerWin(); 
        order=0;
        
        if(gameEnded())
            cout<<endl<<endl<<"Board Filled !"<<endl<<endl;
        
        return ;
    }
     
    // Smart Computer Step
    
    if(winner==false && winner2==false && (isLivingUser1Cells(Cell(static_cast<char>(computerStep+'A'),0)) || isLivingUser2Cells(Cell(static_cast<char>(computerStep+'A'),0))))
    {             
        bool flag = false;
	char letter='A';
	int i=0,j=0;
	char computerStep='\0';

	for(i=getCurrentHeight()-1; i>=0; --i)
        {
            for(j=0; j<=getCurrentWidth()-1; ++j)
            {  
                if(!isLivingUser1Cells(Cell(computerStep+'A'+j,i)) && !isLivingUser2Cells(Cell(computerStep+'A'+j,i)))
                {
                    order=1;                   
                    gameCells[1][livingCellUser2].setCellPosition(computerStep+j+'A');  
                    gameCells[1][livingCellUser2].setRowPosition(i);
                    ++livingCellUser2;
                    ++livingCellAll;
                    cout << endl << "Computer Step : " << static_cast<char>(computerStep+'A'+j) << endl << endl;
                    display();
                    user2OrComputerWin(); 
                    if(gameEnded()) cout<<endl<<endl<<"Board Filled !"<<endl<<endl;

                    return ;  
                } 
            }            
        }
    }	                  
}

// Game Compare Function
// If any game has much living cells on board, it will has best situation from other game 
bool ConnectFour::compareConnectFourGame(const ConnectFour& other)
{
  int user1 = 0;
  int user2 = 0;
  int computer = 0;

  // User vs User
  for (int i = 0; i < gameCells.size(); ++i) 
  {
    for (int j = 0; j < gameCells[i].size(); ++j) 
    {
      if (gameCells[i][j].getCellPosition() == 'X')
        ++user1;
      else 
        ++user2;
    }
  }
  
  // User vs Computer
  for (int i = 0; i < other.gameCells.size(); ++i) 
  {
    for (int j = 0; j < other.gameCells[i].size(); ++j)
    {
      if (other.gameCells[i][j].getCellPosition() == 'X')
        ++user1;
      else 
        ++computer;
    }
  }
 
  return (user1-computer) > (user2-computer);
    
}
void ConnectFour::write(string outputFileName)
{
    
    ofstream fout;

    fout.open(outputFileName);

    if(fout.fail()) {
            cerr << "Input file opening failed" << endl;
            exit(1);
    }
    
    fout  << getGameMode() << endl;
    fout  << getCurrentWidth() << endl;
    fout  << getCurrentHeight() << endl;
   
    if(getGameSelection()=='P')
            fout << 'P'<<endl;
    else 
            fout <<'C'<< endl;
    
    int i=0,j=0;    
 
    // Inputs
    while(1){
       
        fout << gameCells[0][i].getCellPosition()<<endl; 
        if(i==livingCellUser1-1){
            ++i;
            fout << gameCells[0][i].getCellPosition()<<endl;    
        }        
       
        fout << gameCells[1][j].getCellPosition()<<endl;
        
        if(j==livingCellUser2-1) break;
        
        ++i; 
        ++j;
   
    }
 
    fout.close();  

    cout << endl << "> The current game status is written to "<< outputFileName << " file." <<endl<<endl;     
}

void ConnectFour::playGame()
{
 
    int lastPosition=0;
   
    string step="";

    string alphabetOrder = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
           
    getData();
    
    gameCells[0].resize(currentWidth*currentHeight);
    gameCells[1].resize(currentWidth*currentHeight);
    
    cin.ignore(1000, '\n');
      
    while(winner==false && winner2==false)
    {      
        display();
        
        cout<<endl<<"LivingCell: "<<ConnectFour::getNumberOfLivingCell()<<endl;
        
        cout << endl << "> Enter the 'LOAD yourTextFile' command to load the new game." << endl;
	cout << "> Enter the 'SAVE yourTextFile' command to save the current game." << endl;
        cout << "> Continue the game use positions such as ";
        
        printBoardStepRange();
        cout << endl << endl << "Your Movement (X): ";
           
        getline(cin,step);  
        
        string command="", outFile="";
	lastPosition=0;
	command = partition(step,lastPosition);
        
        if(command == "SAVE") 
        {
            outFile = partition(step,lastPosition);
            write(outFile);
        }
        if(command == "LOAD")
        {  
            string newInputFile = partition(step,lastPosition);
            read(newInputFile);
            //display();
            livingCellAll = livingCellInFile+livingCellAll;        
        }
        else 
        {
              for(int i=0; i<26; ++i)
              {
                 if(alphabetOrder[i] == command[0])
                 {  
                    if(i<getCurrentWidth()&&!isLivingUser1Cells(Cell(i+'A',0))&&!isLivingUser2Cells(Cell(i+'A',0)))
                    {   
                        if(order==0)   // Player 1
                        { 
                         movement(i);
                         ++livingCellUser1;
                         ++livingCellAll;
                         user1Win(); 

                            if(getGameSelection()=='P')
                            {
                                order=1;  // Player 2   
                            }
                            if(getGameSelection()=='C') 
                            { 
                                int computerStep= (rand() % getCurrentWidth());
                                order=1;
                                movement(computerStep);
                                cout << endl << "Computer Movement (O) : " << static_cast<char>(computerStep+'A') << endl << endl;
                                order=0;
                                ++livingCellUser2;
                                ++livingCellAll;                               
                                user2OrComputerWin(); 
                                break;
                            }
                         
                         break;
                        }
                        
                        else if(order == 1 && getGameSelection() !='C')
                        {  
                         movement(i);
                         order=0;
                         ++livingCellUser2;
                         ++livingCellAll;
                         user2OrComputerWin();
                         break;
                        }
                    }

                    else 
                    {
                        if(i > getCurrentWidth()-1 && command !="SAVE" && command !="LOAD")
                        {
                                cerr << endl << "> Wrong character or Incomplete command.Invalid Step !" << endl;   
                        }
                        if(isLivingUser1Cells(Cell(command[0],0))||isLivingUser2Cells(Cell(command[0],0)) &&i<getCurrentHeight())
                        {
                                cerr << endl << "> Column is full.Invalid Step !" << endl;
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

int ConnectFour::getNumberOfLivingCell()
{
    return livingCellAll;
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
}

ConnectFour::Cell::Cell(const char& newCellPosition)
{
   cellPosition = newCellPosition;
   rowPosition = 0;
}
ConnectFour::Cell::Cell(const int& newRowPosition)
{
   cellPosition = ' ';
   rowPosition = newRowPosition;
}

ConnectFour::Cell::Cell(const char& newCellPosition, const int& newRowPosition)
{
    cellPosition = newCellPosition;
    rowPosition =  newRowPosition;  
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

void ConnectFour::user1Win()
{
    
    for(int i=0;i<=getCurrentHeight()-1;i++)
    {
        for(int j=0;j<=getCurrentWidth()-1;j++)
        {
            if(isLivingUser1Cells(Cell(i+'A',j)))
            {       
                // UP TO DOWN 
                if(j+3<getCurrentHeight())
                {
                   
                  if(isLivingUser1Cells(Cell(i+'A',j+1))&&isLivingUser1Cells(Cell(i+'A',j+2))&&isLivingUser1Cells(Cell(i+'A',j+3)))   
                  {
                      winner=true;
                      display();
                      cout << endl <<"Game Over .." << endl;
		      cout << "Winner --> User 1 (X)"<<endl;
		  }
                }
                // LEFT TO RIGHT
		if(i + 3 <getCurrentWidth())
                {	
                    if(isLivingUser1Cells(Cell(i+1+'A',j))&&isLivingUser1Cells(Cell(i+2+'A',j))&&isLivingUser1Cells(Cell(i+3+'A',j)))   
                    {
                     winner=true;
                     display();
                     cout << endl <<"Game Over .." << endl;
		     cout << "Winner --> User 1 (X)"<<endl;
                    }
                }
                
                // DIAGONAL LEFT TO RIGHT
                if(i + 3 < getCurrentWidth())
                {
                    if(isLivingUser1Cells(Cell(i+1+'A',j+1))&&isLivingUser1Cells(Cell(i+2+'A',j+2))&&isLivingUser1Cells(Cell(i+3+'A',j+3)))   
                    {
                     winner=true;
                     display();
                     cout << endl <<"Game Over .." << endl;
		     cout << "Winner --> User 1 (X)"<<endl;
		    }
                }
                
                // DIAGONAL RIGHT TO LEFT
                if(i - 3 >= 0 )
                {
                  if(isLivingUser1Cells(Cell(i-1+'A',j+1))&&isLivingUser1Cells(Cell(i-2+'A',j+2))&&isLivingUser1Cells(Cell(i-3+'A',j+3)))   
                  {
                     winner=true;
                     display();
                     cout << endl <<"Game Over .." << endl;
		     cout << "Winner --> User 1 (X)"<<endl;
                  } 
                }                       		
            }					
        }             
    } 
 }

void ConnectFour::user2OrComputerWin()
{
   
    for(int i=0; i<=getCurrentWidth()-1;i++)
    {
        for(int j=0; j<=getCurrentHeight()-1;j++)
        {
            if(isLivingUser2Cells(Cell(i+'A',j)))
            {   
                // UP TO DOWN 
                if(j+3<getCurrentHeight())
                {
                   if(isLivingUser2Cells(Cell(i+'A',j+1))&&isLivingUser2Cells(Cell(i+'A',j+2))&&isLivingUser2Cells(Cell(i+'A',j+3))) 
                  {
                      winner2=true;
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
		if(i+ 3 < getCurrentWidth())
                {
                     if(isLivingUser2Cells(Cell(i+1+'A',j))&&isLivingUser2Cells(Cell(i+2+'A',j))&&isLivingUser2Cells(Cell(i+3+'A',j))) 
                     {
                        winner2=true;
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
                if(i+ 3 < getCurrentWidth())
                {
                    if(isLivingUser2Cells(Cell(i+1+'A',j+1))&&isLivingUser2Cells(Cell(i+2+'A',j+2))&&isLivingUser2Cells(Cell(i+3+'A',j+3)))
                    {
                        winner2=true;
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
                if(i - 3 >= 0 )
                {
                  if(isLivingUser2Cells(Cell(i-1+'A',j+1))&&isLivingUser2Cells(Cell(i-2+'A',j+2))&&isLivingUser2Cells(Cell(i-3+'A',j+3)))   
                  {
                       winner2=true;
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
        
        
        

       