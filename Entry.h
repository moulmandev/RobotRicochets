#pragma once
#include <vector>
#include <iostream>


class Entry {
public:
	Entry();
	Entry(unsigned int, unsigned int, unsigned int, unsigned int);
	~Entry();
	std::vector<unsigned int> getKey();
	unsigned int getDepth();
	void setKey(std::vector<unsigned int>);
	void setDepth(unsigned int);
	void sort();
	bool operator <(Entry&);
	bool operator ==(Entry&);
private:
	std::vector<unsigned int> key;
	unsigned int depth;
};
