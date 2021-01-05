#pragma once
#include "Case.h"
#include<random>
#include<time.h>
#include <vector>
#include "Set.h"
#include "constants.h"

class Grid {
private:
	int nbRow;
	int nbCol;
	int board[16][16];
	std::vector <Robot*> tabRobots;
	int tokenX;
	int tokenY;
	unsigned int moves[16][16];
	unsigned int depth;
	unsigned int nodes;
	unsigned int inner;
	unsigned int hits;
public:
	Grid();
	void afficherGrille();
	void pathSave();
	unsigned int search(unsigned int, unsigned int, std::vector <char>, Set*);
	unsigned int principalSearch(std::vector <char> path, void (*callback)(unsigned int, unsigned int, unsigned int, unsigned int));
	Robot* getRobotGoal();
	void precomputeMinimumMoves();
	inline bool gameOver();
};