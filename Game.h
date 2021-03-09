#include "Grid.h"
#include "User.h"
#include "Robot.h"
#include "constants.h"
#pragma once


class Game {
public:
	Game(User*, int, int);
	Grid* getMap();
	void gameVue();

protected:
	unsigned int* robots;
	unsigned int token;
	unsigned int last;
	User* users;
	Grid* map;
	int nbRobots;
	int nbJoueurs;
};
