#pragma once

class Entry {
public:
	unsigned int getKey();
	unsigned int getDepth();
	unsigned int setKey(unsigned int key);
	unsigned int setDepth(unsigned int depth);
private:
	unsigned int key;
	unsigned int depth;
};
