#ifndef _DEFS__H
#define _DEFS__H

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 520;

const int START_BUTTON_X = 432;
const int START_BUTTON_Y = 266;
const int START_BUTTON_WIDTH = 136;
const int START_BUTTON_HEIGHT = 56;

const int EXIT_BUTTON_X = 21;
const int EXIT_BUTTON_Y = 13;
const int EXIT_BUTTON_WIDTH = 54;
const int EXIT_BUTTON_HEIGHT = 56;

const int OBS_SPEED = 5;
#define BACKGROUND_IMG "img\\play.png"
enum GameState {
    MENU,
    PLAYING,
    END,
    EXIT
};

const int DINO_CLIPS[][4] = {


    {0, 9, 47, 80},
    {50, 9, 47, 80},
    {103, 9, 47, 80},
    {153, 9, 47, 80},



};
const int DINO_FRAMES = sizeof(DINO_CLIPS)/sizeof(int)/4;

#endif
