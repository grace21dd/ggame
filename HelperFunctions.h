#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <SDL.h>

#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "constant.h"

int randInt(int n);
bool equals(SDL_Color c1, SDL_Color c2);
void setRenderColor(SDL_Renderer *renderer, SDL_Color color);
void clearRender(SDL_Renderer *renderer);
void logSDLError(std::ostream& os, const std::string& msg);
int initEverything();

#endif // HELPERFUNCTIONS_H
