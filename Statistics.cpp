#include "Statistics.h"

Statistics::Statistics(User* u): gameNb(0), wonGameNb(0), ratio(1.0){
	user = u;
	std::cout << "Constructeur Statistiques" << std::endl;
}

int Statistics::getgameNb() {
	return gameNb;
}
int Statistics::getWonGameNb() {
	return wonGameNb;
}
double Statistics::getRatio() {
	return ratio;
}

void Statistics::setgameNb(int nb) {
	gameNb = nb;
}
void Statistics::setWonGameNb(int nb) {
	wonGameNb = nb;
}
void Statistics::SetRatio(float r) {
	ratio = r;
}

double Statistics::calculRatio() {
	return wonGameNb/(gameNb - wonGameNb);
}

Statistics::~Statistics() {
	std::cout << "statistics Destructor" << std::endl;
}