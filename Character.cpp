#include "Character.h"

const int GROUND = 300;
const int JUMP_HEIGHT = 150;
const int GRAVITY = 5;
const int JUMP_SPEED = -20;

Character::Character() {
    posX = 50;
    posY = GROUND;
    velocityY = 0;
    isJumping = false;
}

bool Character::LoadTexture(std::string path, SDL_Renderer* renderer) {
    return texture.LoadFromFile(path, renderer);
}

void Character::HandleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && !isJumping) {
        velocityY = JUMP_SPEED;
        isJumping = true;
    }
}

void Character::Move() {
    posY += velocityY;
    velocityY += GRAVITY;

    if (posY >= GROUND) {
        posY = GROUND;
        isJumping = false;
    }
}

void Character::Render(SDL_Renderer* renderer) {
    texture.Render(posX, posY, renderer);
}
