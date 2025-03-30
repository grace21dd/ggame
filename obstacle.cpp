#include "obstacle.h"
#include "defs.h" // Định nghĩa SCREEN_WIDTH, GROUND, v.v.
#include <cstdlib>

Obstacle::Obstacle(int _type) {
    posX = SCREEN_WIDTH + rand() % 200; // Xuất hiện ngoài màn hình
    posY = (_type == IN_AIR_ENEMY) ? (rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT) + ENEMY_MIN_HEIGHT) : (GROUND - 8);

    eWidth = 0;
    eHeight = 0;
    type = _type;
    EnemyTexture = nullptr;
}

Obstacle::~Obstacle() {
    if (EnemyTexture != nullptr) {
        SDL_DestroyTexture(EnemyTexture);
        EnemyTexture = nullptr;
    }
}

void Obstacle::LoadFromFile(std::string path, SDL_Renderer* gRenderer) {
    SDL_Surface* tmpSurface = IMG_Load(path.c_str());
    if (tmpSurface == nullptr) {
        SDL_Log("Không thể tải ảnh %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return;
    }
    SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));
    EnemyTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
    eWidth = tmpSurface->w;
    eHeight = tmpSurface->h;
    SDL_FreeSurface(tmpSurface);
}

void Obstacle::Move(const int &acceleration) {
    posX -= (ENEMY_SPEED + acceleration);
    if (posX + eWidth < 0) {
        posX = SCREEN_WIDTH + rand() % 200; // Xuất hiện lại ngoài màn hình
    }
}

void Obstacle::Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip) {
    SDL_Rect renderSpace = { posX, posY, eWidth, eHeight };
    if (currentClip != nullptr) {
        renderSpace.w = currentClip->w;
        renderSpace.h = currentClip->h;
    }
    SDL_RenderCopy(gRenderer, EnemyTexture, currentClip, &renderSpace);
}

// Getter methods
int Obstacle::GetType() { return type; }
int Obstacle::GetSpeed(const int &acceleration) { return ENEMY_SPEED + acceleration; }
int Obstacle::GetPosX() { return posX; }
int Obstacle::GetPosY() { return posY; }
int Obstacle::GetWidth() { return eWidth; }
int Obstacle::GetHeight() { return eHeight; }
