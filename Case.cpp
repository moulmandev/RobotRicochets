#include "Case.h"

using namespace std;

Case::Case(): x(-1), y(-1), presenceRobot(false){
	robot = nullptr;
}

Case::Case(int coord1, int coord2) : x(coord1), y(coord2), presenceRobot(false) {
	robot = nullptr;
}

Case::~Case() {
	;
}

int Case::getX() {
	return x;
}

int Case::getY() {
	return y;
}

bool Case::getPresenceRobot() {
	return presenceRobot;
}

void Case::ajouterRobot(Robot* r) {
	presenceRobot = true;
	robot = r;
}
