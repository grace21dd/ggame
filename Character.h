#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>
#include "gtexture.h"

class Character {
public:
    Character(SDL_Renderer* renderer, const std::string& texturePath, int x, int y, int width, int height);
    ~Character();

    void render();
    void update();

private:
    GTexture texture;
    int x, y;
    int width, height;
    int frame;
    SDL_Renderer* renderer;
};

#endif
