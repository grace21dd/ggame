#ifndef TEXTDRAWINGFUNCTIONS_H
#define TEXTDRAWINGFUNCTIONS_H

#include <SDL.h>


#include "Tile.h"
#include "constant.h"
#include "DrawingFunctions.h"

void renderTopMessage(SDL_Renderer *renderer, const std::string message, const SDL_Color color);
void renderBottomMessage(SDL_Renderer *renderer, const std::string message, const SDL_Color color);
void renderPauseMessage(SDL_Renderer *renderer);
void renderGameOverMessages(SDL_Renderer *renderer);
void renderRemovedLinesMessage(SDL_Renderer *renderer, int newRemovedLines);
void renderLevelUpMessage(SDL_Renderer* renderer);
void renderLeftMenu(SDL_Renderer* renderer, int score, int level, int removedLines, Tile &nextTile);
void renderRightMenu(SDL_Renderer* renderer);
void renderStartMessage(SDL_Renderer* renderer);
void renderQuitMessage(SDL_Renderer* renderer);

#endif // TEXTDRAWINGFUNCTIONS_H

