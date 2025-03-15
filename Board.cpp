#include <SDL.h>
#include "Constants.h"
#include "HelperFunctions.h"
#include "Square.h"
#include <iostream>
#include "Board.h"

Board::Board()
{
	for (int y = 0; y < BOARD_HEIGHT_SQUARES; ++y) {
		numOfOccupied[y] = 0;
	}

	for (int x = 0; x < BOARD_WIDTH_SQUARES; ++x) {
		for (int y = 0; y < BOARD_HEIGHT_SQUARES; ++y) {
			squares[x][y] = Square(x, y);
		}
	}
}

Square Board::squareAt(int x, int y)
{
	return squares[x][y];
}

void Board::removeSquare(int x, int y)
{
	if (!equals(squares[x][y].getColor(), DEFAULT_COLOR)) {
		--numOfOccupied[y];
		squares[x][y].switchColor(DEFAULT_COLOR);
	}
}

void Board::addSquare(int x, int y, SDL_Color color)
{
	if (equals(squares[x][y].getColor(), DEFAULT_COLOR)) {
		++numOfOccupied[y];
	}
	squares[x][y].switchColor(color);
}

SDL_Color Board::colorAt(int x, int y)
{
	return squares[x][y].getColor();
}

int Board::removeFullLines()
{
	int numOfRemovedLines = 0;
	for (int y = BOARD_HEIGHT_SQUARES - 1; y >= 0; --y) {
		if (numOfOccupied[y] == BOARD_WIDTH_SQUARES) {

	// Line full
			++numOfRemovedLines;

			for (int x = 0; x < BOARD_WIDTH_SQUARES; ++x) {
				removeSquare(x, y);
			}
		} else {	// Line not full
			if (numOfRemovedLines == 0) continue;

			// numOfRemovedLines > 0 --> "drop" line

			for (int x = 0; x < BOARD_WIDTH_SQUARES; ++x) {
				if (equals(squares[x][y].getColor(), DEFAULT_COLOR)) continue;
				addSquare(x, y + numOfRemovedLines, squares[x][y].getColor());
				removeSquare(x, y);
			}
		}
	}


	return numOfRemovedLines;
}

