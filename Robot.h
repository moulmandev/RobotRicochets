#pragma once
#include <iostream>

enum color { blue, red, green, yellow, purple, pink, black, cyan };

class Robot {
private:
	color c;
	int position;
	bool target;
public:
	Robot(int x);
	bool getTarget();
	void setTarget(bool);
	void setPosition(int);
	int getPosition();
	void setColor(color);
	color getColor();
	~Robot();

	Robot operator=(const Robot&);
};