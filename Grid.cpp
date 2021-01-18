#include "Grid.h"
#include "Set.h"
using namespace std;

Grid::Grid() : depth(0), nodes(0), inner(0), hits(0){
	
	for (int i = 0; i < 256; i++) {
			moves[i] = 0;
			boardOneD[i] = 0;
	}

	srand(time(NULL));
	tabRobots.clear();

	int mursPossibles[] = { 16, 8, 4, 2, 20, 18, 12, 10 };
	for (int i = 0; i < 256; i++) {
		if (rand() % 10 == 0) {				
			if ((int)i/16 == 0 && i%16 != 0)
				boardOneD[i] = 2;
			else if ((int)i / 16 == 0 && i % 16 == 0)
				boardOneD[i] = 4;
			else if ((int)i / 16 == 15 && i % 16 != 0)
				boardOneD[i] = 2;
			else if ((int)i / 16 == 15 && i % 16 == 0)
				boardOneD[i] = 4;
			else if ((int)i / 16 != 0 && i % 16 == 0)
				boardOneD[i] = 16;
			else if ((int)i / 16 == 0 && i % 16 == 0)
				boardOneD[i] = 8;
			else if ((int)i / 16 != 0 && i % 16 == 15)
				boardOneD[i] = 16;
			else if ((int)i / 16 == 0 && i % 16 == 15)
				boardOneD[i] = 8;
			else
				boardOneD[i] = mursPossibles[rand()%8];
		}
		else {
			boardOneD[i] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		int x = rand() % 256;
		if (boardOneD[x] % 2 == 0) {
			boardOneD[x]++;//Rajout d'un robot
			//Mettre le robot dans votre tableau
			tabRobots.push_back(new Robot(x));
		}
		else {
			i--;
		}
	}
	tabRobots[0]->setColor(blue);
	tabRobots[1]->setColor(red);
	tabRobots[2]->setColor(green);
	tabRobots[3]->setColor(yellow);

	/*Attribution RobotGoal*/
	int numRobotTarget = rand() % 4;
	tabRobots.at(numRobotTarget)->setTarget(true);
	token = (tabRobots.at(numRobotTarget)->getPosition());
}

void Grid::afficherGrille(){
	for (int i = 1; i <= 256; i++) {
		cout << boardOneD[i-1] << "\t";
			if (i != 0 && i % 16 == 0)
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

	if (robotGoal->getPosition() == token){ //robotGoal arrive case objectif
		return true;
	}
	else {
		return false;
	}
}


void Grid::pathSave() {
	cout << "Depth: " << depth << ",Nodes: " << nodes << "(" << inner << "inner," << hits << "hits)" << endl;
}

void Grid::precomputeMinimumMoves() { //Calcule le nb min de mouvements pour chaque case pour aller � l'objectif
	bool status[256];

	for (int i = 0; i < 256; i++) {
		moves[i] = INT_MAX;//Initialisation avec une valeur "impossible"
		status[i] = false; //Aucun move n'a �t� rempli
	}
	moves[token] = 0;//0 mouvement pr aller de token � token
	status[token] = true;// On a trouv� le plus court mouvement pour aller de token a token


	for (unsigned int i = 0; i < 256; i++) {
		if (!status[i]) {
			continue;
		}
		status[i] = false;
		unsigned int dept = moves[i];
		for (unsigned int direction = 1; direction <= 8; direction <<= 1) {
			unsigned int index = i;
			while (!HAS_WALL(boardOneD[index], direction)) {
				index += OFFSET[direction];
				if (moves[index] > depth) {
					moves[index] = depth;
					status[index] = true;
					//done = false;
				}
			}
		}
	}
}

					
void Grid::deplacerRobot(color c, char dir) {
	Robot* rob = new Robot(0);
	for (int i = 0; i < 4; i++)
		if (tabRobots[i]->getColor() == c)
			rob = tabRobots[i];

	int xRob = (int)(rob->getPosition() / 16);
	int yRob = (int)(rob->getPosition() % 16);
	int index;
	index = xRob * 16 + yRob;

	switch (dir)
	{
	case 'z':
		if (index > 15) {
			bool continuer = true;
			while (continuer) {

				//Mur au Sud
				if (boardOneD[index - 16] == 8) {
					continuer = false;
				}
				//Mur au Nord et case vide
				else if (boardOneD[index - 16] == 16 && boardOneD[index - 16] % 2 == 0) {
					boardOneD[index]--;
					boardOneD[index - 16]++;
					rob->setPosition(rob->getPosition() - 16);
					index -= 16;
					continuer = false;
				}
				//Haut de la grille
				else if (index <= 15) {
					continuer = false;
				}
				//Autre robot sur une case
				else if (boardOneD[index - 16] % 2 != 0) {
					continuer = false;
				}
				//Case libre on avance
				else {
					boardOneD[index]--;
					index -= 16;
					boardOneD[index]++;
					rob->setPosition(rob->getPosition() - 16);
				}
			}
		}
		break;

	case 's':
		if (index < 255 - 15) {
			bool continuer = true;
			while (continuer) {

				//Mur au Nord
				if (boardOneD[index + 16] == 16) {
					continuer = false;
				}
				//Mur au Sud et case vide
				else if (boardOneD[index + 16] == 8 && boardOneD[index + 16] % 2 == 0) {
					boardOneD[index]--;
					boardOneD[index + 16]++;
					rob->setPosition(rob->getPosition() + 16);
					index += 16;
					continuer = false;
				}
				//Bas de la grille
				else if (index >= 255 - 15) {
					continuer = false;
				}
				//Autre robot sur une case
				else if (boardOneD[index + 16] % 2 != 0) {
					continuer = false;
				}
				//Case libre on avance
				else {
					boardOneD[index]--;
					index += 16;
					boardOneD[index]++;
					rob->setPosition(rob->getPosition() + 16);
				}
			}
		}
		break;

	case 'q':
		if (index % 16 != 0) {
			bool continuer = true;
			while (continuer) {

				//Mur a l'Est
				if (boardOneD[index - 1] == 4) {
					continuer = false;
				}
				//Mur a l'Ouest et case vide
				else if (boardOneD[index - 1] == 2 && boardOneD[index - 1] % 2 == 0) {
					boardOneD[index]--;
					boardOneD[index - 1]++;
					rob->setPosition(rob->getPosition() - 1);
					index -= 1;
					continuer = false;
				}
				//Gauche de la grille
				else if (index % 16 == 0) {
					continuer = false;
				}
				//Autre robot sur une case
				else if (boardOneD[index - 1] % 2 != 0) {
					continuer = false;
				}
				//Case libre on avance
				else {
					boardOneD[index]--;
					index -= 1;
					boardOneD[index]++;
					rob->setPosition(rob->getPosition() - 1);
				}
			}
		}
		break;

	case 'd':
		if (index % 16 != 0) {
			bool continuer = true;
			while (continuer) {

				//Mur a l'Ouest
				if (boardOneD[index + 1] == 2) {
					continuer = false;
				}
				//Mur a l'Est et case vide
				else if (boardOneD[index + 1] == 4 && boardOneD[index + 1] % 2 == 0) {
					boardOneD[index]--;
					boardOneD[index + 1]++;
					rob->setPosition(rob->getPosition() + 1);
					index += 1;
					continuer = false;
				}
				//Droite de la grille
				else if (index % 15 == 0) {
					continuer = false;
				}
				//Autre robot sur une case
				else if (boardOneD[index + 1] % 2 != 0) {
					continuer = false;
				}
				//Case libre on avance
				else {
					boardOneD[index]--;
					index += 1;
					boardOneD[index]++;
					rob->setPosition(rob->getPosition() + 1);
				}
			}
		}
		break;
	}

	for (int i = 0; i < 4; i++)
		if (tabRobots[i]->getColor() == c)
			tabRobots[i] = rob;

}

//void Grid::setGrow(Set* setE) {
//	Set newSet;
//
//
//
//	for (unsigned int index = 0; index <= setE->getMask(); index++) {
//		Entry* entry = setE->getData() + index;
//		if (entry->getKey()) {
//			setAdd(&newSet, entry->getKey(), entry->getDepth());
//		}
//	}
//	
//}

unsigned int Grid::hash(unsigned int key) {
	key = ~key + (key << 15);
	key = key ^ (key >> 12);
	key = key + (key << 2);
	key = key ^ (key >> 4);
	key = key * 2057;
	key = key ^ (key >> 16);
	return key;
}

//bool Grid::setAdd(Set* setE, unsigned int key, unsigned int depth){
//	unsigned int index = hash(key) & setE->getMask();
//	Entry* entry = setE->getData() + index;
//	while (entry->getKey() && entry->getKey() != key) {
//		index = (index + 1) & setE->getMask();
//		entry = setE->getData() + index;
//	}
//	if (entry->getKey()) {
//		if (entry->getDepth() < depth) {
//			entry->setDepth(depth);
//			return true;
//		}
//		return false;
//	}
//	else {
//		entry->setKey(key);
//		entry->setDepth(depth);
//		setE->setSize(setE->getSize() + 1);
//		if (setE->getSize() * 2 > setE->getMask()) {
//			setGrow(setE);
//		}
//		return true;
//	}
//}

inline void swap(std::vector<Robot> tab, unsigned int a, unsigned int b) {
	unsigned int temp = tab.at(a).getPosition();
	tab.at(a).setPosition(tab.at(b).getPosition());
	tab.at(b).setPosition(temp);
}

bool Grid::canMove(Robot* robot, unsigned direction) {
	unsigned int index = 
}



inline unsigned int Grid::makeKey() {
	std::vector <Robot> tabRobotsCopy;

	for (int i = 0; i < tabRobots.size(); i++) {
		tabRobotsCopy.push_back(*tabRobots.at(i));
	}
	if (tabRobotsCopy.at(1).getPosition() > tabRobotsCopy.at(2).getPosition()) {
		swap(tabRobotsCopy, 1, 2);
	}
	if (tabRobotsCopy.at(2).getPosition() > tabRobotsCopy.at(3).getPosition()) {
		swap(tabRobotsCopy, 2, 3);
	}
	if (tabRobotsCopy.at(1).getPosition() > tabRobotsCopy.at(2).getPosition()) {
		swap(tabRobotsCopy, 1, 2);
	}
	return MAKE_KEY(tabRobotsCopy);//Ne marche pas

}

unsigned int Grid::search(unsigned int depth, unsigned int maxDepth, std::vector <char> path, Set* set) {
	if (gameOver()) {
		return depth;// Gagn�, en "depth" d�placements
	}
	if (depth == maxDepth) {// perdu
		return 0;
	}
	unsigned int remainingDepth = maxDepth - depth;
	if (moves[getRobotGoal()->getPosition()] > remainingDepth) {
		return 0;
	}

	bool insertSet = false;	

	if (remainingDepth != 1 && (!setEntry.insert(makeKey(), remainingDepth))){
		hits++;
		return 0;
	}
	inner++;
	for (unsigned int robot = 0; robot < 4; robot++) {
		if (robot && moves[tabRobots[token]->getPosition()] == height) {
			continue;
		}
		for (unsigned int direction = 1; direction <= 8; direction <<= 1) {
			if (!canMove(, direction)) {
				continue;
			}

		}


	}

}

unsigned int Grid::computeMove(Robot* robot, unsigned int direction){//Regarde si d�placement possible
	unsigned int index = robot->getPosition() + OFFSET[direction];
	while (true) {
		if (HAS_WALL(boardOneD[index], direction)) {
			break;
		}
		unsigned int newIndex = index + OFFSET[direction];
		if (HAS_ROBOT(boardOneD[newIndex])) {
			break;
		}
		index = newIndex;
	}
	return index;
}

unsigned int Grid::doMove(Robot* robot, unsigned int direction) {
	unsigned int start = robot->getPosition();
	unsigned int end = computeMove(robot, direction);
	unsigned int lastMove = last;
	robot->setPosition(end);
	last = PACK_MOVE(robot->getPosition(), direction);
	UNSET_ROBOT(boardOneD[start]);
	SET_ROBOT(boardOneD[end]);
	return PACK_UNDO(robot->getPosition(), start, last);
}

void Grid::undoMove(unsigned int undo){
	unsigned int robot = UNPACK_ROBOT(undo);
	unsigned int start = UNPACK_START(undo);
	unsigned int lastMove = UNPACK_LAST(undo);
	unsigned int end = tabRobots[robot]->getPosition();
	tabRobots[robot]->setPosition(start);
	last = lastMove;
	SET_ROBOT(tabRobots[start]->getPosition());
	UNSET_ROBOT(tabRobots[end]->getPosition());
}


unsigned int Grid::principalSearch(std::vector <char> path, void (*pathSave)(unsigned int, unsigned int, unsigned int, unsigned int)) {
	if (gameOver()){
		return 0;
	}
	unsigned int resultDepth = 0;
	Set set;
	//set_alloc(&set, 1);//////Remplacer avec fonction ?
	
	precomputeMinimumMoves();
	for (unsigned int maxDepth = 1; maxDepth < MAX_DEPTH; maxDepth++){ //Tant que l'on a pas r�ussi
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
	setEntry.clear();///////////////////////A la place de //setFree(&set, 1);
	return resultDepth;

}

