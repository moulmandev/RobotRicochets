#pragma once
#include <iostream>
#include "Robot.h"

class Case {
private:
	int x, y;
	bool presenceRobot;
	Robot* robot;
public:
	Case();
	Case(int, int);
	~Case();
	int getX();
	int getY();
	bool getPresenceRobot();
	void ajouterRobot(Robot*);
};