#pragma once
#include <iostream>

enum color {blue, red, green, yellow, purple, pink, black, cyan};

class Robot {
private:
	color c;
	unsigned int position;
	bool target;
public:
	Robot(unsigned int);
	const bool getTarget();
	const color getColor();
	void setColor(color);
	void setTarget(bool);
	void setPosition(unsigned int);
	unsigned int getPosition();
	~Robot();

	Robot operator=(const Robot&);
	bool operator<(const Robot) const;
};