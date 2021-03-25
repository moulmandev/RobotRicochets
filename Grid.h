#pragma once
#include"Robot.h"
#include<random>
#include<time.h>
#include <vector>
#include <set>
#include <map>
#include "constants.h"

class Grid {
private:
	int boardOneD[256];
	std::vector <Robot*> tabRobots;
	unsigned int moves[256];
	unsigned int depth;
	unsigned int nodes;
	unsigned int inner;
	unsigned int hits;
	unsigned int last;
	int numRobotTarget;
	std::map <std::vector<unsigned int>, unsigned int> mapSearch;
	int goal; //Position objectif
	std::vector<unsigned int> keyFound;

public:
	Grid();
	void tabRobotSorter();
	void afficherGrille();
	void afficherMoves();
	Robot* getRobotGoal();
	int* getBoard();
	void deplacerRobot(color c, char dir);
	void deplacerRobot(Robot* rob, char dir);

	/*Plus court chemin*/
	void pathSave(unsigned int maxDepth, unsigned int nodes, unsigned int inner, unsigned int hits);
	unsigned int search(unsigned int, unsigned int, std::vector <char>&, std::map <unsigned int*, unsigned int>);
	std::vector<std::string> principalSearch(std::vector <char>& path);
	void precomputeMinimumMoves();
	inline bool gameOver();
	void swap(std::vector <unsigned int>&, int, int);
	void positionSorter(std::vector <unsigned int>&);
	bool hasWall(unsigned int, unsigned int);
	bool hasRobot(unsigned int index, unsigned int direction);
	bool mapAdd(std::vector<unsigned int>, unsigned int depth);
	unsigned int computeMove(unsigned int robot, unsigned int direction);
	unsigned int* doMove(unsigned int, unsigned int direction);
	void setRobot(unsigned int);
	void unsetRobot(unsigned int);
	void undoMove(unsigned int* undo);
	bool checkLeftMove(unsigned int index, unsigned int direction);
	bool checkRightMove(unsigned int index, unsigned int direction);
	bool checkUpMove(unsigned int index, unsigned int direction);
	bool checkDownMove(unsigned int index, unsigned int direction);
	int getGoal();
	std::vector<Robot*> getRobots();
	std::vector<unsigned int> makeKey();
	bool operator<( unsigned int [4]);
	bool canMove(unsigned int, unsigned int);
	const unsigned int* getPrecomputeMinimumMovesArray();
};