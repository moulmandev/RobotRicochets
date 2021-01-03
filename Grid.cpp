#include "Grid.h"
using namespace std;

Grid::Grid() : nbCol(16), nbRow(16) {

	tabRobots = new Robot[4];
	srand(time(NULL));
	int mursPossibles[] = { 16, 8, 4, 2, 20, 18, 12, 10 };
	for (int i = 0; i < nbRow; i++) {
		for (int j = 0; j < nbCol; j++) {
			if (rand() % 10 == 0) {				
				if (i == 0 && j != 0)
					board[i][j] = 2;
				else if (i == 0 && j == 0)
					board[i][j] = 4;
				else if (i == 15 && j != 0)
					board[i][j] = 2;
				else if (i == 15 && j == 0)
					board[i][j] = 4;
				else if (i != 0 && j == 0)
					board[i][j] = 16;
				else if (i == 0 && j == 0)
					board[i][j] = 8;
				else if (i != 0 && j == 15)
					board[i][j] = 16;
				else if (i == 0 && j == 15)
					board[i][j] = 8;
				else
					board[i][j] = mursPossibles[rand()%8];
			}
			else {
				board[i][j] = 0;
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		int x = rand() % 16;
		int y = rand() % 16;
		if (board[x][y] % 2 == 0) {
			board[x][y]++;
		}
		else {
			i--;
		}
	}

}

void Grid::afficherGrille()
{
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			cout << board[i][j] << "\t";
		}
		cout << endl;
	}
}
