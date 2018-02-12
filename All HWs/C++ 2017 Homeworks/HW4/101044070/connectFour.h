#ifndef CONNECTFOUR_H
#define	CONNECTFOUR_H

#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class ConnectFour 
{
    // Private Data Members and Functions to ConnectFour Class
    private:
    		char gameMode;
    		char gameSelection;
    		int  currentWidth;
    		int  currentHeight;
            string boardFileName;

            static int order;
    		static int livingCellAll;
    		static int livingCellUser1;
    		static int livingCellUser2;
            static int livingCellInFile;
            static bool winner,winner2;

            void user1Win();
            void user2OrComputerWin();      // User 2 and Computer game
            void computerSmartMove();       // Smart computer move
            bool gameEnded();               // Check game situation
            int  letterToBoardPosition(char& inputData);    // Convert the characters to board positions
            void printBoardStepRange() const;            // Prompt the user to input range
            void resizeNewBoard(int rowNumber, int columnNumber); // Resize the new board
            void resizeBoard(string gameFile,int& rowNumber,int& columnNumber); // Resize the board and return row and column number
            void readInputFile(string gameFile);  // Read input file 
            string partition(string userInput, int& index); // Parse user input to load and save command   

            static int  getLivingCellInFile(){return livingCellInFile;}  
            static int  getLivingCellUser1(){return  livingCellUser1;}
            static int  getLivingCellUser2(){return  livingCellUser2;}
                

    		class Cell {

    			public:
                    //Constructors to Cell Class
    				Cell();
    				Cell(const char& newCellPosition);
    				Cell(const int& newRowPosition);
    				Cell(const char& newCellPosition,const int& newRowPosition);
                    Cell(const int& newCellState,const char& newCellPosition,const int& newRowPosition);

                    void setAllPosition(const char& newCellPosition,const int& newRowPosition);
    				inline void  setCellPosition(const char& newCellPosition);
    				inline void  setRowPosition(const int& newRowPosition);
                    inline void  setCellState(const int& newCellState);

    				inline char  getCellPosition() const;
    				inline int   getRowPosition() const;
                    inline int   getCellState() const;
                    
                    // Operator overloads
                    bool operator ==(const Cell& other)const; 
                    Cell operator ++(); // Pre-increment
                    Cell operator ++(int ignoreMe); // Post-increment
                    Cell operator --(); // Pre-decrement
                    Cell operator --(int ignoreMe); // Post Decrement
                    //Stream insertion and extraction operators for cell.
                    friend std::ostream& operator <<(std::ostream& outputStream, Cell const& cellObject);
                    friend std::istream& operator >>(std::istream& inputStream, Cell& cellObject);
                                     
                                        

    			private:
    				char cellPosition;
    				int  rowPosition;
                    int  cellState ; 
                    // CellState
                    // User1(X)=1,User2(O)=2,Computer(O)=3,Empty( )=4,Asteriks(*)=5
                    // Little User1(x)=6
                    // Little User2(o)=7

    		};
                  // Global operator overloads
                 friend std::ostream& operator <<(std::ostream& outputStream, ConnectFour::Cell const& cellObject);
                 friend std::istream& operator >>(std::istream& inputStream, ConnectFour::Cell & cellObject);
                

                 Cell **gameBoard;

    // Public Members and Functions to ConnectFour Class
	public:

	    // Constructors to ConnectFour Class

        ConnectFour();// No parameter constructor
        ConnectFour(int newCurrentHeight,int newCurrentWidth); //Contructor takes number of rows and columns as parameters
        ConnectFour(string inputFile); // Constructor takes a text file as a parameter
     
    	ConnectFour(int newCurrentWidth,char newgameMode,char newgameSelection);
    	ConnectFour(int newCurrentWidth,int newCurrentHeight,char newgameMode, char newgameSelection);

        // The Big Three
        ConnectFour(const ConnectFour& newConnectFourObject); // Copy Constructor
        ConnectFour& operator =(const ConnectFour& rightSide); // Assignment Operator
        ~ConnectFour(); //Destructor
        
        // Operator oveloads
        bool operator ==(ConnectFour& other)const;
        bool operator !=(ConnectFour& other)const;

        // Setters - Mutator Functions
    	inline void setCurrentWidth(const int& newCurrentWidth);
    	inline void setCurrentHeight(const int& newCurrentHeight);
    	inline void setGameSelection(const char& newGameSelection);
        void setGameMode(const char& newGameMode);
        void setBoardFileName(string newBoardFileName);
         
        // Getters - Accessor Functions
    	inline int  getCurrentWidth() const ;
    	inline int  getCurrentHeight() const;
        inline char getGameMode() const;
        char        getGameSelection() const;
        inline string getBoardFileName() const;

        // Other functions
        void playGame(); // Single mode game
        void play();     // Multiple mode game to computer
        void play(char& cellPosition);   // Multiple mode game to user
        void load(string  inputFileName);                     // Load the new game 
        void save(string outputFileName, char* userInputs, int& numberOfUserInputs); // Save the current game          
        void display() const;                              // Display the board during the whole game
        void multipleModeGameSelection();  // Get multiple mode game selection
        bool movement(int yPosition);   // Put the steps to board
        bool isLivingUser1Cells(ConnectFour::Cell cell); 
        bool isLivingUser2Cells(ConnectFour::Cell cell);
        static int  getNumberOfLivingCell() {return livingCellAll;}     
        static bool getWinner() {return winner;}
        static bool getWinner2() {return winner2;}
	
};


// My Test Function
void testFunction();


#endif	/* CONNECTFOUR_H */

