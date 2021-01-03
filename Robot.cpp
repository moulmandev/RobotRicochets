#include "Robot.h"

using namespace std;
Robot::Robot() : c(blue){
	cout << "Robot created" << endl;
	target = false;
}

Robot::Robot(color col) : c(col){
	;
}

Robot::~Robot() {
	;
}


