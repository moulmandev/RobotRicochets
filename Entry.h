#pragma once
#include <vector>
#include <iostream>
#include "constants.h"



class Entry {
public:
	Entry();
	Entry(unsigned int[4], unsigned int);
	Entry(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
	~Entry();
	unsigned int* getKey();
	unsigned int getDepth();
	void setKey(unsigned int, unsigned int, unsigned int, unsigned int);
	void setDepth(unsigned int);
	void sort();
	bool operator <(Entry&);
	bool operator ==(Entry&);
private:
	unsigned int key[NB_ROBOTS];
	unsigned int depth;
};
