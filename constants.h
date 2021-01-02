#include <iostream>

#pragma once

#define MAX_DEPTH 32

#define HAS_WALL(x, wall) (x & wall)
#define HAS_ROBOT(x) (x & ROBOT)
#define SET_ROBOT(x) (x |= ROBOT)
#define UNSET_ROBOT(x) (x &= ~ROBOT)

#define PACK_MOVE(robot, direction) (robot << 4 | direction)
#define PACK_UNDO(robot, start, last) (robot << 16 | start << 8 | last)
#define UNPACK_ROBOT(undo) ((undo >> 16) & 0xff)
#define UNPACK_START(undo) ((undo >> 8) & 0xff)
#define UNPACK_LAST(undo) (undo & 0xff)
#define MAKE_KEY(x) (x[0] | (x[1] << 8) | (x[2] << 16) | (x[3] << 24))

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
