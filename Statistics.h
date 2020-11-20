#pragma once
#include <iostream>
class Statistics {
public:
	Statistics();
	
	int getgameNb();
	int getWonGameNb();
	double getRatio();
	
	void setgameNb(int);
	void setWonGameNb(int);
	void SetRatio(float);

	void displayStatistics();
	double calculRatio();

	~Statistics();

private:
	int gameNb;
	int wonGameNb;
	double ratio;
};
