/*******************************************************************/
/*	Object Oriented Programming							           */
/*	Fall 2014									                   */
/*	Homework # 4									               */
/*  															   */
/*  CELAL TEMİZ                                                    */
/* 	101044070											           */
/*																   */
/*******************************************************************/


#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>

using namespace std;

/* The Cell class hold the X and Y positions of the cell */

class Cell
{

    public:
    
        /* Constructors default and two parameters */
        Cell();
        Cell(int xPosition);
        Cell(int xPosition, int yPosition);
        
    
        /* Setter function */
        void setX(int newX) {xPos = newX;}
        void setY(int newY) {yPos = newY;}
       
        /* Getter functions */
        int getXposition() const {return xPos;}
        int getYposition() const {return yPos;}
          
 
    private:
    
        /* Cell position on x and y coordinates */
        int xPos;
        int yPos;  


};


/* The class GameOfLife hold a vector of Cell objects to represent the living cells */
class GameOfLife
{

    public:
    
        /* Constructors */
        GameOfLife();
        GameOfLife(int xCoordinate, int yCoordinate);
         
        /* Getters */   
        int getXCoordinate() const {return x;}
        int getYCoordinate() const {return y;}
     
        /* Setters */
        void setXGame(int newXGame) {x = newXGame;}
        void setYGame(int newYGame) {y = newYGame;}
        
        /* Member Functions */
        int  readFile(FILE* inp);
        int  heightBoard(FILE* inp);
        int  widthBoard(int numOfCell, int lineNumber);
        void writeFile(FILE *inp, FILE* outp, int board_row, int board_column);
        
    
    private:
   
        vector<Cell>livingCells;
        int x;
        int y;


};


int main()
{

    /* Variables */

    char initialize_fileName[20];
	char final_fileName[20];
    int height,board_column,board_row;
    
    
    /* Test Objects */
    GameOfLife readObject;
    
    Cell testObject(1);

	/* File Pointer */

	FILE *inp;
	FILE *outp;


	/* Get the name of initialize file and final file from the user */

	cout << "Enter your initialize board file name" << endl;
	cin >> initialize_fileName;
	cout << "Enter your final board file name" << endl;
	cin >> final_fileName;

	/* Open file */

	inp = fopen(initialize_fileName, "r");	
	outp = fopen(final_fileName, "w");
	


    /* Row Number */
     cout << "\nTest GameOfLife Objects to height board : ";
    cout <<readObject.heightBoard(inp)<< endl;
       
       
    /* Column Number */
    cout << "Test GameOfLife Objects to width board : ";
    board_column = readObject.widthBoard(readObject.readFile(inp), readObject.heightBoard(inp));
   
    cout << readObject.widthBoard(readObject.readFile(inp), readObject.heightBoard(inp));
    
   
    board_row = readObject.heightBoard(inp);
    readObject.writeFile(inp, outp, board_row, board_column);
    
    
    cout << "\nTest Cell Object to getXPosition : ";
    cout << testObject.getXposition() << endl << endl;
    
    
    return 0;
}

/* No parameter Constructor */
Cell::Cell()
{
    xPos=0;
    yPos=0;
}

/* One parameter constructor to xPosition */
Cell::Cell(int xPosition)
{

    xPos = xPosition;
   
}

/* Consruct to cell x and y coordinates */
Cell::Cell(int xPosition,int yPosition)
{
    xPos = xPosition;
    yPos = yPosition;
}

/* No parameter Constructor */
GameOfLife::GameOfLife()
{
    x=0;
    y=0;
}
/* Constructor to GameOfLife x and y coordinate */
GameOfLife::GameOfLife(int xCoordinate, int yCoordinate)
{

    x = xCoordinate;
    y = yCoordinate;
}

/* Read to input file */
int GameOfLife::readFile(FILE* inp)
{

    char ch;
    int status,counter=0;
    
    status = fscanf(inp, "%c", &ch );
    
    while(status != EOF ) {

        if(ch != '\n')
        
            counter++;                
            status = fscanf(inp, "%c", &ch );
        

    }
    
    /* Rewind to return output file again the first element */
    rewind(inp);
    
    return counter;
    
}
/* Write to final board to output file */
void GameOfLife::writeFile(FILE* inp, FILE* outp, int board_row, int board_column)
{

    char ch;
    int status,counter=0,i,j;
    
    /* Vector to board members */
    vector<char>v1;
    
    status = fscanf(inp, "%c", &ch );
    
    while(status != EOF ) {

        if(ch != '\n'){   
        counter++;  
        v1.push_back(ch);
        }            
        status = fscanf(inp, "%c", &ch );
    

    }

    
   
    
    int m=0;
    
    /* Display the board member on output file */
    
    for(int k=0; k<board_row; ++k){ 
    
        for(j=0; j<board_column; ++j) {
        
                fprintf(outp, "%c ", v1[m]);
                m++;
                }
                fprintf(outp,"\n");
                }
                
                       
          
}
/* Calculate the board witdh */
int  GameOfLife::widthBoard(int numOfCell, int lineNumber)
{

    return (numOfCell / lineNumber);

}

/* Calculate the board height or board row */
int GameOfLife::heightBoard(FILE* inp)
{
    
    char line;
    int status,counter=0;
    
    status = fscanf(inp, "%c", &line );
    
    while(status != EOF ) {

        if(line == '\n')
        
        counter++;
        status = fscanf(inp, "%c", &line );
    
    }
    
    /* Rewind to return output file again the first element */
    
    rewind(inp);
    
    return counter;  


}







