#include "Grid.h"
#include "Set.h"
using namespace std;

Grid::Grid() : depth(0), nodes(0), inner(0), hits(0) {

	for (int i = 0; i < 256; i++) {
		moves[i] = 0;
		boardOneD[i] = 0;
	}

	srand(time(NULL));
	tabRobots.clear();

	int mursPossibles[] = { 16, 8, 4, 2, 20, 18, 12, 10 };
	for (int i = 0; i < 256; i++) {
		if (rand() % 10 == 0) {
			if ((int)i / 16 == 0 && i % 16 != 0)
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
			else {
				if(rand()%4 != 0)
					boardOneD[i] = mursPossibles[rand() % 4];
				else
					boardOneD[i] = mursPossibles[4 + (rand() % 4)];
			}
		}
		else {
			boardOneD[i] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		rand();
		rand();
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
	numRobotTarget = rand() % 4;
	tabRobots.at(numRobotTarget)->setTarget(true);
	token =  (tabRobots.at(numRobotTarget)->getPosition());
	cout << "Objectif : " << tabRobots[numRobotTarget]->getColor() << endl;
	goal = rand() % 256;
	goal = rand() % 256;
	goal = rand() % 256;
	goal = rand() % 256;
	token = (tabRobots.at(numRobotTarget)->getPosition());
}

void Grid::afficherGrille() {

	srand(time(NULL));

	for (int i = 1; i <= 256; i++) {
		if (i - 1 == goal)
			cout << "X";
		if (boardOneD[i - 1] % 2 == 0) {
			if (boardOneD[i - 1] != 0)
				cout << boardOneD[i - 1] << "\t";
			else
				cout << ".\t";
		}
		else {
			if (boardOneD[i - 1] == 1) {
				for (int j = 0; j < 4; j++) {
					if (tabRobots[j]->getPosition() == i - 1) {
						switch (tabRobots[j]->getColor())
						{
						case red:
							cout << "R\t";
							break;
						case green:
							cout << "G\t";
							break;
						case blue:
							cout << "B\t";
							break;
						case yellow:
							cout << "Y\t";
							break;
						}
					}
				}
			}
			else {
				for (int j = 0; j < 4; j++) {
					if (tabRobots[j]->getPosition() == i - 1) {
						switch (tabRobots[j]->getColor())
						{
						case red:
							cout << boardOneD[i - 1] - 1 << "R\t";
							break;
						case green:
							cout << boardOneD[i - 1] - 1 << "G\t";
							break;
						case blue:
							cout << boardOneD[i - 1] - 1 << "B\t";
							break;
						case yellow:
							cout << boardOneD[i - 1] - 1 << "Y\t";
							break;
						}
					}
				}
			}
		}
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



inline void swap(unsigned int* array, unsigned int a, unsigned int b) {
	unsigned int temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

inline unsigned int Grid::makeKey() {
	unsigned int tabRobotsCopy[4];

	for (int i = 0; i < tabRobots.size(); i++) {
		tabRobotsCopy[i] = tabRobots.at(i)->getPosition();
	}
	if (tabRobotsCopy[1] > tabRobotsCopy[2]) {
		swap(tabRobotsCopy, 1, 2);
	}
	if (tabRobotsCopy[2] > tabRobotsCopy[3]) {
		swap(tabRobotsCopy, 2, 3);
	}
	if (tabRobotsCopy[1] > tabRobotsCopy[2]) {
		swap(tabRobotsCopy, 1, 2);
	}
	return MAKE_KEY(tabRobotsCopy);
}

unsigned int Grid::hash(unsigned int key) {
	key = ~key + (key << 15);
	key = key ^ (key >> 12);
	key = key + (key << 2);
	key = key ^ (key >> 4);
	key = key * 2057;
	key = key ^ (key >> 16);
	return key;
}

//SetAlloc
//SetFree
//SetGrow
//SetAdd
//setGrow

inline bool Grid::gameOver() {
	Robot* robotGoal = getRobotGoal();

	if (robotGoal->getPosition() == goal) {//Game gagn�e : robotGoal arriv� case objectif
		return true;
	}
	else {
		return false;
	}
}

bool Grid::canMove(unsigned int robot, unsigned direction) {
	unsigned int index = tabRobots.at(robot)->getPosition();
	if (HAS_WALL(boardOneD[index], direction)) {
		return false;
	}
	if (last == PACK_MOVE(robot, REVERSE[direction])) {
		return false;
	}
	unsigned int newIndex = index + OFFSET[direction];
	if (HAS_ROBOT(boardOneD[newIndex])) {
		return false;
	}
	return true;
}

unsigned int Grid::computeMove(Robot* robot, unsigned int direction) {//Regarde si d�placement possible
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

void Grid::undoMove(unsigned int undo) {
	unsigned int robot = UNPACK_ROBOT(undo);
	unsigned int start = UNPACK_START(undo);
	unsigned int lastMove = UNPACK_LAST(undo);
	unsigned int end = tabRobots[robot]->getPosition();
	tabRobots[robot]->setPosition(start);
	last = lastMove;
	SET_ROBOT(boardOneD[start]);
	UNSET_ROBOT(boardOneD[end]);
}


void Grid::precomputeMinimumMoves() {//Calcule le nb min de mouvements pour chaque case pour aller � l'objectif
	bool status[256];

	for (int i = 0; i < 256; i++) {
		moves[i] = INT_MAX;//Initialisation avec une valeur "impossible"
		status[i] = false; //Aucun move n'a �t� rempli
	}
	moves[goal] = 0;//0 mouvement pr aller de goal � goal
	status[goal] = true;// On a trouv� le plus court mouvement pour aller de goal a goal

	bool done = false;
	while (!done) {//Tant qu'on a pas trouv� tous les chemins minimum pour aller � token
		done = true;
		for (unsigned int i = 0; i < 256; i++) {
			if (!status[i]) {//On cherche ?????????????
				continue;
			}
			status[i] = false;
			unsigned int dept = moves[i];
			for (unsigned int direction = 1; direction <= 8; direction <<= 1) {
				unsigned int index = i;
				while (!HAS_WALL(boardOneD[index], direction)) {//Tant qu'il n'y a pas de mur dans la direction observ�e
					index += OFFSET[direction];
					if (moves[index] > depth) {
						moves[index] = depth;
						status[index] = true;
						done = false;
					}
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
		if (index > 15 && (boardOneD[index] != 16 && boardOneD[index] != 18 && boardOneD[index] != 20)) {
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
		if (index < 255 - 15 && (boardOneD[index] != 8 && boardOneD[index] != 12 && boardOneD[index] != 10)) {
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
		if (index % 16 != 0 && (boardOneD[index] != 2 && boardOneD[index] != 18 && boardOneD[index] != 10)) {
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
		if ((boardOneD[index] != 4 && boardOneD[index] != 20 && boardOneD[index] != 12)) {
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
				else if (index == 15 || index == 31 || index == 47 || index == 63 || index == 79 || index == 95 || index == 111 || index == 127 || index == 143 || index == 159 || index == 175 || index == 191 || index == 207 || index == 223 || index == 239 || index == 255) {
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

		if (tabRobots[i]->getColor() == c)
			for (int i = 0; i < 4; i++)
				tabRobots[i] = rob;

		if (rob->getTarget() && rob->getPosition() == goal)
			cout << "Fini !!!" << endl;

	}
}
        

unsigned int Grid::search(unsigned int depth, unsigned int maxDepth, std::vector <char> path, std::set <Entry*> set) {// Set* set
	if (gameOver()) {
		return depth;// Gagné, en "depth" déplacements
	}
	if (depth == maxDepth) {// perdu
		return 0;
	}
	unsigned int remainingDepth = maxDepth - depth;
	if (moves[getRobotGoal()->getPosition()] > remainingDepth) {
		return 0;
	}

	for (std::set<Entry*>::iterator i = setEntry.begin(); i != setEntry.end(); i++) {

	}
	std::pair<std::set<Entry*>::iterator, bool> insertSet;
	insertSet = setEntry.insert(makeKey(), remainingDepth);//Pb avec booleens


	if (remainingDepth != 1 && (!insertSet.second)) {
		hits++;
		return 0;
	}
	inner++;
	for (unsigned int robot = 0; robot < 4; robot++) {
		if (robot && moves[tabRobots.at(numRobotTarget)->getPosition()] == remainingDepth) {
			continue;
		}
		for (unsigned int direction = 1; direction <= 8; direction <<= 1) {
			if (!canMove(robot, direction)) {
				continue;
			}

		}


	}

}
	

unsigned int Grid::principalSearch(std::vector <char> path, void (*pathSave)(unsigned int, unsigned int, unsigned int, unsigned int)) {
	if (gameOver()) {
		return 0;
	}
	unsigned int resultDepth = 0;

	std::set <Entry*> set;
	

	//set_alloc(&set, 1);//////Remplacer avec fonction ?

	precomputeMinimumMoves();
	for (unsigned int maxDepth = 1; maxDepth < MAX_DEPTH; maxDepth++) { //Tant que l'on a pas r�ussi
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
	/*Verifier*/
	for (std::set<Entry*>::iterator i = setEntry.begin(); i != setEntry.end(); i++) {
		delete* i;
	}
	setEntry.clear();
	/*---------------------------*/
	return resultDepth;

}

void Grid::pathSave() {
	cout << "Depth: " << depth << ",Nodes: " << nodes << "(" << inner << "inner," << hits << "hits)" << endl;
}



/*Set*/
/*void set_alloc(std::set<Entry*> set, unsigned int count) {
	for (unsigned int i = 0; i < count; i++) {
		set->mask = 0xfff;
		set->size = 0;
		set->data = (Entry*)calloc(set->mask + 1, sizeof(Entry));
		set++;
	}
}

void Grid::setGrow(Set* setE) {
	Set newSet;

	for (unsigned int index = 0; index <= setE->getMask(); index++) {
		Entry* entry = setE->getData() + index;
		if (entry->getKey()) {
			setAdd(&newSet, entry->getKey(), entry->getDepth());
		}
	}
	
}

bool Grid::setAdd(Set* setE, unsigned int key, unsigned int depth){
	unsigned int index = hash(key) & setE->getMask();
	Entry* entry = setE->getData() + index;
	while (entry->getKey() && entry->getKey() != key) {
		index = (index + 1) & setE->getMask();
		entry = setE->getData() + index;
	}
	if (entry->getKey()) {
		if (entry->getDepth() < depth) {
			entry->setDepth(depth);
			return true;
		}
		return false;
	}
	else {
		entry->setKey(key);
		entry->setDepth(depth);
		setE->setSize(setE->getSize() + 1);
		if (setE->getSize() * 2 > setE->getMask()) {
			setGrow(setE);
		}
		return true;
	}
}*/

