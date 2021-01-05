#include "Grid.h"
#include "User.h"
#include "Robot.h"
#include "constants.h"
#pragma once


class Game {
public:
	Game(User*, int, int);
	void gameVue();
	

protected:
	User* users;
	Grid* map;
	int nbRobots;
	int nbJoueurs;
};
