#include "Grille.h"

Grid::Grid(int row, int col) : nbRow(row), nbCol(col) {
	board = new Case*[nbRow];
	for (int i = 0; i < nbRow; i++) {
		board[i] = new Case[nbCol];
	}

	for (int x; x < nbRow; x++) {
		for (int y; y < nbCol; y++) {

		}
	}
}