#include "Game.h"
using namespace std;

Game::Game(User* u, int nRobots, int nJoueurs) : nbRobots(nRobots), nbJoueurs(nJoueurs){
	users = u;
	robots = new Robot[nbRobots];//Creation tableau de robots
	map = new Grid(5, 5);
	std::cout << "Game created" << std::endl;
}

void Game::displayGame() {
	std::cout << "Liste joueurs : " << std::endl;
	cout << "nb joueurs : " << nbJoueurs << endl;
	for (int i = 0; i < nbJoueurs; i++) {
		std::cout << users[i].getLastName() << " " << users[i].getFirstName();
	}
	cout << endl;
}