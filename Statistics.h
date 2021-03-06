#pragma once

#include <Wt/Dbo/Dbo.h>

#include <iostream>

namespace dbo = Wt::Dbo;

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

	template<class Action>
	void persist(Action& a)
	{
		dbo::field(a, gameNb, "gameNb");
		dbo::field(a, wonGameNb, "wonGameNb");
		dbo::field(a, ratio, "ratio");
	};

	~Statistics();

private:
	int idStatistics;
	int idUser;
	int gameNb;
	int wonGameNb;
	double ratio;
};
