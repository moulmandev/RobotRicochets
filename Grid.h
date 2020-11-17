#pragma once
#include "Case.h"

class Grid {
private:
	int nbRow;
	int nbCol;
	Case** board;
public:
	Grid(int, int);

};