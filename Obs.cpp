#include "Obs.h"

Obstacle::Obstacle(int x, int y) {
    rect = {x, y, 60, 20};
}

void Obstacle::update() {
    rect.x -= 5;
}

void Obstacle::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 210, 180, 140, 255);
    SDL_RenderFillRect(renderer, &rect);
}

bool Obstacle::checkCollision(SDL_Rect dino) {
    return SDL_HasIntersection(&rect, &dino);
}
