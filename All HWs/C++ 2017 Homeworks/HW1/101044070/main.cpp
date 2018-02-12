//
// CSE 241 - Object Oriented Programming
//
// CELAL TEMIZ - 101044070
//
// HW01 - Connect Four Game Implementation
//



#include <iostream>

#include "connectFour.h"

using namespace std;

int main(int argc, char **argv){

	char choice = '\0';
	int size=0;

	cout << endl << "Welcome the Connect Four Game .." << endl;
	cout << "Board Size Must Be Even Number For 4x4, 6x6, 8x8, ... 20x20 Game Boards !"<<endl;
	cout << "Enter Board Size : ";
	cin  >> size;

	// Ask the user if this is a two players game or user versus computer game

	if(boardSizeCheck(size)){
		cout << endl << "Select the game .." << endl;
		cout << "P > User 1(X) vs   User 2(O)" << endl;
		cout << "C > User  (X) vs Computer(O) >> ";
		cin >> choice;
	}

	switch(choice){

		case 'P':
			twoPlayers(size);
			break;

		case 'C':
			userVersusComputer(size);
			break;

		default:
			cout << "Wrong Input.Exit The Game !" << endl;
	}

	return 0;
}

