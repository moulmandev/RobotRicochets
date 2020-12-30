#include "Grid.h"
#include "User.h"
#include "Robot.h"
#include "constants.h"
#include "Set.h"
#pragma once

const int MAX_DEPTH = 32;


class Game {
public:
	Game(User*,int, int);	
	inline bool gameOver();
	inline unsigned int make_key();
	inline void swap(unsigned int* array, unsigned int a, unsigned int b);
	void set_alloc(Set* set, unsigned int count);
	void set_free(Set* set, unsigned int count);
	void set_grow(Set* set);
	int hash(unsigned int key);
	bool set_add(Set* set, unsigned int key, unsigned int depth);
	void set_grow(Set* set);

protected:
	unsigned int Grid[256];
	unsigned int moves[256];
	unsigned int robots[4];
	unsigned int token;
	unsigned int last;
	User* users;
	int nbRobots;
	int nbJoueurs;
};
