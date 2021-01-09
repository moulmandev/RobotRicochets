#include "Robot.h"
#include <ctime>


using namespace std;


Robot::Robot(int k): position(k){
	srand(time(NULL));
	c = (color)(rand() % 8);
	target = false;
	cout << "Robot created";
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


void Robot::setTarget(bool b){
	target = b;
}


Robot::~Robot() {
	;
}



