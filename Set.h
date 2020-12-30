#pragma once
#include "Entry.h"

class Set {
public:
	unsigned int getMask();
	unsigned int getSize();
	Entry* getData();
private:
	unsigned int mask;
	unsigned int size;
	Entry* data;
};
