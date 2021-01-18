#include "Robot.h"
#include <ctime>


using namespace std;


Robot::Robot(int k) : position(k) {
	srand(time(NULL));
	c = (color)(rand() % 8);
}

bool Robot::getTarget() {
	return target;
}

int Robot::getPosition() {
	return position;
}

void Robot::setPosition(int k) {
	position = k;
}
void Robot::setColor(color col)
{
	c = col;
}

color Robot::getColor()
{
	return c;
}


void Robot::setTarget(bool b){
	target = b;
}


Robot::~Robot() {
	;
}

Robot Robot::operator=(const Robot& rob)
{
	if (&rob != this) {
		this->c = rob.c;
		this->target = rob.target;
		this->position = rob.position;
	}
	return *this;
}



