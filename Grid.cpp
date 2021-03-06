#include "Grid.h"
#include <string>
#include <fstream>

Grid::Grid() : depth(0), nodes(0), inner(0), hits(0), last(0) {

	for (int i = 0; i < 256; i++) {
		moves[i] = 0;
		boardOneD[i] = 0;
	}

	mapSearch.clear();

	srand(time(NULL));
	tabRobots.clear();

	int mursPossibles[] = { 16, 8, 4, 2, 20, 18, 12, 10 };
	for (int i = 0; i < 256; i++) {

		boardOneD[i] = 0;

		if (i == 0)
			boardOneD[i] = 18;
		else if (i == 15)
			boardOneD[i] = 20;
		else if (i == 240)
			boardOneD[i] = 10;
		else if (i == 255)
			boardOneD[i] = 12;
		//Haut de la grille 16, 20, 18
		else if (i <= 15) {
			int randNord[] = { 16, 20, 18 };
			if (rand() % 8 == 0)
				boardOneD[i] = randNord[rand() % 3];
			else
				boardOneD[i] = 16;
		}
		//Bas de la grille 8, 10, 12
		else if (i >= 255 - 15) {
			int randSud[] = { 8, 10, 12 };
			if (rand() % 8 == 0)
				boardOneD[i] = randSud[rand() % 3];
			else
				boardOneD[i] = 8;
		}
		//Gauche de la grille 2, 18, 10
		else if (i % 16 == 0) {
			int randOuest[] = { 2, 18, 10 };
			if (rand() % 8 == 0)
				boardOneD[i] = randOuest[rand() % 3];
			else
				boardOneD[i] = 2;
		}
		//Droite de la grille 4, 20, 12
		else if (i == 15 || i == 31 || i == 47 || i == 63 || i == 79 || i == 95 || i == 111 || i == 127 || i == 143 || i == 159 || i == 175 || i == 191 || i == 207 || i == 223 || i == 239 || i == 255) {
			int randEst[] = { 4, 20, 12 };
			if (rand() % 8 == 0)
				boardOneD[i] = randEst[rand() % 3];
			else
				boardOneD[i] = 4;
		}

		if (rand() % 4 == 0 && !(i <= 15 || i >= 255 - 15 || i % 16 == 0 || (i == 15 || i == 31 || i == 47 || i == 63 || i == 79 || i == 95 || i == 111 || i == 127 || i == 143 || i == 159 || i == 175 || i == 191 || i == 207 || i == 223 || i == 239 || i == 255))) {

			if (rand() % 4 != 0)
				boardOneD[i] = mursPossibles[rand() % 4];
			else
				boardOneD[i] = mursPossibles[4 + (rand() % 4)];

		}

	}
	boardOneD[119] = 18;
	boardOneD[120] = 20;
	boardOneD[135] = 10;
	boardOneD[136] = 12;

	for (int i = 0; i < 4; i++) {
		rand();
		rand();
		int x = rand() % 256;
		if (boardOneD[x] % 2 == 0) {
			boardOneD[x]++;//Rajout d'un robot
			//Mettre le robot dans le tableau
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

	numRobotTarget = rand() % 4;
	tabRobots.at(numRobotTarget)->setTarget(true);

	goal = rand() % 256;
	goal = rand() % 256;
	goal = rand() % 256;
	goal = rand() % 256;
	std::cout << "Choix robot goal position: " << tabRobots.at(numRobotTarget)->getPosition() << std::endl;


	tabRobotSorter();

	for (int i = 0; i < 4; i++) {
		tabRobots[i]->setTarget(false);
	}


	last = 0;
	numRobotTarget = rand() % 4;
	tabRobots.at(numRobotTarget)->setTarget(true);

	afficherGrille();
	std::cout << std::endl;
}

void Grid::swap(std::vector <unsigned int>& tab, int first, int second) {
	unsigned int tmp = tab.at(first);
	tab.at(first) = tab.at(second);
	tab.at(second) = tmp;
}

void Grid::positionSorter(std::vector <unsigned int>& tab) {
	if (tab[2] < tab[1]) {
		swap(tab,1, 2);
	}
	if (tab[3] < tab[2]) {
		swap(tab,2, 3);
	}
	if (tab[2] < tab[1]) {
		swap(tab, 1, 2);
	}
}

void Grid::tabRobotSorter() {
	unsigned int tmp = 1;

	if (tabRobots[2]->getPosition() < tabRobots[1]->getPosition()) {
		tmp = tabRobots.at(2)->getPosition();
		tabRobots.at(2)->setPosition(tabRobots.at(1)->getPosition());
		tabRobots.at(1)->setPosition(tmp);
	}
	if (tabRobots[3]->getPosition() < tabRobots[2]->getPosition()) {
		tmp = tabRobots.at(3)->getPosition();
		tabRobots.at(3)->setPosition(tabRobots.at(2)->getPosition());
		tabRobots.at(2)->setPosition(tmp);
	}
	if (tabRobots[2]->getPosition() < tabRobots[1]->getPosition()) {
		tmp = tabRobots.at(2)->getPosition();
		tabRobots.at(2)->setPosition(tabRobots.at(1)->getPosition());
		tabRobots.at(1)->setPosition(tmp);
	}
}


void Grid::afficherMoves(){
	for (int i = 0; i < 256; i++) {	
		if (i != 0 && i % 16 == 0)
			std::cout << std::endl;
		if (moves[i] != INT_MAX) {
			std::cout << moves[i] << "\t";
		}
		else {
			std::cout << "pb" << "\t";
		}
	}
}

void Grid::afficherGrille(){
	
	srand(time(NULL));

	for (int i = 1; i <= 256; i++) {
		if (i - 1 == goal)
			std::cout << "X";
		if (boardOneD[i - 1] % 2 == 0) {
			if (boardOneD[i - 1] != 0)
				std::cout << boardOneD[i - 1] << "\t";
			else
				std::cout << ".\t";
		}
		else {
			if (boardOneD[i - 1] == 1) {
				for (int j = 0; j < 4; j++) {
					if (tabRobots[j]->getPosition() == i - 1) {
						if (tabRobots[j]->getTarget()) {
							std::cout << "M\t";
						}
						else {
							switch (tabRobots[j]->getColor())
							{
							case red:
								std::cout << "R\t";
								break;
							case green:
								std::cout << "G\t";
								break;
							case blue:
								std::cout << "B\t";
								break;
							case yellow:
								std::cout << "Y\t";
								break;

							}
						}
					}
				}
			}

			else {
				for (int j = 0; j < 4; j++) {
					if (tabRobots[j]->getPosition() == i - 1) {
						if (tabRobots[j]->getTarget()) {
							std::cout << "M\t";
						}
					else {
						switch (tabRobots[j]->getColor())
							{
							case red:							
								std::cout << boardOneD[i - 1] - 1 << "R\t";
								break;
							case green:
								std::cout << boardOneD[i - 1] - 1 << "G\t";
								break;
							case blue:
								std::cout << boardOneD[i - 1] - 1 << "B\t";
								break;
							case yellow:
								std::cout << boardOneD[i - 1] - 1 << "Y\t";
								break;
							}
					}
						
					}
				}
			}
		}
		if (i != 0 && i % 16 == 0)
			std::cout << std::endl;
	}

}


Robot* Grid::getRobotGoal() {
	return tabRobots.at(numRobotTarget);
}

int* Grid::getBoard()
{
	return boardOneD;
}

int Grid::getGoal()
{
	return goal;
}

std::vector<Robot*> Grid::getRobots()
{
	return tabRobots;
}

std::vector<unsigned int> Grid::makeKey(){
	std::vector<unsigned int> tabRobotsCopy;

	for (int i = 0; i < NB_ROBOTS; i++) {
		tabRobotsCopy.push_back(tabRobots[i]->getPosition());//tabRobots[i] deja triés à partir de tabRobots[1]
	}	
	positionSorter(tabRobotsCopy);
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

	if (hasWall(index, direction)) {//S'il y a un mur
		return false;
	}
	if (last == PACK_MOVE(robot, REVERSE[direction])) {
		return false;
	}
	if (hasRobot(index, direction)) {//S'il y a un robot
		return false;
	}
	return true;

}

const unsigned int* Grid::getPrecomputeMinimumMovesArray() {
	return moves;
}

bool Grid::hasWall(unsigned int index, unsigned int direction){	
	if (index + OFFSET[direction] >= 0 && index + OFFSET[direction] < 256) {
		if (OFFSET[direction] == -16 && checkUpMove(index, direction) || OFFSET[direction] == 16 && checkDownMove(index, direction) || OFFSET[direction] == -1 && checkLeftMove(index, direction) || OFFSET[direction] == 1 && checkRightMove(index, direction)){
			return false;
		}
	}
	return true;
}

bool Grid::hasRobot(unsigned int index, unsigned int direction) {
	if (boardOneD[index + OFFSET[direction]]%2==1) {//S'il y a un robot
		return true;
	}
	return false;
}



unsigned int Grid::computeMove(unsigned int robot, unsigned int direction) {//Regarde si déplacement possible
	
	unsigned int index = tabRobots.at(robot)->getPosition() + OFFSET[direction];

	while (true) {
		if (hasWall(index, direction)) {
			break;
		}
		unsigned int newIndex = index + OFFSET[direction];

		if (hasRobot(index, direction)) {//S'il y a un robot
			break;
		}
		index = newIndex;
	}
	return index;
}

unsigned int* Grid::doMove(unsigned int robot, unsigned int direction) {
	
	unsigned int start = tabRobots.at(robot)->getPosition();//Position de départ du robot goal
	unsigned int end = computeMove(robot, direction);//position d'arrivée du robot goal	
	unsigned int lastMove = last;

	tabRobots.at(robot)->setPosition(end);

	last = PACK_MOVE(robot, direction);

	UNSET_ROBOT(boardOneD[start]);
	
	SET_ROBOT(boardOneD[end]);

	unsigned int* tabMove = new unsigned int[3];
	
	tabMove[0] = robot;
	tabMove[1] = start;
	tabMove[2] = lastMove;
	return tabMove;
}

void Grid::setRobot(unsigned int start) {
	boardOneD[start] += 1;
}

void Grid::unsetRobot(unsigned int start) {
	boardOneD[start] -= 1;
}

void Grid::undoMove(unsigned int* undo){
	unsigned int robot = undo[0];
	unsigned int start = undo[1];
	unsigned int lastMove = undo[2];
	unsigned int end = tabRobots.at(robot)->getPosition();

	tabRobots.at(robot)->setPosition(start);

	last = lastMove;	
	
	SET_ROBOT(boardOneD[start]);
	UNSET_ROBOT(boardOneD[end]);

}

bool Grid::checkLeftMove(unsigned int index, unsigned int direction){
	
	if (boardOneD[index + OFFSET[direction]] != 4 && boardOneD[index + OFFSET[direction]] != 20 && boardOneD[index + OFFSET[direction]] != 12 && boardOneD[index + OFFSET[direction]] != 6 && boardOneD[index]!= 2 + 1 && boardOneD[index] !=10 + 1 && boardOneD[index] !=18 + 1 && boardOneD[index] != 6+1 && boardOneD[index] != 2 && boardOneD[index] != 10 && boardOneD[index] != 18 && boardOneD[index] != 6){
		return true;
	}
	return false;
}

bool Grid::checkRightMove(unsigned int index, unsigned int direction) {
	if(boardOneD[index + OFFSET[direction]] != 2 && boardOneD[index + OFFSET[direction]] != 18 && boardOneD[index + OFFSET[direction]] != 10 && boardOneD[index + OFFSET[direction]]!=6 && boardOneD[index]!= 4 + 1 && boardOneD[index] != 20 + 1 && boardOneD[index] != 12 + 1 && boardOneD[index] != 6+1 && boardOneD[index] != 4 && boardOneD[index] != 20 && boardOneD[index] != 12 && boardOneD[index] != 6){
		return true;
	}
	return false;
}


bool Grid::checkUpMove(unsigned int index, unsigned int direction) {
	
	if((boardOneD[index + OFFSET[direction]] != 8 && boardOneD[index + OFFSET[direction]]!=24 && boardOneD[index + OFFSET[direction]] != 12 && boardOneD[index + OFFSET[direction]] != 10 && boardOneD[index] != 16+1 && boardOneD[index] != 18 + 1 && boardOneD[index] != 20 + 1 && boardOneD[index] != 24+1 && boardOneD[index] != 16 && boardOneD[index] != 18 && boardOneD[index] != 20 && boardOneD[index] != 24)){
		return true;
	}
	return false;
}

bool Grid::checkDownMove(unsigned int index, unsigned int direction) {
	if((boardOneD[index + OFFSET[direction]] != 16 && boardOneD[index + OFFSET[direction]] != 24 && boardOneD[index + OFFSET[direction]] != 20 && boardOneD[index + OFFSET[direction]] != 18 && boardOneD[index] != 8 + 1 && boardOneD[index] != 10 + 1 && boardOneD[index] != 12 + 1 && boardOneD[index] != 24+1 && boardOneD[index] != 8 && boardOneD[index] != 10 && boardOneD[index] != 12 && boardOneD[index] != 24)){
		return true;
	}
	return false;
}


void Grid::precomputeMinimumMoves() {//Calcule le nb min de mouvements pour chaque case pour aller à l'objectif

	bool status[256];

	for (int i = 0; i < 256; i++) {
		moves[i] = INT_MAX;//Initialisation avec une valeur "impossible"
		status[i] = false; //Aucun move n'a été rempli
	}

	moves[goal] = 0;//0 mouvement pr aller de goal à goal
	status[goal] = true;// On a trouvé le plus court mouvement pour aller de goal a goal

	bool done = false;
	unsigned int depth = 0;

	while (!done) {//Tant qu'on a pas trouvé tous les chemins minimum pour aller à goal
		done = true;
		for (unsigned int i = 0; i < 256; i++) {

			if (!status[i]) {
				continue;
			}

			status[i] = false;
			depth = moves[i] + 1;

			for (unsigned int direction = 1; direction <= 8; direction <<= 1) {
				unsigned int index = i;
				while (index + OFFSET[direction] >= 0 && index + OFFSET[direction] < 256 && (OFFSET[direction] == 16 && index < 240 || OFFSET[direction] == -16 && index > 15 || OFFSET[direction] == 1 && (index != 15 && index != 31 || index != 47 && index != 63 && index != 79 && index != 95 && index != 111 && index != 127 && index != 143 && index != 159 && index != 175 && index != 191 && index != 207 && index != 223 && index != 239 && index != 255) || OFFSET[direction] == -1 && index % 16 != 0)) {
					if (boardOneD[index + OFFSET[direction]] % 2 == 0 && boardOneD[index + OFFSET[direction]] != 0 || boardOneD[index] % 2 == 0 && boardOneD[index] != 0) {
						//cout << "On rencontre un mur " << endl;
						if ((OFFSET[direction] == -16 && checkUpMove(index, direction) || OFFSET[direction] == 16 && checkDownMove(index, direction) || OFFSET[direction] == -1 && checkLeftMove(index, direction) || OFFSET[direction] == 1 && checkRightMove(index, direction))) {
							//cout << "Ce mur ne gene pas pour aller a la destination " << endl;
							index += OFFSET[direction];
							if (moves[index] > depth) {
								moves[index] = depth;
								status[index] = true;
								done = false;
							}
						}
						else {
							//cout << "Un mur gene a " << index << " pour aller a " << direction << endl;
							break;
						}
					}
					else {
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
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "AFFICHAGE MOVES : " << std::endl;
	afficherMoves();
	std::cout << std::endl;

}

void Grid::deplacerRobot(color c, char dir) {
	Robot* rob = new Robot(0);
	for (int i = 0; i < 4; i++)
		if (tabRobots[i]->getColor() == c)
			rob = tabRobots[i];

	deplacerRobot(rob, dir);
}

void Grid::deplacerRobot(Robot* rob, char dir) {
	int xRob = (int)(rob->getPosition() / 16);
	int yRob = (int)(rob->getPosition() % 16);	int index;
	index = xRob * 16 + yRob;

	switch (dir)
	{
	case 'z':
		if (index > 15 && (boardOneD[index] != 17 && boardOneD[index] != 19 && boardOneD[index] != 21)) {
			bool continuer = true;
			while (continuer) {

				//Mur au Sud
				if (boardOneD[index - 16] == 8 || boardOneD[index - 16] == 10 || boardOneD[index - 16] == 12) {
					continuer = false;
				}
				//Mur au Nord et case vide
				else if ((boardOneD[index - 16] == 16 || boardOneD[index - 16] == 20 || boardOneD[index - 16] == 18) && boardOneD[index - 16] % 2 == 0) {
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
		if (index < 255 - 15 && (boardOneD[index] != 9 && boardOneD[index] != 13 && boardOneD[index] != 11)) {
			bool continuer = true;
			while (continuer) {

				//Mur au Nord
				if (boardOneD[index + 16] == 16 || boardOneD[index + 16] == 20 || boardOneD[index + 16] == 18) {
					continuer = false;
				}
				//Mur au Sud et case vide
				else if ((boardOneD[index + 16] == 8 || boardOneD[index + 16] == 12 || boardOneD[index + 16] == 10) && boardOneD[index + 16] % 2 == 0) {
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
		if (index % 16 != 0 && (boardOneD[index] != 3 && boardOneD[index] != 19 && boardOneD[index] != 11)) {
			bool continuer = true;
			while (continuer) {

				//Mur a l'Est
				if (boardOneD[index - 1] == 4 || boardOneD[index - 1] == 12 || boardOneD[index - 1] == 20) {
					continuer = false;
				}
				//Mur a l'Ouest et case vide
				else if ((boardOneD[index - 1] == 2 || boardOneD[index - 1] == 18 || boardOneD[index - 1] == 10) && boardOneD[index - 1] % 2 == 0) {
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
		if ((boardOneD[index] != 5 && boardOneD[index] != 21 && boardOneD[index] != 13)) {
			bool continuer = true;
			while (continuer) {

				//Mur a l'Ouest
				if (boardOneD[index + 1] == 2 || boardOneD[index + 1] == 18 || boardOneD[index + 1] == 10) {
					continuer = false;
				}
				//Mur a l'Est et case vide
				else if ((boardOneD[index + 1] == 4 || boardOneD[index + 1] == 20 || boardOneD[index + 1] == 12) && boardOneD[index + 1] % 2 == 0) {
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
			if (tabRobots[i]->getColor() == rob->getColor())
				tabRobots[i] = rob;

		if (rob->getTarget() && rob->getPosition() == goal)
			std::cout << "Fini !!!" << std::endl;

	}
}



unsigned int Grid::search(unsigned int depth, unsigned int maxDepth, std::vector <char>& path, std::map <unsigned int*, unsigned int> map) {
	nodes++;
	
	if (gameOver()) {
		return depth;// Gagné, en "depth" déplacements
	}
	if (depth == maxDepth) {// perdu
		return 0;
	}
	unsigned int remainingDepth = maxDepth - depth;

	if (moves[getRobotGoal()->getPosition()] > remainingDepth) {//Plus de déplacements que ce qu'il reste pour aller au goal
		return 0;
	}
	
	if (remainingDepth != 1 && !mapAdd(makeKey(), remainingDepth)) {//Si on n'a pas pu ajouter tel déplacement à la map
		hits++;
		return 0;
	}
	inner++;
	for (unsigned int robot = 0; robot < 4; robot++) {//Pour chaque robot
	
		if (robot && moves[tabRobots[numRobotTarget]->getPosition()] == remainingDepth) {
			continue;
		}
		for (unsigned int direction = 1; direction <= 8; direction <<= 1) {
			if (!canMove(robot, direction)) {
				continue;
			}			
		
			unsigned int* undo = doMove(robot, direction);
			unsigned int result = search(depth + 1, maxDepth, path, map);
			undoMove(undo);
			
			if (result){
				path.push_back(PACK_MOVE(robot, direction));
				return result;
			}
		}
	}
	return 0;
}



std::vector<std::string> Grid::principalSearch(std::vector <char>& path) {
	std::vector<std::string> pathSolution;
	pathSolution.clear();

	if (gameOver()) {
		return pathSolution;
	}
	unsigned int resultDepth = 0;
	std::map <unsigned int*, unsigned int> map;

	precomputeMinimumMoves();
	for (unsigned int maxDepth = 1; maxDepth < MAX_DEPTH; maxDepth++){ //Tant que l'on a pas réussi
		
		nodes = 0;
		hits = 0;
		inner = 0;

		resultDepth = search(0, maxDepth, path, map);
		
		pathSave(maxDepth, nodes, inner, hits);

		if (resultDepth) {//Si robotGoal à goal

			char c = ' ';
			char r = ' ';

			std::string k ="";

			for (int i = 0; i < path.size(); ++i) {
				std::cout << "path.size() : " << path.size() << std::endl;
				std::string etape = "";
				if (tabRobots[path[i] >> 4]->getColor() == blue) {
					k = "B";
					r = 'B';
				}
				else if (tabRobots[path[i] >> 4]->getColor() == red) {
					k ="R";
					r = 'R';
				}
				else if (tabRobots[path[i] >> 4]->getColor() == green) {
					k = "G";
					r = 'G';
				}
				else if (tabRobots[path[i] >> 4]->getColor() == yellow) {
					k = "Y";
					r = 'Y';
				}
				if ((path[i] & 0x0f) == NORTH) {
					k += "N";
					c = 'N';
				}
				else if ((path[i] & 0x0f) == EAST) {
					k += "E";
					c = 'E';
				}
				else if ((path[i] & 0x0f) == SOUTH) {
					k += "S";
					c = 'S';
				}
				else if ((path[i] & 0x0f) == WEST) {
					k += "O";
					c = 'O';
				}
				pathSolution.push_back(k);
				printf("\t\t%d- %c ->%c\n", i, r, c);

			}
		
			mapSearch.clear();
			std::cout << "map deleted" << std::endl;
			return pathSolution;

		}
	}	
	
}

void Grid::pathSave(unsigned int maxDepth, unsigned int nodes, unsigned int inner, unsigned int hits) {
	std::cout << maxDepth << " " << nodes << " " << inner << " " << hits << std::endl;
}

bool Grid::operator<(unsigned int keyCompare[4]) {
	int cpt = 0;

	for (int i = 0; i < 4; i++) {
		if (keyFound[i] < keyCompare[i]){
			cpt++;
		}
	}
	if (cpt == 4) {//On a trouve la meme cle
		return true;
	}
	return false;
}

bool Grid::mapAdd(std::vector<unsigned int> key, unsigned int d) {
	positionSorter(key);

	keyFound.clear();
	std::map<std::vector<unsigned int>, unsigned int>::iterator m = mapSearch.begin();
	bool found = 0;

	m = mapSearch.find(key);
	if (m != mapSearch.end()) {//Si la position existe ds la map
			
		found = 1;
		for (int i = 0; i < NB_ROBOTS; i++) {
			keyFound.push_back(key[i]);
		}
		if (m->second < d) {
		
			m->second = d;
			return true;
		}
		return false;
	}
	if (found == 0 || mapSearch.size() == 0) {
		mapSearch.emplace(key, d);
		return true;
	}
}

