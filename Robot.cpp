#include "Robot.h"
#include <ctime>



using namespace std;


Robot::Robot(unsigned int k): position(k){
	srand(time(NULL));
	c = (color)(rand() % 8);
}

const bool Robot::getTarget() {
	return target;
}

unsigned int Robot::getPosition() {
	return position;
}


void Robot::setPosition(unsigned int k) {
	position = k;
}
void Robot::setColor(color col)
{
	c = col;
}

const color Robot::getColor()
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

bool Robot::operator<(const Robot r) const {
	if (this->position < r.position) {
		return true;
	}
	return false;
}



