#include "Entry.h"

unsigned int Entry::getKey() {
    return key;
}
unsigned int Entry::getDepth() {
    return depth;
}

void Entry::setKey(unsigned int k) {
    key = k;
}
void Entry::setDepth(unsigned int d) {
    depth = d;
}