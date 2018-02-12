/* 
 * File:   Reversi.h
 * Author: celal
 *
 * Created on November 21, 2015, 10:34 PM
 */

#ifndef REVERSI_H
#define	REVERSI_H

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>

#include "Cell.h"

using namespace std;

#define GAME_BOARD_SIZE 6


class Reversi
{
    public:
    
  
        Reversi();
        Reversi(int xCoordinate);
        Reversi(int xCoordinate, int yCoordinate);
         
          
        const int getXPosition() const {return x;}
        const int getYPosition() const {return y;}
     
        
        void setXGame(int newXGame) {x = newXGame;}
        void setYGame(int newYGame) {y = newYGame;}
        void showGameBoard(char gameBoard[][GAME_BOARD_SIZE]);
        
        
        void initialAllGameBoard(char gameBoard[][GAME_BOARD_SIZE],int boardRow,int boardColumn);

        
        int  readFile(FILE* inp);
        int  heightBoard(FILE* inp);
        int  widthBoard(char gameBoard[][GAME_BOARD_SIZE],FILE* inp);
        void writeFile(FILE* outp,char gameBoard[][GAME_BOARD_SIZE],int board_row, int board_column);
        void userStep(char gameBoard[][GAME_BOARD_SIZE],char userOrComputer,int boardRow,int boardColumn);
        void computerStep(char gameBoard[][GAME_BOARD_SIZE],char userOrComputer,int step[][GAME_BOARD_SIZE]);       
        int  status(char gameBoard[][GAME_BOARD_SIZE], char userOrComputer, int step[][GAME_BOARD_SIZE]);
        
    private:   
        vector< vector<Cell> > gameCells;
        int x;
        char y;

   
    
};


#endif	/* REVERSI_H */

