#include "Grid.h"

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
				if (rand() % 4 != 0)
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
	cout << "Objectif : " << tabRobots[numRobotTarget]->getColor() << endl;
	goal = rand() % 256;
	goal = rand() % 256;
	goal = rand() % 256;
	goal = rand() % 256;
}

void Grid::afficherGrille(){

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

	vector <char> path;
	principalSearch(path);
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

unsigned int* Grid::makeKey() {
	unsigned int tabRobotsCopy[4];//Tableau avec la position des robots

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
	return tabRobotsCopy;
}

inline bool Grid::gameOver() {
	Robot* robotGoal = getRobotGoal();

	if (robotGoal->getPosition() == goal) {//Game gagnée : robotGoal arrivé case objectif
		return true;
	}
	else {
		return false;
	}
}

bool Grid::canMove(unsigned int robot, unsigned int direction) {
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

unsigned int Grid::computeMove(unsigned int robot, unsigned int direction) {//Regarde si d�placement possible
	unsigned int index = tabRobots.at(robot)->getPosition() + OFFSET[direction];
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

unsigned int Grid::doMove(unsigned int robot, unsigned int direction) {
	unsigned int start = tabRobots.at(robot)->getPosition();
	unsigned int end = computeMove(robot, direction);
	unsigned int lastMove = last;
	tabRobots.at(robot)->setPosition(end);
	last = PACK_MOVE(tabRobots.at(robot)->getPosition(), direction);
	UNSET_ROBOT(boardOneD[start]);
	SET_ROBOT(boardOneD[end]);
	return PACK_UNDO(tabRobots.at(robot)->getPosition(), start, last);
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


void Grid::precomputeMinimumMoves(){//Calcule le nb min de mouvements pour chaque case pour aller à l'objectif
	//cout << "Dans precompute minimum moves : " << endl;
	bool status[256];

	for (int i = 0; i < 256; i++) {
		moves[i] = INT_MAX;//Initialisation avec une valeur "impossible"
		status[i] = false; //Aucun move n'a été rempli
	}
	
	moves[goal] = 0;//0 mouvement pr aller de goal à goal
	status[goal] = true;// On a trouvé le plus court mouvement pour aller de goal a goal
	cout << "INDEX GOAL : " << goal << endl;
	/*for (int i = 0; i < 256; i++) {
		cout << "Moves : " << moves[i] << " status : ";
		cout << status[i] << endl;
	}*/

	bool done = false;
	unsigned int depth = 0;
	while (!done){//Tant qu'on a pas trouvé tous les chemins minimum pour aller à goal
		done = true;
		for (unsigned int i = 0; i < 256; i++){
			//cout << "------------------------------Nouvelle case-------------------------------------" << i << endl;
			if (!status[i]) {
				continue;
			}
			status[i] = false;
			depth = moves[i]+1;
			cout << "DEPTH ++" << endl;
			cout << depth << endl;
			//cout << "DEPTH : " << depth << endl;
			for (unsigned int direction = 1; direction <= 8; direction <<= 1){
				unsigned int index = i;
				/*cout << "------------Nouvelles direction" << endl;
				cout << "INDEEEEEEEEX" << index << endl;*/
				while (!HAS_WALL(boardOneD[index], direction) && OFFSET[direction] == 16 && index <240 || OFFSET[direction]== -16 && index >= 16 || OFFSET[direction] == 1 && (index == 15 || index == 31 || index == 47 || index == 63 || index == 79 || index == 95 || index == 111 || index == 127 || index == 143 || index == 159 || index == 175 || index == 191 || index == 207 || index == 223 || index == 239 || index == 255) || OFFSET[direction] == -1 && index % 16 != 0) {
						index += OFFSET[direction];
						//cout << "Apres Index: " << index << endl;				
						if (moves[index] > depth){
							moves[index] = depth;
							status[index] = true;
							done = false;
						}
						/*cout << "moves[ "<< index << "] : " << moves[index] << endl;
						cout << "depth : " << depth << endl;	*/			

				}
				//cout << "Il y a un mur " << endl;
			}
			/*cout << "------------------------------------------TOUR "<< i <<" : " << endl;
			for (int i = 0; i < 256; i++) {
				cout << "Moves : " << moves[i] << " status : ";
				cout << status[i] << endl;
			}*/
			
		}
	}
	/*cout << "AFFICHAGE : " << endl;
	for (int i = 0; i < 256; i++) {
		cout << "Moves : " <<moves[i] << " status : "; 
		cout << status[i] << endl;
	}*/
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

		for (int i = 0; i < 4; i++)
			if (tabRobots[i]->getColor() == c)
				tabRobots[i] = rob;

		if (rob->getTarget() && rob->getPosition() == goal)
			cout << "Fini !!!" << endl;

	}
}


unsigned int Grid::search(unsigned int depth, unsigned int maxDepth, vector <char> path, map <unsigned int*, unsigned int> map) {// Set* set
	if (gameOver()) {
		return depth;// Gagné, en "depth" déplacements
	}
	if (depth == maxDepth) {// perdu
		return 0;
	}
	unsigned int remainingDepth = maxDepth - depth;

	if (moves[getRobotGoal()->getPosition()] > remainingDepth) {//perdu
		return 0;
	}

	if (remainingDepth != 1 && !mapAdd(makeKey(), remainingDepth)) {//Si on n'a pas pu ajouter tel déplacement à la map
		hits++;//Statistics++
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
			unsigned int undo = doMove(robot, direction);
			unsigned int result = search(depth + 1, maxDepth, path, map);
			undoMove(undo);
			if (result) {
				path[depth] = PACK_MOVE(robot, direction);
				return result;
			}
		}
	}
	return 0;
}


unsigned int Grid::principalSearch(std::vector <char> path) {
	if (gameOver()) {
		return 0;
	}
	unsigned int resultDepth = 0;
	map <unsigned int*, unsigned int> map;

	precomputeMinimumMoves();
	for (unsigned int maxDepth = 1; maxDepth < MAX_DEPTH; maxDepth++) { //Tant que l'on a pas réussi
		depth = 0;
		nodes = 0;
		hits = 0;
		inner = 0;

		resultDepth = search(0, maxDepth, path, map);
		//if (pathSave()) {       //J'ai enlevé ça parce que pas booléen
			pathSave(maxDepth, nodes, inner, hits);
		//}
		if (resultDepth) {
			break;
		}

	}
	/*for (auto i : setEntry) {
		cout << "Delete setEntry ";
		delete i;
	}
	setEntry.clear();*/

	mapSearch.clear();
	cout << "map deleted" << endl;
	
	return resultDepth;

}

void Grid::pathSave(unsigned int maxDepth, unsigned int nodes, unsigned int inner, unsigned int hits) {
	cout << "Depth: " << depth << ",Nodes: " << nodes << "(" << inner << "inner," << hits << "hits)" << endl;
}

int Grid::compare(Entry* e1, Entry* e2) {
	if (*e1 < *e2)
		return -1;
	else if (*e1 == *e2)
		return 0;
	return 1;
	
}

bool Grid::operator<(unsigned int tab[NB_ROBOTS]){	
	map<unsigned int*, unsigned int>::iterator i;
	for(i = mapSearch.begin(); i!=mapSearch.end(); i++){
		for (int j = 0; j < 4; j++) {
			if (i->first[j] < tab[j]) {//Key de setMap < Key de tab
				return true;
			}
		}
	}
	return false;
}

bool Grid::mapAdd(unsigned int key[NB_ROBOTS], unsigned int remainingDepth){
	bool equal;
	pair<unsigned int*, unsigned int> newElement;
	newElement.first = new unsigned int[4];

	for (auto m : mapSearch) {
		equal = true;
		for (int i = 0; i < NB_ROBOTS; i++){//On cherche si key existe déjà dans map
			if (key < m.first) {
				equal = false;
			}
		}
		if (equal) {
			if (m.second < remainingDepth) {
				m.second = remainingDepth;
				return true;
			}
			return false;
		}
		else {//Si key n'existe pas dans la map
			for (int i = 0; i < NB_ROBOTS; i++) {
				newElement.first[i] = key[i];
			}
			newElement.second = remainingDepth;
			mapSearch.insert(newElement);
			return true;
		}
	}
	
}

