#pragma once
#include "User.h"

class Statistics {
public:
	Statistics(User*);
	
	int getgameNb();
	int getWonGameNb();
	double getRatio();
	
	void setgameNb(int);
	void setWonGameNb(int);
	void SetRatio(float);

	double calculRatio();
	~Statistics();

private:
	User* user;
	int gameNb;
	int wonGameNb;
	double ratio;
};
