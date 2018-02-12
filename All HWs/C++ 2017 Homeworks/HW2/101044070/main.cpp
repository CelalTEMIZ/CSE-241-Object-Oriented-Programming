//
// CSE 241 - Object Oriented Programming
//
// CELAL TEMIZ - 101044070
//
// HW02 - Connect Four Game Implementation with LOAD and SAVE commands and files
//

#include <iostream>
#include <fstream>
#include "connectFour.h"

using namespace std;

int main(){


	string loadFileName="";

	cout << endl << "Welcome the Connect Four Game .." << endl;
	cout << "Enter the 'LOAD yourTextFile' command to load the game board."<<endl<<endl;

	getline(cin,loadFileName);

	startGame(loadFileName);

	return 0;
}

