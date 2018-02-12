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
        private:
		char gameMode;
		char gameSelection;
		int  currentWidth;
		int  currentHeight;
                
                static int order;
		static int livingCellAll;
		static int livingCellUser1;
		static int livingCellUser2;
                static int livingCellInFile;
                static bool winner,winner2;
                

		class Cell {
			public:
				Cell();
				Cell(const char& newCellPosition);
				Cell(const int& newRowPosition);
				Cell(const char& newCellPosition,const int& newRowPosition);

				inline void setCellPosition(const char& newCellPosition);
				inline void setRowPosition(const int& newRowPosition);
                                void setAllPosition(const char& newCellPosition,const int& newRowPosition);
				inline char getCellPosition() const;
				inline int  getRowPosition() const;

			private:
				char cellPosition;
				int  rowPosition;

		};
                
                
                vector< vector<Cell> > gameCells;


	public:

	ConnectFour();
	ConnectFour(const int& newCurrentWidth, const char& newgameMode, const char& newgameSelection);
	ConnectFour(const int& newCurrentWidth,const int& newCurrentHeight,const char& newgameMode, const char& newgameSelection);


	inline void setCurrentWidth(const int& newCurrentWidth);
	inline void setCurrentHeight(const int& newCurrentHeight);
        inline void setGameMode(const char& newGameMode);
	inline void setGameSelection(const char& newGameSelection);
        
	inline int  getCurrentWidth() const ;
	inline int  getCurrentHeight() const;
        inline char getGameMode() const;
        char getGameSelection() const;

        
	void read(string  inputFileName);
	void write(string outputFileName);
	void display();
        void printBoardStepRange();
        string partition(string userInput, int& index);

        void getData();      	
	bool gameEnded();    
	void playGame();
        void play();
        void play(char& cellPosition);

        bool isLivingUser1Cells(ConnectFour::Cell cell);
        bool isLivingUser2Cells(ConnectFour::Cell cell);

	static int getLivingCellUser1(){return livingCellUser1;}
	static int getLivingCellUser2(){return livingCellUser2;}

	bool compareConnectFourGame(const ConnectFour& other);
        void movement(int yPosition);
        void user1Win();
        void user2OrComputerWin();
        
        static int  getNumberOfLivingCell();
        static bool getWinner() {return winner;}
        static bool getWinner2() {return winner2;}

	
};



#endif	/* CONNECTFOUR_H */

