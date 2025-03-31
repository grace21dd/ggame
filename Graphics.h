#ifndef _GRAPHICS__H
#define _GRAPHICS__H
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include <vector>
#include<algorithm>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
struct Obstacle {
    SDL_Texture* texture;
    SDL_Rect rect;
    int speed;

    Obstacle(SDL_Texture* _texture, int x, int y, int w, int h, int _speed)
        : texture(_texture), speed(_speed) {
        rect = {x, y, w, h};
    }

    void update() {
        rect.x -= speed;
    }

    void render(SDL_Renderer* renderer) {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }

    bool isOffScreen() const {
        return rect.x + rect.w < 0;
    }
};


class ObstacleManager {
    std::vector<Obstacle> obstacles;
     Uint32 lastSpawnTime = 0;
     Uint32 nextSpawnTime = 1000 + rand() % 3500;
    const Uint32 minSpawnInterval = 1500;
    const Uint32 maxSpawnInterval = 3500;

public:
     bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
        return (a.x < b.x + b.w &&
                a.x + a.w > b.x &&
                a.y < b.y + b.h &&
                a.y + a.h > b.y);
    }
    void addObstacle(SDL_Texture* texture) {
        int obsWidth = 40;
        int obsHeight = 60;
        int x = SCREEN_WIDTH;
        int y = 406 ;

        obstacles.emplace_back(texture, x, y, obsWidth, obsHeight, 7);
        lastSpawnTime = SDL_GetTicks();
    }




void update(SDL_Texture* texture, const SDL_Rect& dinoRect, GameState& gameState, bool& isGameOver) {
    for (auto& obs : obstacles) {
        obs.update();
        if (checkCollision(dinoRect, obs.rect)) {
            gameState = END;
            isGameOver = true;
            return;
        }
    }
    obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
                    [](const Obstacle& obs) { return obs.isOffScreen(); }), obstacles.end());

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastSpawnTime >= nextSpawnTime) {
        addObstacle(texture);
        lastSpawnTime = currentTime;
        nextSpawnTime = 2000 + rand() % 4000;
    }
}

    void render(SDL_Renderer* renderer) {
        for (auto& obs : obstacles) {
            obs.render(renderer);
        }
    }
    void clear() {
    obstacles.clear();
}

};

struct ScrollingBackground {
    SDL_Texture* texture;
    int scrollingOffset = 0;
    int width, height;

    void setTexture(SDL_Texture* _texture) {
        texture = _texture;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }

    void scroll(int distance) {
        scrollingOffset -= distance;
        if( scrollingOffset < 0 ) { scrollingOffset = width; }
    }
};

struct Sprite {
    bool isJumping = false;
    int jumpVelocity = 0;
    int dinoY = 395;
    const int maxJumpHeight = 100;
    SDL_Texture* texture;
    std::vector<SDL_Rect> clips;
    int currentFrame = 0;

    void init(SDL_Texture* _texture, int frames, const int _clips [][4]) {
        texture = _texture;

        SDL_Rect clip;
        for (int i = 0; i < frames; i++) {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            clips.push_back(clip);
        }
    }
    void tick() {
        currentFrame = (currentFrame + 1) % clips.size();
        if (isJumping) {
            dinoY += jumpVelocity;
            jumpVelocity += 5;

            if (dinoY <= maxJumpHeight) {
            dinoY = maxJumpHeight;
            jumpVelocity = 0;
        }

            if (dinoY >= 395) {
                dinoY = 395;
                isJumping = false;
            }
        }
    }
    void handleInput(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
        if (!isJumping) {
            isJumping = true;
            jumpVelocity = -33;
        }
    }
}

    const SDL_Rect* getCurrentClip() const {
        return &(clips[currentFrame]);
    }
};
struct Graphics
{
    SDL_Renderer *renderer;
	SDL_Window *window;

	const char* WINDOW_TITLE ="run crazy";

	void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }

	void init(){
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);


        if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        }
    }

	void prepareScene(SDL_Texture * background = nullptr)
    {
        SDL_RenderClear(renderer);
        if (background != nullptr) SDL_RenderCopy( renderer, background, NULL, NULL);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture* loadTexture(const char *filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

   void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)

    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = src->w;
        dest.h = src->h;

        SDL_RenderCopy(renderer, texture, src, &dest);
    }

    void quit()
    {
        IMG_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

     void render(int x, int y, const Sprite& sprite) {
        const SDL_Rect* clip = sprite.getCurrentClip();
        SDL_Rect renderQuad = {x, y, clip->w, clip->h};
        SDL_RenderCopy(renderer, sprite.texture, clip, &renderQuad);
    }
     void render(const ScrollingBackground& background) {
        renderTexture(background.texture, background.scrollingOffset, 0);
        renderTexture(background.texture, background.scrollingOffset - background.width, 0);
    }
///////////////////
    Mix_Music* loadMusic(const char* path)
    {
        Mix_Music *gMusic = Mix_LoadMUS(path);
        if (gMusic == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                           "Could not load music! SDL_mixer Error: %s", Mix_GetError());
        }
        return gMusic;
    }
     void play(Mix_Music *gMusic)
    {
        if (gMusic == nullptr) return;

        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic( gMusic, -1 );
        }
        else if( Mix_PausedMusic() == 1 ) {
            Mix_ResumeMusic();
        }
    }

    Mix_Chunk* loadSound(const char* path) {
        Mix_Chunk* gChunk = Mix_LoadWAV(path);
        if (gChunk == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
        }
    }
     void play(Mix_Chunk* gChunk) {
        if (gChunk != nullptr) {
            Mix_PlayChannel( -1, gChunk, 0 );
        }
    }


void renderText(const char* text, int x, int y, SDL_Color color, TTF_Font* font) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
    if (textSurface == nullptr) return;

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};

    SDL_FreeSurface(textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
}
void waitForRestartOrExit(bool& quit, GameState& gameState, bool& isGameOver, ObstacleManager& obstacleManager) {
    SDL_Event e;
    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
                return;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    isGameOver = false;
                    gameState = PLAYING;
                    obstacleManager.clear();
                    return;
                }
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                    return;
                }
            }
        }
    }
}


};

#endif
