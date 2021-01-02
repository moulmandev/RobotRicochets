#include "Grid.h"
#include "User.h"
#include "Robot.h"
#include "constants.h"
#include "Set.h"
#pragma once


class Game {
public:
	Game(User*, Robot*, int, int);
	void gameVue();

	/*inline bool gameOver();
	inline unsigned int make_key();
	inline void swap(unsigned int* array, unsigned int a, unsigned int b);
	void set_alloc(Set* set, unsigned int count);
	void set_free(Set* set, unsigned int count);
	void set_grow(Set* set);
	int hash(unsigned int key);
	bool set_add(Set* set, unsigned int key, unsigned int depth);
	bool can_move(unsigned int robot, unsigned int direction);
	unsigned int do_move(unsigned int robot, unsigned int direction);
	void undo_move(unsigned int undo);
	void precompute_minimum_moves();
	unsigned int compute_move(unsigned int robot, unsigned int direction);*/

protected:
	User* users;
	Grid* map;
	Robot* robots;
	int nbRobots;
	int nbJoueurs;
};
