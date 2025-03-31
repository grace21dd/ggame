#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include <vector>


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
    SDL_Init(SDL_INIT_VIDEO);
    GameState gameState = MENU;

    if (TTF_Init() == -1) {
    SDL_Log("Failed to initialize SDL_ttf: %s", TTF_GetError());
}

    Graphics graphics;
    graphics.init();
    ObstacleManager obstacleManager;

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture(BACKGROUND_IMG));

    Sprite dino;
    SDL_Texture* dinoTexture = graphics.loadTexture("img//dino.png");
    dino.init(dinoTexture, DINO_FRAMES, DINO_CLIPS);
    ////////////
    Mix_Music *gMusic = graphics.loadMusic("music\\running.mp3");
    graphics.play(gMusic);

    Mix_Chunk *gJump = graphics.loadSound("music\\jump.wav");


bool quit = false;
SDL_Event e;
int spawnCounter = 0;


bool isGameOver = false;

Uint32 lastSpawnTime = 0;
const Uint32 spawnInterval = 400;
 SDL_Texture* menuBackground = graphics.loadTexture("img//run.png");

SDL_Texture* obsTexture = graphics.loadTexture("img//obs.png");

TTF_Font* font = TTF_OpenFont("assets//fontpu.ttf", 30);

if (!font) {
    SDL_Log("Failed to load font: %s", TTF_GetError());
}


int score = 0;
int highest = 0;
// Vòng lặp chính
while (!quit) {

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) quit = true;

        // click menu
        if (gameState == MENU && e.type == SDL_MOUSEBUTTONDOWN) {
            int x = e.button.x, y = e.button.y;
            if (x >= START_BUTTON_X && x <= START_BUTTON_X + START_BUTTON_WIDTH &&
                y >= START_BUTTON_Y && y <= START_BUTTON_Y + START_BUTTON_HEIGHT) {
                gameState = PLAYING;
            }
            if (x >= EXIT_BUTTON_X && x <= EXIT_BUTTON_X + EXIT_BUTTON_WIDTH &&
                y >= EXIT_BUTTON_Y && y <= EXIT_BUTTON_Y + EXIT_BUTTON_HEIGHT) {
                gameState = EXIT;
            }
        }


        if (gameState == PLAYING) {
            dino.handleInput(e);
        }
    }

    SDL_RenderClear(graphics.renderer);

    if (gameState == MENU) {
        SDL_RenderCopy(graphics.renderer, menuBackground, NULL, NULL);
    }
    else if (gameState == PLAYING) {

    score += 1;

        graphics.prepareScene();

        background.scroll(9);
        dino.tick();


        graphics.render(background);
        SDL_Rect dinoRect = {200, dino.dinoY, 40, 40};
        graphics.render(200, dino.dinoY, dino);
        obstacleManager.render(graphics.renderer);

        obstacleManager.update(obsTexture, dinoRect, gameState, isGameOver);

SDL_Color scoreColor = {75, 0, 130, 255};
string scoreText = "Score: " + to_string(score);
graphics.renderText(scoreText.c_str(), 700, 20, scoreColor, font);
string highScoreText = "Highest: " + to_string(highest);
graphics.renderText(highScoreText.c_str(), 700, 50, scoreColor,font);
graphics.presentScene();


    }
    else if (gameState == EXIT) {
        quit = true;
    }
    else if (gameState == END) {

    graphics.prepareScene();
    graphics.render(background);
    graphics.render(200, dino.dinoY, dino);
    obstacleManager.render(graphics.renderer);

    SDL_Color yellow = {25, 25, 112, 255};
    graphics.renderText("Press ENTER to replay or ESC to exit", 150, 250, yellow, font);

    graphics.presentScene();

    bool waitingForInput = true;
    while (waitingForInput) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
                waitingForInput = false;
            }
            if (e.type == SDL_KEYDOWN) {
                std::cout << "Key pressed: " << SDL_GetKeyName(e.key.keysym.sym) << std::endl;
                if (e.key.keysym.sym == SDLK_RETURN) {
                    isGameOver = false;
                    gameState = PLAYING;
                    score = 0;
                    obstacleManager.clear();
                    waitingForInput = false;
                }
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                    waitingForInput = false;
                }
            }
        }
    }

}
if (isGameOver) {
    if (score > highest) {
        highest = score;
    }
}


graphics.presentScene();
    SDL_Delay(100);
}


 if (gMusic != nullptr) Mix_FreeMusic( gMusic );
    if (gJump != nullptr) Mix_FreeChunk( gJump);



SDL_DestroyTexture(obsTexture);


    SDL_DestroyTexture( background.texture );
	SDL_DestroyTexture( dinoTexture ); dinoTexture = nullptr;

    graphics.quit();
    return 0;
}
