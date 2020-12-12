#include "Game.h"
#include <time.h>
using namespace std;

Game::Game(User* u, int nRobots, int nJoueurs) : nbRobots(nRobots){
	users = u;
	robots = new Robot[nbRobots];//Creation tableau de robots
	GenerateBoard(5, 5, nRobots, robots);
	std::cout << "Game created" << std::endl;
}

void Game::GenerateBoard(int nbRow, int nbCol, int nbRobots, Robot tabRobots[]) {
	map = new Grid(nbCol, nbRow);
	int l,c = 0;
	srand(time(NULL));
	for (int i = 0; i < nbRobots; i++) {
		l = rand() %(map->getNbRow());
		c = rand() % (map->getNbCol());
		if (map->getCase(l, c)->getPresenceRobot()){
			i--;
		}
		else {			
			map->getCase(l, c)->ajouterRobot(&tabRobots[i]);
		}
	}
	cout << "Board generated " << endl;
}

void Game::drawBoard() {
	for (int i = 0; i < map->getNbRow(); i++) {
		for (int j = 0; j < map->getNbCol(); j++) {			
			if (map->getCase(i, j)->getPresenceRobot()) {
				cout << "Robot dans la case : " << i << "," <<j ;
			}		
		}
		cout << endl;
	}
	bool PresenceRobot;
	for (int i = 0; i < map->getNbRow(); i++) {
		
		for (int j = 0; j < map->getNbCol(); j++) {
			cout << "* * * * * * *";		
		}	
		for (int k = 0; k < 5; k++) {
			cout << endl;
			for(int j=0; j< map->getNbCol()+1;j++){
				if (k == 2 && j<map->getNbCol()){
					if (map->getCase(i, j)->getPresenceRobot()) {
						cout << "  R  ";
					}

				}	
				else {
					cout << "*            ";
				}
				
			}
			
		}
		
		cout << endl;
				
		
	}
	for (int j = 0; j < map->getNbCol(); j++) {
		cout << "* * * * * * *";
	}
	cout << endl;
}

/*void Game::gameInformation() {
	std::cout << "Liste joueurs : " << std::endl;
	cout << "nb joueurs : " << nbJoueurs << endl;
	for (int i = 0; i < nbJoueurs; i++) {
		std::cout << users[i].getLastName() << " " << users[i].getFirstName();
	}
	cout << endl;
}*/