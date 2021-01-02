#pragma once

class Entry {
public:
	unsigned int getKey();
	unsigned int getDepth();
	void setKey(unsigned int key);
	void setDepth(unsigned int depth);
private:
	unsigned int key;
	unsigned int depth;
};
