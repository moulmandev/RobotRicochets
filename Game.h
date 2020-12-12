#include "Grid.h"
#include "User.h"
#include "Robot.h"
#pragma once


class Game {
public:
	Game(User*,int, int);
	void GenerateBoard(int nbRow,int nbCol, int nbRobots, Robot tabRobots[]);
	void GameInformation();
	void drawBoard();
protected:
	Grid* map;
	User* users;
	Robot* robots;
	int nbRobots;
};
