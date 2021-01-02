#include "Game.h"
#include <time.h>
using namespace std;

Game::Game(User* u, int nRobots, int nJoueurs) : nbRobots(nRobots){
	users = u;
	/*robots = new Robot[nbRobots];//Creation tableau de robots
	GenerateBoard(5, 5, nRobots, robots);*/
	std::cout << "Game created" << std::endl;
}

inline void swap(unsigned int* array, unsigned int a, unsigned int b) {
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
		if (entry->getDepth() < depth) {
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

/*void Game::GenerateBoard(int nbRow, int nbCol, int nbRobots, Robot tabRobots[]) {
	map = new Grid(nbCol, nbRow);
	int l,c = 0;
	srand(time(NULL));
	for (int i = 0; i < nbRobots; i++) {
		l = rand() %(map->getNbRow());
		c = rand() % (map->getNbCol());
		if (map->getCase(l, c)->getPresenceRobot()){
			i--;
		}
		else {			
			map->getCase(l, c)->ajouterRobot(&tabRobots[i]);
		}
	}
	cout << "Board generated " << endl;
}

void Game::drawBoard() {
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
}

/*void Game::gameInformation() {
	std::cout << "Liste joueurs : " << std::endl;
	cout << "nb joueurs : " << nbJoueurs << endl;
	for (int i = 0; i < nbJoueurs; i++) {
		std::cout << users[i].getLastName() << " " << users[i].getFirstName();
	}
	cout << endl;
}*/