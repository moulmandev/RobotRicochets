#pragma once
#include"Robot.h"
#include<random>
#include<time.h>
#include <vector>
#include <set>
#include <map>
#include "Entry.h"

class Grid {
private:
	int boardOneD[256];
	//TODO : changer en tableau statique
	std::vector <Robot*> tabRobots;
	unsigned int moves[256];
	unsigned int depth;
	unsigned int nodes;
	unsigned int inner;
	unsigned int hits;
	unsigned int last;
	int numRobotTarget;
	std::set <Entry*> setEntry;
	std::map <unsigned int*, unsigned int> mapSearch;//Tableau 4 keys robots, int : depth
	int goal; //Position objectif

public:
	Grid();
	void afficherGrille();
	Robot* getRobotGoal();
	void deplacerRobot(color c, char dir);
	
	/*Plus court chemin*/
	void pathSave();
	int compare(Entry*, Entry*);
	unsigned int search(unsigned int, unsigned int, std::vector <char>, std::set <Entry*>);
	unsigned int principalSearch(std::vector <char> path, void (*callback)(unsigned int, unsigned int, unsigned int, unsigned int));
	void precomputeMinimumMoves();
	inline bool gameOver();
	bool mapAdd(unsigned int key[NB_ROBOTS], unsigned int depth);
	unsigned int computeMove(unsigned int robot, unsigned int direction);
	unsigned int doMove(unsigned int, unsigned int direction);
	void undoMove(unsigned int undo);
	unsigned int* makeKey();
	bool operator<(unsigned int tab[NB_ROBOTS]);
	bool canMove(unsigned int, unsigned int);
	
};