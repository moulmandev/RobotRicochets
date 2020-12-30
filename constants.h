#include <iostream>

#pragma once

/*Directions*/
const char NORTH = 'N';
const char EAST = 'E';
const char SOUTH = 'S';
const char WEST = 'W';

const char DIRECTIONS[4] = {NORTH, EAST, SOUTH, WEST};

const char REVERSE{

};

const char OFFSET{

};

/*Masks*/
const unsigned char M_NORTH = 0x01;
const unsigned char M_EAST = 0x02;
const unsigned char M_SOUTH = 0x04;
const unsigned char M_WEST = 0x08;
const unsigned char M_ROBOT = 0x10;

const char M_LOOKUP{

};

/*Colors*/
const char RED = 'R';
const char GREEN = 'G';
const char BLUE = 'B';
const char YELLOW = 'Y';

const char COLORS[4] = { RED, GREEN, BLUE, YELLOW};

/*Shapes*/

const char CIRCLE = 'C';
const char TRIANGLE = 'T';
const char SQUARE = 'Q';
const char HEXAGON = 'H';

const char SAHPES[4] = { CIRCLE, TRIANGLE, SQUARE, HEXAGON};
