#include <SDL.h>
#include <string>

#include "constant.h"
#include "HelperFunctions.h"
#include "Square.h"
#include "Board.h"
#include "PairOfXY.h"
#include "Tile.h"

void renderDrawRect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color)
{
	setRenderColor(renderer, color);
	SDL_RenderFillRect(renderer, &rect);
}

void renderDrawSquare(SDL_Renderer *renderer, Square square)
{
	SDL_Rect rect = square.getRect();
	renderDrawRect(renderer, rect, square.getColor());
}

void renderDrawAllBoardSquares(SDL_Renderer* renderer, Board &board)
{
	for (int x = 0; x < BOARD_WIDTH_SQUARES; ++x) {
		for (int y = 0; y < BOARD_HEIGHT_SQUARES; ++y) {
			renderDrawSquare(renderer, board.squareAt(x, y));
		}
	}
}

void renderDrawNewBoard(SDL_Renderer *renderer)
{
	for (int x = 0; x < BOARD_WIDTH_SQUARES; ++x) {
		for (int y = 0; y < BOARD_HEIGHT_SQUARES; ++y) {

			SDL_Rect rect;
			rect.x = BOARD_STARTX + SQUARE_SIZE * x;
			rect.y = BOARD_STARTY + SQUARE_SIZE * y;
			rect.w = SQUARE_SIZE;
			rect.h = SQUARE_SIZE;
			setRenderColor(renderer, SQUARE_SIDE_COLOR);
			SDL_RenderDrawRect(renderer, &rect);
		}
	}

	SDL_Rect rect;
	rect.x = BOARD_STARTX;
	rect.y = BOARD_STARTY;
	rect.w = BOARD_WIDTH_PIXELS;
	rect.h = BOARD_HEIGHT_PIXELS;
	setRenderColor(renderer, BOARD_SIDE_COLOR);
	SDL_RenderDrawRect(renderer, &rect);
}

void renderDrawFullBoard(SDL_Renderer* renderer, Board &board)
{
	renderDrawNewBoard(renderer);
	renderDrawAllBoardSquares(renderer, board);
}

void renderTextureToCenterOfRect(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect rect)
{
	SDL_Rect texRect;
	SDL_QueryTexture(texture, NULL, NULL, &texRect.w, &texRect.h);
	texRect.x = rect.x + (rect.w - texRect.w) / 2;
	texRect.y = rect.y + (rect.h - texRect.h) / 2;

	SDL_RenderCopy(renderer, texture, NULL, &texRect);
}

void renderImageToCenterOfRect(SDL_Renderer *renderer, const std::string file, const SDL_Rect rect)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
	renderTextureToCenterOfRect(renderer, texture, rect);
	SDL_DestroyTexture(texture);
}

SDL_Texture* textTexture(SDL_Renderer *renderer, const std::string &message, const std::string &fontFile, const SDL_Color color, const int fontSize)
{
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);

	SDL_Surface *surface = TTF_RenderUTF8_Blended(font, message.c_str(), color);

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	return texture;
}

void renderTextToCenterOfRect(SDL_Renderer *renderer, const std::string &message, const std::string &fontFile, const SDL_Color color, const int fontSize, const SDL_Rect rect)
{
	SDL_Texture* texture = textTexture(renderer, message, fontFile, color, fontSize);
	renderTextureToCenterOfRect(renderer, texture, rect);
	SDL_DestroyTexture(texture);
}

void renderTileToCenterOfRect(SDL_Renderer* renderer, Tile tile, const SDL_Rect rect)
{
	int tX, tY, tW, tH;
	PairOfXY occupiedSquares[TILE_SQUARES];
	tile.getTileInfo(&tX, &tY, &tW, &tH, occupiedSquares);
	int pixelX = rect.x + (rect.w - tW * SQUARE_SIZE) / 2;
	int pixelY = rect.y + (rect.h - tH * SQUARE_SIZE) / 2;
	for (int i = 0; i < TILE_SQUARES; ++i) {
		SDL_Rect rect;
		rect.x = pixelX + (occupiedSquares[i].x - tX) * SQUARE_SIZE;
		rect.y = pixelY + (occupiedSquares[i].y - tY) * SQUARE_SIZE;
		rect.w = SQUARE_SIZE;
		rect.h = SQUARE_SIZE;
		renderDrawRect(renderer, rect, tile.getColor());
	}
}

void renderTextureToLeftOfRect(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect rect)
{
	SDL_Rect texRect;
	SDL_QueryTexture(texture, NULL, NULL, &texRect.w, &texRect.h);
	texRect.x = rect.x;
	texRect.y = rect.y + (rect.h - texRect.h) / 2;

	SDL_RenderCopy(renderer, texture, NULL, &texRect);
}

void renderTextToLeftOfRect(SDL_Renderer *renderer, const std::string &message, const std::string &fontFile, const SDL_Color color, const int fontSize, const SDL_Rect rect)
{
	SDL_Texture* texture = textTexture(renderer, message, fontFile, color, fontSize);
	renderTextureToLeftOfRect(renderer, texture, rect);
	SDL_DestroyTexture(texture);
}

