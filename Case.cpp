#include "Case.h"

using namespace std;

Case::Case(): x(-1), y(-1), presenceRobot(false){
	robot = nullptr;
}

Case::Case(int coord1, int coord2, char m) : x(coord1), y(coord2), mur(m), presenceRobot(false) {
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

char Case::getMur()
{
	return mur;
}

bool Case::getPresenceRobot() {
	return presenceRobot;
}

void Case::ajouterRobot(Robot* r) {
	presenceRobot = true;
	robot = r;
}
