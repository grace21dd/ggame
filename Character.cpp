#include "character.h"

Character::Character(SDL_Renderer* renderer, const std::string& texturePath, int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height), frame(0), renderer(renderer), texture(renderer) {
    texture.loadFromFile(texturePath);
}

Character::~Character() {}

void Character::render() {
    SDL_Rect clip = {frame * width, 0, width, height};
    texture.render(x, y, &clip);
}

void Character::update() {
    frame = (frame + 1) % 3;
    x += 2;

     if (x > 640) {
        x = -64;
    }
}
