#pragma once
#include "Case.h"
#include<random>
#include<time.h>
#include <vector>
#include "Set.h"
#include "constants.h"
#include <set>

class Grid {
private:
	int nbRow;
	int nbCol;
	int board[16][16];
	int boardOneD[256];
	std::vector <Robot*> tabRobots;
	int token;
	unsigned int moves[256];
	unsigned int depth;
	unsigned int nodes;
	unsigned int inner;
	unsigned int hits;
	//set <Entry*> set;
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