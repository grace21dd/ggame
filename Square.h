#ifndef SQUARE_H
#define SQUARE_H

#include <SDL.h>
#include "constant.h"
#include "HelperFunctions.h"

class Square {
	private:
		SDL_Rect rect;
		SDL_Color color = DEFAULT_COLOR;

	public:
		Square();

		Square(int x, int y);

		void switchColor(SDL_Color c);

		SDL_Color getColor();

		SDL_Rect getRect();
};


#endif // SQUARE_H
