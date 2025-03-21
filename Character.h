#ifndef CHARACTER_H
#define CHARACTER_H

#include "GTexture.h"

class Character {
public:
    Character();
    void HandleEvent(SDL_Event& e);
    void Move();
    void Render(SDL_Renderer* renderer);
    bool LoadTexture(std::string path, SDL_Renderer* renderer);

private:
    int posX, posY;
    int velocityY;
    bool isJumping;
    GTexture texture;
};

#endif
