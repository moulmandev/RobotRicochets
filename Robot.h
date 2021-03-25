#pragma once
#include <iostream>

enum color { blue = 0x009dff, red = 0xff0000, green = 0x149414, yellow = 0xfbd428};

class Robot {
private:
	color c;
	unsigned int position;
	bool target;
	bool focus = false;
public:
	Robot(unsigned int);
	const bool getTarget();
	const bool getFocus();
	const color getColor();
	void setColor(color);
	void setTarget(bool value);
	void setFocus(bool value);
	void setPosition(unsigned int);
	unsigned int getPosition();
	~Robot();

	Robot operator=(const Robot&);
	bool operator<(const Robot) const;
};