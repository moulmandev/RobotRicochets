#include "Statistics.h"

Statistics::Statistics(): gameNb(0), wonGameNb(0), ratio(0.0){
	std::cout << "Statistics Constructor" << std::endl;
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

void Statistics::displayStatistics() {
	std::cout << "Nombre de parties jouees : " << gameNb << std::endl;
	std::cout << "Nombre de parties gagnees : " << wonGameNb << std::endl;
	std::cout << "Nombre de parties perdues : " << gameNb- wonGameNb << std::endl;
	std::cout << "Ratio du joueur : " << ratio << std::endl;

}

Statistics::~Statistics() {
	std::cout << "statistics Destructor" << std::endl;
}