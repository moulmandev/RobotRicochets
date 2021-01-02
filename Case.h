#pragma once
#include <iostream>
#include "Robot.h"

class Case {
private:
	int x, y;
	bool presenceRobot;
	char mur;
	Robot* robot;
public:
	Case();
	Case(int, int, char);
	~Case();
	int getX();
	int getY();
	char getMur();
	bool getPresenceRobot();
	void ajouterRobot(Robot*);
};