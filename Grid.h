#pragma once
#include "Case.h"
#include<random>
#include<time.h>

class Grid {
private:
	int nbRow;
	int nbCol;
	int board[16][16];
public:
	Grid();
	void afficherGrille();
};