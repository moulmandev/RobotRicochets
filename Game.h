#include "Grid.h"
#include "User.h"
#include "Robot.h"
#pragma once


class Game {
public:
	Game(User*,int, int);
	void displayGame();
private:
	Grid* map;
	User* users;
	Robot* robots;
	int nbRobots;
	int nbJoueurs;
};
