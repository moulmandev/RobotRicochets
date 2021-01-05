#include "Grid.h"
#include "Set.h"
using namespace std;

Grid::Grid() : nbCol(16), nbRow(16), depth(0), nodes(0), inner(0), hits(0){
		
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			moves[i][j] = 0;
		}
	}

	srand(time(NULL));
	tabRobots.clear();

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
			board[x][y]++;//Rajout d'un robot
			tabRobots.push_back((new Robot(x,y)));
		}
		else {
			i--;
		}
	}

	/*Attribution RobotGoal*/
	int numRobotTarget = rand() % 4;
	tabRobots.at(numRobotTarget)->setTarget(true);
	tokenX = tabRobots.at(numRobotTarget)->getX();
	tokenY = tabRobots.at(numRobotTarget)->getY();

}

void Grid::afficherGrille(){
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			cout << board[i][j] << "\t";
		}
		cout << endl;
	}
}

Robot* Grid::getRobotGoal() {
	for (int i = 0; i < tabRobots.size(); i++) {
		if (tabRobots[i]->getTarget()) {
			return tabRobots[i];			
		}
	}
	
}

inline bool Grid::gameOver() {
	Robot* robotGoal = getRobotGoal();	

	if (robotGoal->getX() == tokenX && robotGoal->getY() == tokenY) {//robotGoal arrivé case objectif
		return true;
	}
	else {
		return false;
	}
}

void Grid::pathSave() {
	cout << "Depth: " << depth << ",Nodes: " << nodes << "(" << inner << "inner," << hits << "hits)" << endl;
}

void Grid::precomputeMinimumMoves() {
	bool status[16][16];

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			moves[i][j] = INT_MAX;//Initialisation avec une valeur "impossible"
			status[i][j] = false; //Aucun move n'a été rempli
		}
	}
	moves[tokenX][tokenY] = 0;//0 mouvement pr aller de token à token
	status[tokenX][tokenY] = true;// On a trouvé le plus court mouvement pour aller de token a token

	bool done = false;
	while (!done) {//Tant qu'on a pas trouvé tous les chemins les plus courts
		done = true;

		for (unsigned int i = 0; i < 16; i++) {
			for (unsigned j = 0; j < 16; j++) {
				if (!status[i][j]){
					continue;
				}
				status[i][j] = false;
				unsigned int dept = moves[i][j];
			}
		}


	}

}

unsigned int Grid::search(unsigned int depth, unsigned int maxDepth, std::vector <char> path, Set* set) {
	if (gameOver()) {
		return depth;// Gagné, en "depth" déplacements
	}
	if (depth == maxDepth) {// perdu
		return 0;
	}
	unsigned int remainingDepth = maxDepth - depth;
	if (moves[getRobotGoal()->getX()][getRobotGoal()->getY()] > remainingDepth) {
		return 0;
	}

}


unsigned int Grid::principalSearch(std::vector <char> path, void (*pathSave)(unsigned int, unsigned int, unsigned int, unsigned int)) {
	if (gameOver()){
		return 0;
	}
	unsigned int resultDepth = 0;
	Set set;
	//set_alloc(&set, 1);
	precomputeMinimumMoves();
	for (unsigned int maxDepth = 1; maxDepth < MAX_DEPTH; maxDepth++){ //Tant que l'on a pas réussi
		depth = 0;
		nodes = 0;
		hits = 0;
		inner = 0;

		resultDepth = search(0, maxDepth, path, &set);
		if (pathSave) {
			pathSave(maxDepth, nodes, inner, hits);
		}
		if (resultDepth) {
			break;
		}

	}
	//setFree(&set, 1);
	return resultDepth;

}

