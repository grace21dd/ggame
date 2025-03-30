#ifndef _DEFS__H
#define _DEFS__H

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 520;



#define BACKGROUND_IMG "img\\play.png"


const int BIRD_CLIPS[][4] = {


    {0, 9, 47, 80},
    {50, 9, 47, 80},
    {103, 9, 47, 80},
    {153, 9, 47, 80},



};
const int BIRD_FRAMES = sizeof(BIRD_CLIPS)/sizeof(int)/4;

#endif
