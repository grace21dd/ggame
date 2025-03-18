#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL.h>
#include <string>

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;

const int SQUARE_SIZE = 25;
const int BOARD_WIDTH_SQUARES = 10;
const int BOARD_HEIGHT_SQUARES = 20;
const int BOARD_WIDTH_PIXELS = BOARD_WIDTH_SQUARES * SQUARE_SIZE;
const int BOARD_HEIGHT_PIXELS = BOARD_HEIGHT_SQUARES * SQUARE_SIZE;

const int BOARD_STARTX = SCREEN_WIDTH / 2 - BOARD_WIDTH_PIXELS / 2;
const int BOARD_STARTY = SCREEN_HEIGHT / 2 - BOARD_HEIGHT_PIXELS / 2;

const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};

const SDL_Color SQUARE_SIDE_COLOR = {32, 32, 34}; // MY gray
const SDL_Color BOARD_SIDE_COLOR = WHITE_COLOR;
const SDL_Color DEFAULT_COLOR = BLACK_COLOR;

const std::string WINDOW_TITLE = "My Tetris";
const int STARTING_SPEED = 900;
const double SPEED_INCREMENT = 0.8;
const std::string SPEED_INCREMENT_STR = "80%";

const int TILE_TYPES = 7;
const int TILE_SQUARES = 4;

const std::string GAMEOVER_FILE = "paint/GAMEOVER.png";
const std::string TETRIS_200x66_FILE = "paint/TETRIS_200x66.png";
const std::string TETRIS_600x200_FILE = "paint/TETRIS_600x200.png";
const std::string NORMAL_FONT_LINK = "fonts/courbd.ttf";
const std::string TETRIS_LINK = "fonts/Tetris.ttf";

const int WORD_FONT = 24;
const int NUMBERS_FONT = 36;
const int TETRIS_FONT = 48;

const int INF = 999999999;

#endif // CONSTANTS_H
