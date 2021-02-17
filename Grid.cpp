#include "Grid.h"
#include <string>
#include <fstream>

Grid::Grid() : depth(0), nodes(0), inner(0), hits(0), last(0) {

	for (int i = 0; i < 256; i++) {
		moves[i] = 0;
		boardOneD[i] = 0;
	}

	//mapSearch.clear();

	srand(time(NULL));
	tabRobots.clear();

	/*int mursPossibles[] = { 16, 8, 4, 2, 20, 18, 12, 10 };
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
		//Haut de la grille
		else if (i <= 15) {
			boardOneD[i] = 16;
		}
		//Bas de la grille
		else if (i >= 255 - 15) {
			boardOneD[i] = 8;
		}
		//Gauche de la grille
		else if (i % 16 == 0) {
			boardOneD[i] = 2;
		}
		//Droite de la grille
		else if (i == 15 || i == 31 || i == 47 || i == 63 || i == 79 || i == 95 || i == 111 || i == 127 || i == 143 || i == 159 || i == 175 || i == 191 || i == 207 || i == 223 || i == 239 || i == 255) {
			boardOneD[i] = 4;
		}

		if (rand() % 4 == 0 && !(i <= 15 || i >= 255 - 15 || i % 16 == 0 || (i == 15 || i == 31 || i == 47 || i == 63 || i == 79 || i == 95 || i == 111 || i == 127 || i == 143 || i == 159 || i == 175 || i == 191 || i == 207 || i == 223 || i == 239 || i == 255)) ){
			
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

	numRobotTarget = rand() % 4;
	tabRobots.at(numRobotTarget)->setTarget(true);
	
	goal = rand() % 256;
	goal = rand() % 256;
	goal = rand() % 256;
	goal = rand() % 256;
	cout << "Choix robot goal position: " << tabRobots.at(numRobotTarget)->getPosition() << endl;*/

	unsigned int liste[256] = {9, 1, 5, 1, 3, 9, 1, 1, 1, 3, 9, 1, 1, 1, 1, 3, 8, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 3, 8, 0, 0, 0, 0, 2, 12, 0, 2, 9, 0, 0, 0, 0, 4, 2, 12, 0, 0, 0, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 10, 9, 0, 0, 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 6, 8, 0, 0, 0, 0, 4, 4, 0, 0, 2, 12, 0, 0, 2, 8, 1, 0, 0, 0, 0, 2, 9, 3, 8, 0, 0, 1, 0, 0, 2, 8, 0, 4, 0, 2, 12, 2, 12, 6, 8, 0, 0, 0, 0, 0, 6, 8, 18, 9, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 4, 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9, 0, 2, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 0, 0, 0, 2, 9, 0, 0, 0, 4, 0, 0, 0, 0, 0, 1, 0, 0, 2, 12, 2, 8, 0, 0, 16, 3, 8, 0, 0, 0, 4, 0, 0, 0, 0, 1, 2, 8, 6, 8, 0, 0, 0, 0, 0, 0, 3, 8, 0, 0, 0, 16, 2, 12, 5, 4, 4, 4, 6, 12, 4, 4, 4, 4, 6, 12, 4, 4, 6};

	for (int i = 0; i < 256; i++){
		if (liste[i] == NORTH) {
			boardOneD[i] = 16;
		}
		if (liste[i] == EAST)
			boardOneD[i] = 4;
		if (liste[i] == SOUTH)
			boardOneD[i] = 8;
		if (liste[i] == WEST)
			boardOneD[i] = 2;
		if (liste[i] == WEST + NORTH)
			boardOneD[i] = 18;
		if (liste[i] == WEST + SOUTH)
			boardOneD[i] = 10;
		if (liste[i] == EAST + NORTH)
			boardOneD[i] = 20;
		if (liste[i] == EAST + SOUTH)
			boardOneD[i] = 12;		
		if (liste[i] == NORTH + SOUTH) {
			boardOneD[i] = 24;
		}
		if (liste[i] == EAST + WEST){
			boardOneD[i] = 6;
		}
		if (liste[i] == 0) {
			boardOneD[i] = 0;
		}

		if (liste[i] >= 16){
			if (liste[i] == 16) {
				boardOneD[i] = 0;//Juste un robot
			}

			else {//Un robot + un mur
				int k = liste[i] % 16;
				if (k == NORTH) {
					boardOneD[i] = 16;
				}
				if (k == EAST)
					boardOneD[i] = 4;
				if (k == SOUTH)
					boardOneD[i] = 8;
				if (k == WEST)
					boardOneD[i] = 2;
				if (k == WEST + NORTH)
					boardOneD[i] = 18;
				if (k == EAST + NORTH)
					boardOneD[i] = 20;
				if (k == EAST + SOUTH)
					boardOneD[i] = 12;
				if (k == WEST + SOUTH)
					boardOneD[i] = 10;
			}

			
		}
	}

	tabRobots.push_back(new Robot(176));
	boardOneD[176]++;
	tabRobots.push_back(new Robot(145));
	boardOneD[145]++;
	tabRobots.push_back(new Robot(211));
	boardOneD[211]++;
	tabRobots.push_back(new Robot(238));
	boardOneD[238]++;

	tabRobots[0]->setColor(blue);
	tabRobots[1]->setColor(red);
	tabRobots[2]->setColor(green);
	tabRobots[3]->setColor(yellow);

	goal = 54;
	last = 0;
	numRobotTarget = 0;
	tabRobots.at(numRobotTarget)->setTarget(true);

	std::sort(tabRobots.begin() + 1, tabRobots.begin() + 4);

	printf("Case 208 : ");
	printf("%d\n", boardOneD[208]);
	printf("Case haut 192 : ");
	printf("%d\n", boardOneD[192]);

	afficherGrille();
	std::cout << std::endl;
	
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
			
			else {
				for (int j = 0; j < 4; j++) {
					if (tabRobots[j]->getPosition() == i - 1) {
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
		if (i != 0 && i % 16 == 0)
			std::cout << std::endl;
	}
	
}


Robot* Grid::getRobotGoal() {
	return tabRobots.at(numRobotTarget);
}

inline void Grid::swap(unsigned int* array, unsigned int a, unsigned int b) {
	unsigned int temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

std::vector<unsigned int> Grid::makeKey(){
	unsigned int robots[4];
	std::vector<unsigned int> tabRobotsCopy;

	for (int i = 0; i < NB_ROBOTS; i++) {
		tabRobotsCopy.push_back(tabRobots[i]->getPosition());
	}
	//std::sort(tabRobotsCopy.begin()+1, tabRobotsCopy.begin()+4);

	//unsigned int tabRobotsCopy[4] = {tabRobots[0]->getPosition(), tabRobots[1]->getPosition(), tabRobots[2]->getPosition(), tabRobots[3]->getPosition()};

	//memcpy(robots, tabRobotsCopy, sizeof(unsigned int) * 4);//Tirer robots dans l'ordre
	/*if (robots[1] > robots[2]) {
		swap(robots, 1, 2);
	}
	if (robots[2] > robots[3]) {
		swap(robots, 2, 3);
	}
	if (robots[1] > robots[2]) {
		swap(robots, 1, 2);
	}*/

	//return MAKE_KEY(robots);
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
	//cout << "l'index 176 vaut : " << boardOneD[176] << endl;
	if (hasWall(index, direction)) {//S'il y a un mur
		return false;
	}	
	if (last == PACK_MOVE(robot, REVERSE[direction])){
		return false;
	}
	if (hasRobot(index, direction)){//S'il y a un robot
		return false;
	}
	return true;

}

unsigned int* Grid::getPrecomputeMinimumMovesArray() {
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
	if (boardOneD[index + OFFSET[direction]] == 176 || boardOneD[index + OFFSET[direction]] == 145 || boardOneD[index + OFFSET[direction]] == 211 || boardOneD[index + OFFSET[direction]] == 238) {//S'il y a un robot
		return true;
	}
	return false;
}

unsigned int Grid::computeMove(unsigned int robot, unsigned int direction) {//Regarde si déplacement possible
	unsigned int index = tabRobots.at(robot)->getPosition() + OFFSET[direction];
	while (true) {
		if (hasWall(index, direction)){
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

unsigned int packMove(unsigned int robot, unsigned int direction){
	return robot<<4 | direction;
}

unsigned int* Grid::doMove(unsigned int robot, unsigned int direction) {
		
	unsigned int start = tabRobots.at(robot)->getPosition();//Position de départ du robot goal
	unsigned int end = computeMove(robot, direction);//position d'arrivée du robot goal	
	unsigned int lastMove = last;
	tabRobots.at(robot)->setPosition(end);
	last = PACK_MOVE(robot, direction);

	setRobot(start);
	unsetRobot(end);
	/*UNSET_ROBOT(boardOneD[start]);
	SET_ROBOT(boardOneD[end]);*/

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
	setRobot(start);
	unsetRobot(end);
	//SET_ROBOT(boardOneD[start]);
	//UNSET_ROBOT(boardOneD[end]);
}

bool Grid::checkLeftMove(unsigned int index, unsigned int direction){
	
	if (boardOneD[index + OFFSET[direction]] != 4 && boardOneD[index + OFFSET[direction]] != 20 && boardOneD[index + OFFSET[direction]] != 12 && boardOneD[index]!= 2 && boardOneD[index] !=10 && boardOneD[index] !=18){
		return true;
	}
	return false;
}

bool Grid::checkRightMove(unsigned int index, unsigned int direction) {
	if(boardOneD[index + OFFSET[direction]] != 2 && boardOneD[index + OFFSET[direction]] != 18 && boardOneD[index + OFFSET[direction]] != 10 && boardOneD[index]!= 4 && boardOneD[index] != 20 && boardOneD[index] != 12){
		return true;
	}
	return false;
}


bool Grid::checkUpMove(unsigned int index, unsigned int direction) {

	if((boardOneD[index + OFFSET[direction]] != 8 && boardOneD[index + OFFSET[direction]] != 12 && boardOneD[index + OFFSET[direction]] != 10 && boardOneD[index] != 16 && boardOneD[index] != 18 && boardOneD[index] != 20)){
		return true;
	}
	return false;
}

bool Grid::checkDownMove(unsigned int index, unsigned int direction) {
	if((boardOneD[index + OFFSET[direction]] != 16 && boardOneD[index + OFFSET[direction]] != 20 && boardOneD[index + OFFSET[direction]] != 18 && boardOneD[index] != 8 && boardOneD[index] != 10 && boardOneD[index] != 12)){
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
		for (unsigned int i = 0; i < 256; i++){

			if (!status[i]){
				continue;
			}

			status[i] = false;
			depth = moves[i] + 1;

			for (unsigned int direction = 1; direction <= 8; direction <<= 1) {
				unsigned int index = i;
				while (index + OFFSET[direction] >= 0 && index + OFFSET[direction] < 256 && (OFFSET[direction] == 16 && index < 240 || OFFSET[direction] == -16 && index > 15 || OFFSET[direction] == 1 && (index != 15 && index != 31 || index != 47 && index != 63 && index != 79 && index != 95 && index != 111 && index != 127 && index != 143 && index != 159 && index != 175 && index != 191 && index != 207 && index != 223 && index != 239 && index != 255) || OFFSET[direction] == -1 && index % 16 != 0)) {
					if (boardOneD[index + OFFSET[direction]] % 2 == 0 && boardOneD[index + OFFSET[direction]]!=0 || boardOneD[index]%2 == 0 && boardOneD[index]!=0){
						//cout << "On rencontre un mur " << endl;
						if ((OFFSET[direction] == -16 && checkUpMove(index, direction) || OFFSET[direction] == 16 && checkDownMove(index, direction) || OFFSET[direction] == -1 && checkLeftMove(index, direction) || OFFSET[direction] == 1 && checkRightMove(index, direction))){
						//cout << "Ce mur ne gene pas pour aller a la destination " << endl;
							index += OFFSET[direction];
								if (moves[index] > depth){
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
					else{
						index += OFFSET[direction];
						if (moves[index] > depth){
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

void Grid::deplacerRobot(color c, char dir){
	Robot* rob = new Robot(0);
	for (int i = 0; i < 4; i++)
		if (tabRobots[i]->getColor() == c)
			rob = tabRobots[i];

	int xRob = (int)(rob->getPosition() / 16);
	int yRob = (int)(rob->getPosition() % 16);	int index;
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
				else if (boardOneD[index - 16] == 16 && boardOneD[index - 16] % 2 == 0){
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
				else if (boardOneD[index - 16] % 2 != 0){
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
				else if (boardOneD[index + 1] == 4 && boardOneD[index + 1] % 2 == 0){
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
			std::cout << "Fini !!!" << std::endl;

	}
}



unsigned int Grid::search(unsigned int depth, unsigned int maxDepth, std::vector <char> path, std::map <unsigned int*, unsigned int> map) {
	
	printf("Case 208 : ");
	printf("%d\n", boardOneD[208]);
	/*cout << "--------------------------------------------------------------------------------" << endl;
	cout << "Nouvelle recherche : " << endl;*/

	nodes++;
	
	/*printf("nodes : ");
	printf("%d\n", nodes);*/
	if (gameOver()) {
		return depth;// Gagné, en "depth" déplacements
		std::cout << "Gagné " << std::endl;
	}
	if (depth == maxDepth) {// perdu
		//cout << "Perdu" << endl;
		return 0;
	}
	unsigned int remainingDepth = maxDepth - depth;

	if (moves[getRobotGoal()->getPosition()] > remainingDepth) {//Plus de déplacements que ce qu'il reste pour aller au goal
		//cout << "Perdu 2 " << endl;
		return 0;
	}

	if (remainingDepth != 1 && !mapAdd(makeKey(), remainingDepth)) {//Si on n'a pas pu ajouter tel déplacement à la map
		hits++;
		return 0;
	}
	inner++;
	for (unsigned int robot = 0; robot < 4; robot++) {//Pour chaque robot
		/*printf("robot :");
		printf("%d\n", robot);*/

		if (robot && moves[tabRobots[numRobotTarget]->getPosition()] == remainingDepth) {
			continue;
		}
		for (unsigned int direction = 1; direction <= 8; direction <<= 1) {
			if (!canMove(robot, direction)) {
				//cout << "Continue2" << endl;
				continue;
			}
			
			/*printf("On appelle doMove\n");
			printf("robot : ");
			printf("%d", robot);
			printf(", direction : ");
			printf("%d\n", direction);*/

			unsigned int* undo = doMove(robot, direction);
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
	std::map <unsigned int*, unsigned int> map;

	precomputeMinimumMoves();
	for (unsigned int maxDepth = 1; maxDepth < MAX_DEPTH; maxDepth++){ //Tant que l'on a pas réussi

		depth = 0;
		nodes = 0;
		hits = 0;
		inner = 0;

		resultDepth = search(0, maxDepth, path, map);
		//if (pathSave()) {       //J'ai enlevé ça parce que pas booléen
		//cout << "pathSave a " << "maxDepth : " << maxDepth << "nodes : " << nodes << " inner : " << inner << " hits : " << hits << endl;
			pathSave(maxDepth, nodes, inner, hits);
		//}
		if (resultDepth) {//Si robotGoal à goal
			break;
		}

	}
	
	//mapSearch.clear();
	std::cout << "map deleted" << std::endl;
	return resultDepth;
	return 0;
}

void Grid::pathSave(unsigned int maxDepth, unsigned int nodes, unsigned int inner, unsigned int hits) {
	//cout << "maxDepth: " << demaxDepthpth << ",Nodes: " << nodes << "(" << inner << "inner," << hits << "hits)" << endl;
	//printf("new path : \n");
	printf("%u %u %u %u\n", maxDepth, nodes, inner, hits);
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

int cpt = 0;
bool Grid::mapAdd(std::vector<unsigned int> key, unsigned int d){
	cpt++;
	//printf("%d\n", cpt);
	keyFound.clear();
	std::pair<std::vector<unsigned int>, unsigned int> p;
	std::map<std::vector<unsigned int>, unsigned int>::iterator m = mapSearch.begin();
	bool found = 0;
	
	while(m!=mapSearch.end()){
		//std::cout << "Map = " << m->first[0] << ", " << m->first[1] << ", " << m->first[2] << ", " << m->first[3] << std::endl;
		if (m->first == key) {//Si la position existe ds la map
			//printf("okk ==\n");
			found = 1;
			//printf("Found\n");
			for (int i = 0; i < NB_ROBOTS; i++) {
				keyFound.push_back(key[i]);
			}
			/*printf("d : ");
			printf("%d\n", d);
			printf("m->second : ");
			printf("%d\n", m->second);*/
			if (m->second < d) {//Si nouvelle distance restante meilleure que l'ancienne				
				//printf("depth inferieure\n");
				m->second = d;
				return true;
			}
			return false;
		}		
		m++;
	}

	if(found==0 || mapSearch.size() == 0){
		//printf("Pas egal\n");
		p.first = key;
		p.second = d;
		mapSearch.insert(p);
		return true;
	}
}

