#pragma once
#include <iostream>

enum color { blue, red, green, yellow, purple, pink, black, cyan };

class Robot {
private:
	color c;
	int x;
	int y;
	bool target;
public:
	Robot(int x, int y);
	bool getTarget();
	void setX(int);
	void setY(int);
	void setTarget(bool);
	void setXY(int, int);
	int getX();
	int getY();
	~Robot();
};