#include "Robot.h"
#include <ctime>


using namespace std;


Robot::Robot(int k, int v): x(k), y(v){
	srand(time(NULL));
	c = (color)(rand() % 8);
	target = false;
	cout << "Robot created";
}

bool Robot::getTarget() {
	return target;
}

int Robot::getX() {
	return x;
}

int Robot::getY() {
	return y;
}

void Robot::setXY(int k, int v) {
	x = k;
	y = v;
}

void Robot::setX(int k) {
	x = k;
}
void Robot::setY(int v) {
	y = v;
}

void Robot::setTarget(bool b){
	target = b;
}


Robot::~Robot() {
	;
}



