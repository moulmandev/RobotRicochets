#pragma once

#include "Game.h"

class GameMultiPlayer : public Game {

private: 
	int nbJoueurs;

public:
	virtual void displayGame();

};
