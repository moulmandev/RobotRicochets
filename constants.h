#include <iostream>

#pragma once

#define MAX_DEPTH 32
#define NB_ROBOTS 4

#define NORTH 0x01
#define EAST  0x02
#define SOUTH 0x04
#define WEST  0x08


#define ROBOT 0x01


#define SET_ROBOT(x) (x |= ROBOT)
#define UNSET_ROBOT(x) (x &= ~ROBOT)

#define PACK_MOVE(robot, direction) (robot << 4 | direction)

const int OFFSET[] = {0, -16, 1, 0, 16, 0, 0, 0, -1};

const unsigned int REVERSE[] = {0, SOUTH, WEST, 0, NORTH, 0, 0, 0, EAST};

