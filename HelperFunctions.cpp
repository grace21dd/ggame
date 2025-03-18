#include <SDL.h>

#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
// #include <random>
#include "constant.h"

int randInt(int n)
{
	/*
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(0, n-1);
	return dist(engine);
	*/
	return rand() % n;
}

bool equals(SDL_Color c1, SDL_Color c2)
{
	return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
}

void setRenderColor(SDL_Renderer *renderer, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
}

void clearRender(SDL_Renderer* renderer)
{
	setRenderColor(renderer, DEFAULT_COLOR);
	SDL_RenderClear(renderer);
}

void logSDLError(std::ostream& os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

int initEverything()
{
	srand (time(NULL));

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	if (TTF_Init() != 0) {
		logSDLError(std::cout, "TFF_Init");
		return 1;
	}

	return 0;
}

