#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include "constant.h"
#include "HelperFunctions.h"
#include "Square.h"
#include "Board.h"
#include "PairOfXY.h"

class Tile
{
	private:
		SDL_Color TILE_COLOR[TILE_TYPES] {CYAN_COLOR, BLUE_COLOR, ORANGE_COLOR, YELLOW_COLOR, LIME_COLOR, PURPLE_COLOR, RED_COLOR};
		PairOfXY OCCUPIED_SQUARES[TILE_TYPES][TILE_SQUARES]					// Assuming x = 0, y = 0;
		{
			{ {0, 1}, {1, 1}, {2, 1}, {3, 1} },					// 'I' -> 4X4
			{ {0, 0}, {0, 1}, {1, 1}, {2, 1} },					// 'J' -> 3X3
			{ {0, 1}, {1, 1}, {2, 1}, {2, 0} },					// 'L' -> 3X3
			{ {0, 0}, {0, 1}, {1, 0}, {1, 1} },					// 'O' -> 2X2	(standard = 4X3)
			{ {1, 0}, {2, 0}, {0, 1}, {1, 1} },					// 'S' -> 3X3
			{ {1, 0}, {0, 1}, {1, 1}, {2, 1} },					// 'T' -> 3X3
			{ {0, 0}, {1, 0}, {1, 1}, {2, 1} },					// 'Z' -> 3X3
		};
		PairOfXY OCCUPIED_AREA[TILE_TYPES] { {4, 4}, {3, 3}, {3, 3}, {2, 2}, {3, 3}, {3, 3}, {3, 3} };


		int type = 0;
		int dir = 0;
		int x = 0, y = 0;

		SDL_Color color;
		PairOfXY occupiedSquares[TILE_SQUARES];
		PairOfXY occupiedArea;

	public:
		Tile();
		Tile(int type, int x, int y);
		int getX();
		int getY();
		void setToType(int type);
		void setToTopMid();
		void removeFromBoard(Board& board);
		void addToBoard(Board& board);;
		bool canDraw(Board& board);;
		bool canMoveLeft(Board& board);
		void moveLeft(Board& board);
		bool canMoveRight(Board& board);
		void moveRight(Board& board);
		bool canMoveDown(Board& board);
		void moveDown(Board& board);
		bool canRotate(Board& board);
		void rotate(Board& board);
		SDL_Color getColor();
		void getTileInfo(int *finalX, int *finalY, int* finalW, int *finalH, PairOfXY *copyOfOccupiedSquares);
};

#endif // TILE_H
