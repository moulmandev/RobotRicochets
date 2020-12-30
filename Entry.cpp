#include "Entry.h"

unsigned int Entry::getKey() {
    return key;
}
unsigned int Entry::getDepth() {
    return depth;
}

unsigned int Entry::setKey(unsigned int k) {
    key = k;
}
unsigned int Entry::setDepth(unsigned int d) {
    depth = d;
}