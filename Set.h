#pragma once
#include "Entry.h"

class Set {
public:
	unsigned int getMask();
	unsigned int getSize();
	void setMask(unsigned int i);
	void setSize(unsigned int i);
	Entry* setData(Entry* data);
	Entry* getData();
private:
	unsigned int mask;
	unsigned int size;
	Entry* data;
};
