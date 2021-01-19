#include "Entry.h"
#include <algorithm>

using namespace std;

Entry::Entry() {
	for (int i = 0; i < NB_ROBOTS; i++) {
		key[i] = 0;
	}
	depth = 0;
}

Entry::Entry(unsigned int k[4], unsigned int d) {
	for (int i = 0; i < NB_ROBOTS; i++) {
		key[i] = k[i];
	}
	depth = d;
}
Entry::Entry(unsigned int d, unsigned int pos1, unsigned int pos2, unsigned int pos3, unsigned int pos4) {
	depth = d;
	key[0] = pos1;
	key[1] = pos2;
	key[2] = pos3;
	key[3] = pos4;
	//sort();
}

Entry::~Entry() {

}


unsigned int* Entry::getKey() {
    return key;
}
unsigned int Entry::getDepth() {
    return depth;
}

void Entry::setKey(unsigned int pos1, unsigned int pos2, unsigned int pos3, unsigned int pos4) {
	key[0] = pos1;
	key[1] = pos2;
	key[2] = pos3;
	key[3] = pos4;
}
void Entry::setDepth(unsigned int d) {
    depth = d;
}

void Entry::sort() {
	cout << "Key before sort: ";
	for (int i = 0; i < NB_ROBOTS; i++) {
		cout << key[i] << " / ";
	}
	cout << endl;

	std::sort(key[0], key[NB_ROBOTS-1]);

	cout << "Key : ";
	for (int i = 0; i < NB_ROBOTS; i++) {
		cout << key[i] << " / ";
	}
	cout << endl;
}


bool Entry::operator<(Entry& e2) {
	/*sort();
	e2.sort();*/
	for (int i = 0; i < NB_ROBOTS; i++) {
		if (key[i] < e2.key[i])
			return true;
	}
	return false;
}

bool Entry::operator==(Entry& e2) {
	/*sort();
	e2.sort();*/
	for(int i = 0; i < NB_ROBOTS; i++) {
		if (key[i] != e2.key[i])
			return false;
	}
	return true;
}