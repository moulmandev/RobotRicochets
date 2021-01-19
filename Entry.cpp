#include "Entry.h"
#include <algorithm>

using namespace std;

Entry::Entry() {
	key.clear();
	depth = 0;
}

Entry::Entry(unsigned int pos1, unsigned int pos2, unsigned int pos3, unsigned int pos4) {
	key.push_back(pos1);
	key.push_back(pos2);
	key.push_back(pos3);
	key.push_back(pos4);
	sort();
}

Entry::~Entry() {

}


vector<unsigned int> Entry::getKey() {
    return key;
}
unsigned int Entry::getDepth() {
    return depth;
}

void Entry::setKey(vector<unsigned int> k) {
    key = k;
}
void Entry::setDepth(unsigned int d) {
    depth = d;
}

void Entry::sort() {
	cout << "Key before sort: ";
	for (int i = 0; i < key.size; i++) {
		cout << key[i] << " / ";
	}
	cout << endl;

	std::sort(key.begin(), key.end());

	cout << "Key : ";
	for (int i = 0; i < key.size; i++) {
		cout << key[i] << " / ";
	}
	cout << endl;
}


bool Entry::operator<(Entry& e2) {
	sort();
	e2.sort();
	for (int i = 0; i < key.size(); i++) {
		if (key[i] < e2.key[i])
			return true;
	}
	return false;
}

bool Entry::operator==(Entry& e2) {
	sort();
	e2.sort();
	for(int i = 0; i < key.size(); i++) {
		if (key[i] != e2.key[i])
			return false;
	}
	return true;
}