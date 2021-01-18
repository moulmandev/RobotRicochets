#pragma once
#include"Robot.h"
#include<random>
#include<time.h>
#include <vector>
#include "Set.h"
#include "constants.h"
#include <set>

class Grid {
private:
	int boardOneD[256];
	std::vector <Robot*> tabRobots;
	int token;
	int goal;
	unsigned int moves[256];
	unsigned int depth;
	unsigned int nodes;
	unsigned int inner;
	unsigned int hits;
	unsigned int last;
	int numRobotTarget;
	std::set <Entry*> setEntry;
	int goal; //Position objectif
public:
	Grid();
	void afficherGrille();
	Robot* getRobotGoal();
	
	/*Plus court chemin*/
	void pathSave();
	unsigned int search(unsigned int, unsigned int, std::vector <char>, std::set <Entry*>);
	unsigned int principalSearch(std::vector <char> path, void (*callback)(unsigned int, unsigned int, unsigned int, unsigned int));
	void precomputeMinimumMoves();
	inline bool gameOver();
	unsigned int hash(unsigned int key);
	//bool setAdd(Set* setE, unsigned int key, unsigned int depth);
	//void setGrow(Set* setE);
	unsigned int computeMove(Robot* robot, unsigned int direction);
	unsigned int doMove(Robot* robot, unsigned int direction);
	void undoMove(unsigned int undo);
	inline unsigned int makeKey();
	bool canMove(unsigned int, unsigned int);

	void deplacerRobot(color c, char dir);
};