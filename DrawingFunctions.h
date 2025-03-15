#ifndef DRAWINGFUNCTIONS_H
#define DRAWINGFUNCTIONS_H

#include <SDL.h>
#include "Constants.h"
#include "HelperFunctions.h"
#include "Square.h"
#include "Board.h"

void renderDrawRect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color);
void renderDrawSquare(SDL_Renderer *renderer, Square square);
void renderDrawAllBoardSquares(SDL_Renderer* renderer, Board &board);
void renderDrawNewBoard(SDL_Renderer *renderer);
void renderDrawFullBoard(SDL_Renderer* renderer, Board &board);
void renderTextureToCenterOfRect(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect rect);
void renderImageToCenterOfRect(SDL_Renderer *renderer, const std::string file, const SDL_Rect rect);
SDL_Texture* textTexture(SDL_Renderer *renderer, const std::string &message, const std::string &fontFile, const SDL_Color color, const int fontSize);
void renderTextToCenterOfRect(SDL_Renderer *renderer, const std::string &message, const std::string &fontFile, const SDL_Color color, const int fontSize, const SDL_Rect rect);
void renderTileToCenterOfRect(SDL_Renderer* renderer, Tile tile, const SDL_Rect rect);
void renderTextureToLeftOfRect(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect rect);
void renderTextToLeftOfRect(SDL_Renderer *renderer, const std::string &message, const std::string &fontFile, const SDL_Color color, const int fontSize, const SDL_Rect rect);
#endif // DRAWINGFUNCTIONS_H

