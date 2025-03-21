#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>

class Obstacle {
public:
    Obstacle(int x, int y);
    void update();
    void render(SDL_Renderer* renderer);
    bool checkCollision(SDL_Rect dino);

private:
    SDL_Rect rect;
};

#endif
