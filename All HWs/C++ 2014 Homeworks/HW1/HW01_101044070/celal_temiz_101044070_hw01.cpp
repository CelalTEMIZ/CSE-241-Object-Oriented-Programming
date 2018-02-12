/*******************************************************************/
/*	Object Oriented Programming							           */
/*	Fall 2014									                   */
/*	Homework # 1									               */
/*  															   */
/*	                                                               */
/*  CELAL TEMİZ                                                    */
/* 	101044070											           */
/*																   */
/*	                                                               */
/* A C++ program that will simulate the game of life.The game of   */
/* life is played by a computer with no other players. The game is */ 
/* on a two dimentional board (2D array) with rectangular cells.   */
/* Each cell is either dead or alive.For each time step, the game  */
/* decides which cells will be dead or alive for the next time step*/
/*																   */
/*******************************************************************/


/* Include library */

#include<iostream>
#include<cstdio>
#include<cstdlib>


using namespace std;



int main()
{

	/* Number of board row, column number, step , live cell */

	int board_row,board_column,
	    status,step_number,live_cell=0;


	/* Two dimentional array for game board and updated game board	*/

	int **game_board;
	
	int **copy_board;


	int i, j, N=0;


	/* File names */

	char ch;
	char initialize_fileName[20];
	char final_fileName[20];


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
		


	/* Read number of row and column from the initialize file */

	fscanf(inp, "%d %d", &board_row, &board_column);

	/* Check the validity of the user input */

	if (board_row != 0 && board_column != 0) {
		
	
		/* Game board and updated board are created */

		game_board = (int**)malloc(sizeof(int*) * board_row);

		for(i=0; i<board_row; ++i)
		
			game_board[i] = (int*)malloc(sizeof(int) *board_column);

	

		copy_board = (int**)malloc(sizeof(int*) * board_row);

			for(i=0; i<board_row; ++i)
			
				copy_board[i] = (int*)malloc(sizeof(int) *board_column);



		/* Operation of file.Convert the character to integer symbol */

			for(i=0; i<board_row; ++i) {
				for(j=0; j<board_column; ++j) {

					fscanf(inp, " %c", &ch );

						if(ch == '0')					
							game_board[i][j] = 0;

						else
							game_board[i][j] = 1;				
				}
			}
		

		/* Prompt the user for number of step */

		cout << "Enter the number of time steps N " << endl;		
		cin >> N;

		cout << "--Initial Board-- \n\n";

		for(i=0; i<board_row; ++i) {
						for(j=0; j<board_column; ++j) {

							cout << game_board[i][j] << "  ";
						}
						cout <<"\n";
					}


	


			while(N > 0) {

				cout << "---------------\n";

				for(i=0; i<board_row; ++i){

					for(j=0; j<board_column; ++j){
				
						live_cell = 0;
				

						/* Left */
						if(j!=0) 
						{
							if(game_board[i][j-1] == 1 )
								{
									live_cell++;	
								}
						}

						/* Right */
						if( j != board_column - 1) {	
							if(game_board[i][j+1] == 1 )
								live_cell++;
						}

						/* Upper */
						if( i != 0) {	
							if(game_board[i-1][j] == 1 )			
								live_cell++;
						} 
				
						/* Lower */
						if( i < board_row - 1) {	
							if(game_board[i+1][j] == 1 )
								live_cell++;		
						} 

						/* Left Upper */
						if( j != 0 && i != 0) {
							if(game_board[i-1][j-1] == 1 )			
								live_cell++;		
						}

						/* Right Upper */
						if( i != 0 && j != board_column -1) {
							if(game_board[i-1][j+1] == 1 )			
								live_cell++;
						}    

						/* Left Lower */
						if( j != 0 && i != board_row -1) {
							if(game_board[i+1][j-1] == 1 )			
								live_cell++;
						}     

						/* Right Lower */
						if( i != board_row-1 && j != board_column -1) {
							if(game_board[i+1][j+1] == 1 )
								live_cell++;				
						}
		   
				
				
				
								/* Game Rules */	
	
								if(game_board[i][j] == 1 && (live_cell == 2 || live_cell == 3) )			
										copy_board[i][j] = 1;
								else if (game_board[i][j] == 0 && live_cell == 3)			
										copy_board[i][j] = 1;
								else if(!(game_board[i][j] == 1 && (live_cell == 2 || live_cell == 3)))
										copy_board[i][j] = 0;		
								else
										copy_board[i][j] = 0;

				
	
			}
					 
		}		
				/* Display the updated board */
	
				for(int m=0; m<board_row; ++m) {
						for(int n=0; n<board_column; ++n) {

							cout<<copy_board[m][n]<<"  ";
						
						}
						cout << endl;

				}

				/* Change from updated board to game board */

					for(i=0; i<board_row; ++i) {
						for(j=0; j<board_column; ++j) {

							game_board[i][j] = copy_board[i][j];
						}
					}

						N--;
		}

	
	
		/* Write to final board to output file */

		for(i=0; i<board_row; ++i) {
			for(j=0; j<board_column; ++j) {
				fprintf(outp, "%d  ", game_board[i][j]);
		}
		
			fprintf(outp,"\n");

		}

			cout << "\n--Final Board--\n" << endl;

		/* Free the two dimentional game board array */

		for(i=0; i < board_row; ++i)

				free(game_board[i]);
			
					free(game_board);

	} 

	/* Close files */
	fclose(inp);

	fclose(outp);


	return 0;

}
