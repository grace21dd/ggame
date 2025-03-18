#ifndef TILEGENERATOR_H
#define TILEGENERATOR_H

#include <SDL.h>

#include "constant.h"
#include "Tile.h"

class TileGenerator
{
private:
	// int int_arr[TILE_TYPES];
	// int idx;

	// void init();

public:
	Tile next();
};

#endif // TILEGENERATOR_H
