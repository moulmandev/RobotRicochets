#include "Set.h"

unsigned int Set::getMask(){
	return mask;
}
unsigned int Set::getSize() {
	return size;
}
Entry* Set::getData(){
	return data;
}

void Set::setMask(unsigned int m) {
	mask = m;
}
void Set::setSize(unsigned int s) {
	size = s;
}

Entry* Set::setData(Entry* data) {
	return data;
}
