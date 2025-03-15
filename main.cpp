#include <iostream>
#include <SDL.h>
#include <cmath>

#include "Constants.h"
#include "HelperFunctions.h"
#include "Square.h"
#include "Board.h"
#include "Tile.h"
#include "TileGenerator.h"
#include "Timer.h"
#include "DrawingFunctions.h"
#include "TextDrawingFunctions.h"

//const char* WINDOW_TITLE = "My Tetris";

int game(bool &restart, SDL_Renderer *renderer)
{
	restart = false;
	SDL_Event e;
	bool quit = false;

	clearRender(renderer);
	renderStartMessage(renderer);
	SDL_RenderPresent(renderer);

	bool start = false;
	while (!start) {
		if (SDL_WaitEvent(&e) != 0) {
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
					start = true;
				} else {
					start = true;
				}
			} else if (e.type == SDL_QUIT) {
				quit = true;
				start = true;
			}
		}
	}

	clearRender(renderer);

	Board board;
	renderDrawNewBoard(renderer);

	TileGenerator tileGenerator = TileGenerator();
	Tile tile;
	Tile nextTile = tileGenerator.next();

	SDL_RenderPresent(renderer);
	//SDL_UpdateWindowSurface(window);

	int speed = STARTING_SPEED;
	int score = 0;
	int level = 1;
	int removedLines = 0;
	int newRemovedLines = 0;


	Timer timer = Timer(speed);

	bool canMove = false;
	bool gameOver = false;
	bool isPause = false;
	bool resetScreen = false;
	bool levelUp = false;
	bool quitRequested = false;

	while (!quit){
		if (SDL_WaitEvent(&e) != 0){
			resetScreen = false;
			if (e.type == SDL_QUIT) {
				quitRequested = true;
			}
			else if (e.type == timer.eventType()) {
				newRemovedLines = 0;
				levelUp = false;

				if (isPause || gameOver);
				else if (!canMove) {
					canMove = true;
					newRemovedLines = board.removeFullLines();
					removedLines += newRemovedLines;

					if (newRemovedLines == 1) score += 40 * level;
					else if (newRemovedLines == 2) score += 100 * level;
					else if (newRemovedLines == 3) score += 300 * level;
					else if (newRemovedLines == 4) score += 1200 * level;

					levelUp = (removedLines / 10 + 1 - level) > 0;
					level = removedLines / 10 + 1;
					speed = STARTING_SPEED * pow(SPEED_INCREMENT, level - 1);
					timer.restart(speed);

					tile = nextTile;
					nextTile = tileGenerator.next();
					if (!tile.canDraw(board)) gameOver = true;
					tile.addToBoard(board);

					resetScreen = true;
				} else if (tile.canMoveDown(board)) {
					tile.moveDown(board);
					resetScreen = true;
				} else {
					canMove = false;
				}
			}
			else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					quitRequested = true;
				}
				if (e.key.keysym.sym == SDLK_p) {
					if (isPause) { // pause()
						isPause = false;
						timer.restart();
						resetScreen = true;
					} else {		// resume()
						isPause = true;
						timer.stop();
						resetScreen = true;
					}
				}
				if (e.key.keysym.sym == SDLK_r) {
					if (gameOver) {
						restart = true;
						quit = true;
					}
				}
				if (isPause || gameOver);
				else if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w) {
					if (canMove && tile.canRotate(board)) {
						tile.rotate(board);
						resetScreen = true;
					}
				}
				else if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s) {
					if (canMove && tile.canMoveDown(board)) {
						tile.moveDown(board);
						score += 1;
						resetScreen = true;
					}
				}
				else if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a) {
					if (canMove && tile.canMoveLeft(board)) {
						tile.moveLeft(board);
						resetScreen = true;
					}
				}
				else if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d) {
					if (canMove && tile.canMoveRight(board)) {
						tile.moveRight(board);
						resetScreen = true;
					}
				}
				else if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_RETURN) {
					while (canMove && tile.canMoveDown(board)) {
						tile.moveDown(board);
						score += 2;
						resetScreen = true;
					}
					canMove = false;
				}
			}

			if (quitRequested) {
				clearRender(renderer);
				renderDrawNewBoard(renderer);
				renderLeftMenu(renderer, score, level, removedLines, nextTile);
				renderRightMenu(renderer);
				renderQuitMessage(renderer);
				SDL_RenderPresent(renderer);

				bool keyPressed = false;
				while (!keyPressed) {
					if (SDL_WaitEvent(&e) != 0) {
						if (e.type == SDL_KEYDOWN) {
							keyPressed = true;
							if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_y) {
								quit = true;
							}
						}
						if (e.type == SDL_QUIT) {
							keyPressed = true;
							quit = true;
						}
					}
				}
				quitRequested = false;
				resetScreen = true;
			}
			if (resetScreen) {
				clearRender(renderer);

				if (gameOver) {
					renderDrawFullBoard(renderer, board);
					renderLeftMenu(renderer, score, level, removedLines, nextTile);
					renderRightMenu(renderer);
					renderGameOverMessages(renderer);
				} else if (!isPause) {
					renderDrawFullBoard(renderer, board);
					renderLeftMenu(renderer, score, level, removedLines, nextTile);
					renderRightMenu(renderer);
					renderRemovedLinesMessage(renderer, newRemovedLines);
					if (levelUp) renderLevelUpMessage(renderer);
				} else {
					renderPauseMessage(renderer);
				}
				SDL_RenderPresent(renderer);
				//SDL_UpdateWindowSurface(window);
			}
		}
	}

	timer.stop();

	return 0;
}

int run()
{
	// Initialize everything
	if (initEverything() != 0) return 1;



	//SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);

//Begin: LQH
	SDL_Surface* appIcon = IMG_Load( "paint/icon.png" );
	SDL_SetWindowIcon(window, appIcon);
//End: LQH

	if (window == nullptr) {
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
	if (renderer == nullptr) {
		logSDLError(std::cout, "CreateRenderer");
		SDL_Quit();
		return 1;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	bool restart = true;
	while (restart)
	{
		if (game(restart, renderer) != 0) return 1;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

int main(int argc, char* args[]) {
	return run();
}
