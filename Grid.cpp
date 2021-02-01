#include "Grid.h"
#include <string>

using namespace std;

Grid::Grid() : depth(0), nodes(0), inner(0), hits(0), last(0) {

	for (int i = 0; i < 256; i++) {
		moves[i] = 0;
		boardOneD[i] = 0;
	}

	//srand(time(NULL));
	//tabRobots.clear();

	//int mursPossibles[] = { 16, 8, 4, 2, 20, 18, 12, 10 };
	//for (int i = 0; i < 256; i++) {
	//	if (rand() % 10 == 0){
	//		if ((int)i / 16 == 0 && i % 16 != 0)
	//			boardOneD[i] = 2;
	//		else if ((int)i / 16 == 0 && i % 16 == 0)
	//			boardOneD[i] = 4;
	//		else if ((int)i / 16 == 15 && i % 16 != 0)
	//			boardOneD[i] = 2;
	//		else if ((int)i / 16 == 15 && i % 16 == 0)
	//			boardOneD[i] = 4;
	//		else if ((int)i / 16 != 0 && i % 16 == 0)
	//			boardOneD[i] = 16;
	//		else if ((int)i / 16 == 0 && i % 16 == 0)
	//			boardOneD[i] = 8;
	//		else if ((int)i / 16 != 0 && i % 16 == 15)
	//			boardOneD[i] = 16;
	//		else if ((int)i / 16 == 0 && i % 16 == 15)
	//			boardOneD[i] = 8;
	//		else {
	//			if (rand() % 4 != 0)
	//				boardOneD[i] = mursPossibles[rand() % 4];
	//			else
	//				boardOneD[i] = mursPossibles[4 + (rand() % 4)];
	//		}
	//	}
	//	else {
	//		boardOneD[i] = 0;
	//	}
	//}

	//for (int i = 0; i < 4; i++) {
	//	rand();
	//	rand();
	//	int x = rand() % 256;
	//	if (boardOneD[x] % 2 == 0) {
	//		boardOneD[x]++;//Rajout d'un robot
	//		//Mettre le robot dans votre tableau
	//		tabRobots.push_back(new Robot(x));
	//	}
	//	else {
	//		i--;
	//	}
	//}
	//tabRobots[0]->setColor(blue);
	//tabRobots[1]->setColor(red);
	//tabRobots[2]->setColor(green);
	//tabRobots[3]->setColor(yellow);

	//numRobotTarget = rand() % 4;
	//tabRobots.at(numRobotTarget)->setTarget(true);
	//
	//goal = rand() % 256;
	//goal = rand() % 256;
	//goal = rand() % 256;
	//goal = rand() % 256;
	//cout << "Choix robot goal position: " << tabRobots.at(numRobotTarget)->getPosition() << endl;

	unsigned int liste[256] = {9, 1, 5, 1, 3, 9, 1, 1, 1, 3, 9, 1, 1, 1, 1, 3, 8, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 3, 8, 0, 0, 0, 0, 2, 12, 0, 2, 9, 0, 0, 0, 0, 4, 2, 12, 0, 0, 0, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 10, 9, 0, 0, 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 6, 8, 0, 0, 0, 0, 4, 4, 0, 0, 2, 12, 0, 0, 2, 8, 1, 0, 0, 0, 0, 2, 9, 3, 8, 0, 0, 1, 0, 0, 2, 8, 0, 4, 0, 2, 12, 2, 12, 6, 8, 0, 0, 0, 0, 0, 6, 8, 18, 9, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 4, 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9, 0, 2, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 0, 0, 0, 2, 9, 0, 0, 0, 4, 0, 0, 0, 0, 0, 1, 0, 0, 2, 12, 2, 8, 0, 0, 16, 3, 8, 0, 0, 0, 4, 0, 0, 0, 0, 1, 2, 8, 6, 8, 0, 0, 0, 0, 0, 0, 3, 8, 0, 0, 0, 16, 2, 12, 5, 4, 4, 4, 6, 12, 4, 4, 4, 4, 6, 12, 4, 4, 6};
	
	for (int i = 0; i < 256; i++){
		if (liste[i] == 1) {
			boardOneD[i] = 16;
		}
		if (liste[i] == 2)
			boardOneD[i] = 4;
		if (liste[i] == 4)
			boardOneD[i] = 8;
		if (liste[i] == 8)
			boardOneD[i] = 2;
		if (liste[i] == 9)
			boardOneD[i] = 18;
		if (liste[i] == 3)
			boardOneD[i] = 20;
		if (liste[i] == 6)
			boardOneD[i] = 12;
		if (liste[i] == 12)
			boardOneD[i] = 10;
		if (liste[i] == 0)
			boardOneD[i] = 0;
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
	numRobotTarget = rand() % 4;
	tabRobots.at(numRobotTarget)->setTarget(true);
}

void Grid::afficherMoves(){
	for (int i = 0; i < 256; i++) {	
		if (i != 0 && i % 16 == 0)
			cout << endl;
		if (moves[i] != INT_MAX) {
			cout << moves[i] << "\t";
		}
		else {
			cout << "pb" << "\t";
		}		
	}
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
	return tabRobots.at(numRobotTarget);
}

inline void Grid::swap(unsigned int* array, unsigned int a, unsigned int b) {
	unsigned int temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

inline unsigned int Grid::makeKey(){
	unsigned int tabRobotsCopy[4];//Tableau avec la position des robots
	//cout << "Robot avant : " << endl;
	for (int i = 0; i < 4; i++) {
		//cout << tabRobots[i]->getPosition() << endl;
	}

	for (int i = 0; i < NB_ROBOTS; i++) {
		tabRobotsCopy[i] = tabRobots.at(i)->getPosition();
	}

	if (tabRobots[1] > tabRobots[2]) {
		swap(tabRobotsCopy, 1, 2);
	}
	if (tabRobots[2] > tabRobots[3]) {
		swap(tabRobotsCopy, 2, 3);
	}
	if (tabRobots[1] > tabRobots[2]) {
		swap(tabRobotsCopy, 1, 2);
	}
		
	//cout << "Robot apres : " << endl;
	for (int i = 0; i < 4; i++) {
		//cout << tabRobotsCopy[i] << endl;
	}
	
	return MAKE_KEY(tabRobotsCopy);
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
	if (hasWall(index, direction)) {
		return false;
	}
	if (last == PACK_MOVE(robot, REVERSE[direction])) {
		return false;
	}
	//unsigned int newIndex = index + OFFSET[direction];
	if (hasRobot(index, direction)){
		return false;
	}
	return true;
}

bool Grid::hasWall(unsigned int index, unsigned int direction){
	if (index + OFFSET[direction] >= 0 && index + OFFSET[direction] < 256 && boardOneD[index + OFFSET[direction]] % 2 == 0 && boardOneD[index + OFFSET[direction]] != 0 || boardOneD[index] % 2 == 0 && boardOneD[index] != 0 && OFFSET[direction] == 16 && index < 240 || OFFSET[direction] == -16 && index > 15 || OFFSET[direction] == 1 && (index != 15 || index != 31 || index != 47 || index != 63 || index != 79 || index != 95 || index != 111 || index != 127 || index != 143 || index != 159 || index != 175 || index != 191 || index != 207 || index != 223 || index != 239 || index != 255) || OFFSET[direction] == -1 && index % 16 != 0) {
		if ((OFFSET[direction] == -16 && checkUpMove(index, direction) || OFFSET[direction] == 16 && checkDownMove(index, direction) || OFFSET[direction] == -1 && checkLeftMove(index, direction) || OFFSET[direction] == 1 && checkRightMove(index, direction))) {
			return false;
		}
	}
	return true;
}

bool Grid::hasRobot(unsigned int index, unsigned int direction) {
	if (boardOneD[index + OFFSET[direction]] == 1) {//S'il y a un robot
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

unsigned int tabMove[3];//0 :numRobot //1 start 2 : last

unsigned int* Grid::doMove(unsigned int robot, unsigned int direction) {
	//cout << "Nouveau mouvement : " << endl;
	
	unsigned int start = tabRobots.at(robot)->getPosition();//Position de départ du robot goal
	unsigned int end = computeMove(robot, direction);//position d'arrivée du robot goal
	//cout << "Robot goal part de " << start << " et arrive a " << end << endl;
	unsigned int lastMove = last;
	tabRobots.at(robot)->setPosition(end);
	last = PACK_MOVE(tabRobots.at(robot)->getPosition(), direction);
	UNSET_ROBOT(boardOneD[start]);
	SET_ROBOT(boardOneD[end]);
	tabMove[0] = robot;
	tabMove[1] = start;
	tabMove[2] = lastMove;

	return tabMove;
}



void Grid::undoMove(unsigned int* undo){
	/*unsigned int robot = UNPACK_ROBOT(undo);
	cout << "Robot= " << robot << endl;
	unsigned int start = UNPACK_START(undo);
	cout << "start= " << start << endl;
	unsigned int lastMove = UNPACK_LAST(undo);
	cout << "lastMove= " << lastMove << endl;*/
	
	unsigned int end = tabRobots[undo[0]]->getPosition();
	tabRobots[undo[0]]->setPosition(undo[1]);
	last = undo[2];
	SET_ROBOT(boardOneD[undo[1]]);
	UNSET_ROBOT(boardOneD[end]);
}

bool Grid::checkLeftMove(unsigned int index, unsigned int direction){
	if (boardOneD[index + OFFSET[direction]] != 4 && boardOneD[index + OFFSET[direction]] != 20 && boardOneD[index + OFFSET[direction]] != 12 && boardOneD[index]!= 2 && boardOneD[index] !=10 && boardOneD[index] !=18){
		//cout << "Aucun obstacle pour " << index << " pour aller a l'ouest " << endl;
		return true;
	}
	return false;
}

bool Grid::checkRightMove(unsigned int index, unsigned int direction) {
	if(boardOneD[index + OFFSET[direction]] != 2 && boardOneD[index + OFFSET[direction]] != 18 && boardOneD[index + OFFSET[direction]] != 10 && boardOneD[index]!= 4 && boardOneD[index] != 20 && boardOneD[index] != 12){
		//cout << "Aucun obstacle pour " << index << " pour aller a l'est " << endl;
		return true;
	}
	return false;
}

bool Grid::checkUpMove(unsigned int index, unsigned int direction) {
	if((boardOneD[index + OFFSET[direction]] != 8 && boardOneD[index + OFFSET[direction]] != 12 && boardOneD[index + OFFSET[direction]] != 10 && boardOneD[index] != 16 && boardOneD[index] != 18 && boardOneD[index] != 20)){
		//cout << "Aucun obstacle pour " << index << " pour aller au nord " << endl;
		return true;
	}
	return false;
}
bool Grid::checkDownMove(unsigned int index, unsigned int direction) {
	if((boardOneD[index + OFFSET[direction]] != 16 && boardOneD[index + OFFSET[direction]] != 20 && boardOneD[index + OFFSET[direction]] != 18 && boardOneD[index] != 8 && boardOneD[index] != 10 && boardOneD[index] != 12)){
		//cout << "Aucun obstacle pour " << index << " pour aller au sud " << endl;
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

			if (!status[i]) {
				continue;
			}

			status[i] = false;
			depth = moves[i] + 1;

			for (unsigned int direction = 0; direction < 4; direction++){
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
	cout << endl << endl << endl;
	cout << "AFFICHAGE MOVES : " << endl;
	afficherMoves();
	cout << endl;
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
			cout << "Fini !!!" << endl;

	}
}


unsigned int Grid::search(unsigned int depth, unsigned int maxDepth, vector <char> path, map <unsigned int*, unsigned int> map){
	/*cout << "--------------------------------------------------------------------------------" << endl;
	cout << "Nouvelle recherche : " << endl;*/

	nodes++;
	if (gameOver()) { 
		return depth;// Gagné, en "depth" déplacements
		cout << "Gagné " << endl;
	}
	if (depth == maxDepth) {// perdu
		//cout << "Perdu" << endl;
		return 0;
	}
	unsigned int remainingDepth = maxDepth - depth;
	/*cout << "Max depth : " << maxDepth << endl;
 	cout << "Remaining depth : " << remainingDepth << endl;
	cout << "Position robot goal " << getRobotGoal()->getPosition() << endl;
	cout << "Moves robot Goal " << moves[getRobotGoal()->getPosition()] << endl << endl;
	*/
	if (moves[getRobotGoal()->getPosition()] > remainingDepth) {//Plus de déplacements que ce qu'il reste pour aller au goal
		//cout << "Perdu 2 " << endl;
		return 0;
	}

	if (remainingDepth != 1 && !mapAdd(makeKey(), remainingDepth)) {//Si on n'a pas pu ajouter tel déplacement à la map
		hits++;
		return 0;
	}
	inner++;
	for (unsigned int robot = 0; robot < 4; robot++) {
		/*cout << "robot : " << robot << ",moves[tabRobots[numRobotTarget]->getPosition()] : " << moves[tabRobots[numRobotTarget]->getPosition()] << endl;
		cout << "= " << (robot && moves[tabRobots[numRobotTarget]->getPosition()]);
		cout << endl;*/
		if(robot && moves[tabRobots[numRobotTarget]->getPosition()] == remainingDepth){
			//cout << "Continue " << endl;
			continue;
		}
		for (unsigned int direction = 0; direction < 4; direction++){
			if (!canMove(robot, direction)){
				//cout << "Continue2" << endl;
				continue;
			}
			unsigned int* u = doMove(robot, direction);
			unsigned int tabUndo[3];
			for (int i = 0; i < 3; i++) {
				tabUndo[i] = u[i];
			}

			/*cout << "LE RESULTAT : " << endl;
			cout << "ROBOT : " << tabUndo[0] << endl;
			cout << "START : " << tabUndo[1] << endl;
			cout << "LAST : " << tabUndo[2] << endl;*/

			unsigned int result = search(depth + 1, maxDepth, path, map);	
			
			undoMove(tabUndo);
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
	for (unsigned int maxDepth = 1; maxDepth < MAX_DEPTH; maxDepth++){ //Tant que l'on a pas réussi
		depth = 0;
		nodes = 0;
		hits = 0;
		inner = 0;

		resultDepth = search(0, maxDepth, path, map);
		//if (pathSave()) {       //J'ai enlevé ça parce que pas booléen
			pathSave(maxDepth, nodes, inner, hits);
		//}
		if (resultDepth) {//Si robotGoal à goal
			break;
		}

	}
	
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

bool Grid::operator<(unsigned int key){	
	
	for (auto m : mapSearch) {
		if (m.first < key) {
			return true;
		}
	}
	return false;
}

bool Grid::mapAdd(unsigned int key, unsigned int remainingDepth){
	bool equal;
	pair<unsigned int, unsigned int> newElement;
	//cout << "Key : " << key << endl;
	
	for (auto m : mapSearch){
		equal = true;
		//On cherche si key existe déjà dans map
			if (key < m.first) {
				equal = false;
			}		
			if (equal) {
				if (m.second < remainingDepth){
					m.second = remainingDepth;
					//cout << "ON A TROUVE CETTE KEY DANS LA MAP " << endl;
					return true;
				}
				return false;
			}
		else {//Si key n'existe pas dans la map
			newElement.first = key;
			newElement.second = remainingDepth;
			mapSearch.insert(newElement);
			//cout << "ON A INSERT NEW ELEMENT DANS LA MAP " << endl;
			return true;
		}
	}
	if (mapSearch.size() == 0) {
		newElement.first = key;
		newElement.second = remainingDepth;
		mapSearch.insert(newElement);
		//cout << "ON A INSERT NEW ELEMENT DANS LA MAP parce que size = 0" << endl;
		return true;
	}
	
}

