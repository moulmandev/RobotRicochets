#include "Game.h"
#include <time.h>
using namespace std;

Game::Game(User* u, int nRobots, int nJoueurs) : nbRobots(nRobots), nbJoueurs(nJoueurs){
	users = u;
	map = new Grid();
	std::cout << "Game created" << std::endl;
}

void Game::gameVue() {
	map->afficherGrille();
	cout << endl << endl;
	cout << "nb joueurs : " << nbJoueurs << endl;
	std::cout << "Liste joueurs : " << std::endl;

	for (int i = 0; i < nbJoueurs; i++) {
		std::cout << "-" << users[i].getLastName() << " " << users[i].getFirstName() << endl;
	}
	cout << endl;	
}

unsigned int nodes;
unsigned int hits;
unsigned int inner;


/*inline void swap(unsigned int* array, unsigned int a, unsigned int b) {
	unsigned int temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

inline unsigned int Game::make_key() {
	unsigned int robots[4];
	memcpy(robots, robots, sizeof(unsigned int) * 4);
	if (robots[1] > robots[2]) {
		swap(robots, 1, 2);
	}
	if (robots[2] > robots[3]) {
		swap(robots, 2, 3);
	}
	if (robots[1] > robots[2]) {
		swap(robots, 1, 2);
	}
	return MAKE_KEY(robots);
}

int Game::hash(unsigned int key){
	key = ~key + (key << 15);
	key = key ^ (key >> 12);
	key = key + (key << 2);
	key = key ^ (key >> 4);
	key = key * 2057;
	key = key ^ (key >> 16);
	return key;
}

void Game::set_alloc(Set* set, unsigned int count) {
	for (unsigned int i = 0; i < count; i++) {
		set->setMask(0xfff);
		set->setSize(0);
		set->setData((Entry*)calloc(set->getMask() + 1, sizeof(Entry)));
		set++;
	}
}

void Game::set_free(Set* set, unsigned int count) {
	for (unsigned int i = 0; i < count; i++) {
		free(set->getData());
		set++;
	}
}

void Game::set_grow(Set* set) {
	Set new_set;
	new_set.setMask((set->getMask() << 2) | 3);
	new_set.setSize(0);
	new_set.setData((Entry*)calloc(new_set.getMask() + 1, sizeof(Entry)));
	for (unsigned int index = 0; index <= set->getMask(); index++) {
		Entry* entry = set->getData() + index;
		if (entry->getKey()) {
			set_add(&new_set, entry->getKey(), entry->getDepth());
		}
	}
	free(set->getData());
	set->setMask(new_set.getMask());
	set->setSize(new_set.getSize());
	set->setData(new_set.getData());
}

bool Game::set_add(Set* set, unsigned int key, unsigned int depth) {
	unsigned int index = hash(key) & set->getMask();
	Entry* entry = set->getData() + index;
	while (entry->getKey() && entry->getKey() != key) {
		index = (index + 1) & set->getMask();
		entry = set->getData() + index;
	}
	if (entry->getKey()) {
		if (entry->getDepth() < depth){
			entry->setDepth(depth);
			return true;
		}
		return false;
	}
	else {
		entry->setKey(key);
		entry->setDepth(depth);
		set->setSize(set->getSize()+1);
		if (set->getSize() * 2 > set->getMask()) {
			set_grow(set);
		}
		return true;
	}
}

inline bool Game::gameOver() {
	if (robots[0] == token) {
		return true;
	}
	else {
		return false;
	}
}

bool Game::can_move(unsigned int robot, unsigned int direction)
{
	unsigned int index = robots[robot];
	if (HAS_WALL(grid[index], direction)) {
		return false;
	}
	if (last == PACK_MOVE(robot, REVERSE[direction])) {
		return false;
	}
	unsigned int new_index = index + OFFSET[direction];
	if (HAS_ROBOT(grid[new_index])){
		return false;
	}
	return true;
}

unsigned int Game::compute_move(unsigned int robot, unsigned int direction){
	unsigned int index = robots[robot] + OFFSET[direction];
	while (true) {
		if (HAS_WALL(grid[index], direction)) {
			break;
		}
		unsigned int new_index = index + OFFSET[direction];
		if (HAS_ROBOT(grid[new_index])) {
			break;
		}
		index = new_index;
	}
	return index;
}

unsigned int Game::do_move(unsigned int robot, unsigned int direction){
	unsigned int start = robots[robot];
	unsigned int end = compute_move(robot, direction);
	unsigned int l = last;
	robots[robot] = end;
	last = PACK_MOVE(robot, direction);
	UNSET_ROBOT(grid[start]);
	SET_ROBOT(grid[end]);
	return PACK_UNDO(robot, start, l);
}

void Game::undo_move(unsigned int undo){
	unsigned int robot = UNPACK_ROBOT(undo);
	unsigned int start = UNPACK_START(undo);
	unsigned int l = UNPACK_LAST(undo);
	unsigned int end = robots[robot];
	robots[robot] = start;
	last = l;
	SET_ROBOT(grid[start]);
	UNSET_ROBOT(grid[end]);
}

void Game::precompute_minimum_moves()
{
	bool status[256];
	for (unsigned int i = 0; i < 256; i++) {
		moves[i] = 0xffffffff;
		status[i] = false;
	}
	moves[token] = 0;
	status[token] = true;
	bool done = false;
	while (!done) {
		done = true;
		for (unsigned int i = 0; i < 256; i++) {
			if (!status[i]) {
				continue;
			}
			status[i] = false;
			unsigned int depth = moves[i] + 1;
			for (unsigned int direction = 1; direction <= 8; direction <<= 1) {
				unsigned int index = i;
				while (!HAS_WALL(grid[index], direction)) {
					index += OFFSET[direction];
					if (moves[index] > depth) {
						moves[index] = depth;
						status[index] = true;
						done = false;
					}
				}
			}
		}
	}
}*/


/*void Game::drawBoard() {
	for (int i = 0; i < map->getNbRow(); i++) {
		for (int j = 0; j < map->getNbCol(); j++) {			
			if (map->getCase(i, j)->getPresenceRobot()) {
				cout << "Robot dans la case : " << i << "," <<j ;
			}		
		}
		cout << endl;
	}
	bool PresenceRobot;
	for (int i = 0; i < map->getNbRow(); i++) {
		
		for (int j = 0; j < map->getNbCol(); j++) {
			cout << "* * * * * * *";		
		}	
		for (int k = 0; k < 5; k++) {
			cout << endl;
			for(int j=0; j< map->getNbCol()+1;j++){
				if (k == 2 && j<map->getNbCol()){
					if (map->getCase(i, j)->getPresenceRobot()) {
						cout << "  R  ";
					}

				}	
				else {
					cout << "*            ";
				}
				
			}
			
		}
		
		cout << endl;
				
		
	}
	for (int j = 0; j < map->getNbCol(); j++) {
		cout << "* * * * * * *";
	}
	cout << endl;
}*/
