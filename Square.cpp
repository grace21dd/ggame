#include <SDL.h>
#include "Constants.h"
#include "HelperFunctions.h"

class Square
{
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

Square::Square()
{}

Square::Square(int x, int y)
{
	rect.x = BOARD_STARTX + SQUARE_SIZE * x + 1;
	rect.y = BOARD_STARTY + SQUARE_SIZE * y + 1;
	rect.w = SQUARE_SIZE - 2;
	rect.h = SQUARE_SIZE - 2;
}

void Square::switchColor(SDL_Color c)
{
	color = c;
}

SDL_Color Square::getColor()
{
	return color;
}

SDL_Rect Square::getRect() {
	return rect;
}
