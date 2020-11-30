#pragma once
#include <iostream>

enum color { blue, red, green, yellow, purple, pink, black, cyan };

class Robot {
private:
	color c;
public:
	Robot();
	Robot(color);
	~Robot();
};