#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"
#include<SDL_mixer.h>

#include <vector>
//const char* WINDOW_TITLE = "Hello World!";
using namespace std;
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture(BACKGROUND_IMG));

    Sprite bird;
    SDL_Texture* birdTexture = graphics.loadTexture("img//dino.png");
    bird.init(birdTexture, BIRD_FRAMES, BIRD_CLIPS);
    ////////////
    Mix_Music *gMusic = graphics.loadMusic("music\\running.mp3");
    graphics.play(gMusic);

    Mix_Chunk *gJump = graphics.loadSound("music\\jump.wav");


   bool quit = false;
SDL_Event e;

ObstacleManager obstacleManager;
SDL_Texture* enemyTexture = graphics.loadTexture("img/tree.png");

Uint32 lastSpawnTime = 0;
const Uint32 spawnInterval = 400; // Cứ 400ms sinh một nhóm xương rồng

while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) quit = true;
    }

    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);


        if (currentKeyStates[SDL_SCANCODE_UP]) cerr << " Up";
        if (currentKeyStates[SDL_SCANCODE_DOWN]) cerr << " Down";
        if (currentKeyStates[SDL_SCANCODE_LEFT]) cerr << " Left";
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) cerr << " Right";
        if (currentKeyStates[SDL_SCANCODE_UP]) graphics.play(gJump);
    background.scroll(8);
    bird.tick();



    // Xóa màn hình và vẽ lại
    graphics.prepareScene();
    graphics.render(background);
    graphics.render(200, 382, bird);
    //obstacleManager.render(graphics.renderer);

    graphics.presentScene();

    SDL_Delay(100); // Tốc độ khoảng 60 FPS (1000ms / 60 ≈ 16ms)
}

 if (gMusic != nullptr) Mix_FreeMusic( gMusic );
    if (gJump != nullptr) Mix_FreeChunk( gJump);



// Giải phóng tài nguyên
SDL_DestroyTexture(enemyTexture);

// Giải phóng tài nguyên
SDL_DestroyTexture(enemyTexture);





    SDL_DestroyTexture( background.texture );
	SDL_DestroyTexture( birdTexture ); birdTexture = nullptr;

    graphics.quit();
    return 0;
}
