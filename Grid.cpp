#include "Grid.h"

Grid::Grid(int row, int col) : nbRow(row), nbCol(col) {

	board = new Case*[nbRow];
	for (int i = 0; i < nbRow; i++) {
		board[i] = new Case[nbCol];
	}

	for (int x=0; x < nbRow; x++) {
		for (int y =0; y < nbCol; y++) {

		}
	}
}

int Grid::getNbCol() {
	return nbCol;
}

int Grid::getNbRow() {
	return nbRow;
}

Case* Grid::getCase(int row, int column) {
	return &board[row][column];
}
