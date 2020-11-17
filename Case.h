#pragma once
#include <iostream>

class Case {
private:
	int x, y;
	bool presenceRobot;
public:
	Case();
	Case(int, int);
	~Case();
	int getX();
	int getY();
};