#ifndef BOARD_H
#define BOARD_H

#include <SDL.h>
#include "constant.h"
#include "HelperFunctions.h"
#include "Square.h"

class Board
{
	private:
		Square squares[BOARD_WIDTH_SQUARES][BOARD_HEIGHT_SQUARES];
		int numOfOccupied[BOARD_HEIGHT_SQUARES];

	public:
		Board();
		Square squareAt(int x, int y);
		void removeSquare(int x, int y);
		void addSquare(int x, int y, SDL_Color color);
		SDL_Color colorAt(int x, int y);
		int removeFullLines();  // Return num of removed lines
};

#endif // _BOARD_H_INCLUDED_
