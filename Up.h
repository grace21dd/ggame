#ifndef POWERUP_H
#define POWERUP_H

#include <SDL.h>

class PowerUp {
public:
    PowerUp(int x, int y);
    void update();
    void render(SDL_Renderer* renderer);
    bool checkCollision(SDL_Rect dino);
    bool isActive() const;

private:
    SDL_Rect rect;
    bool active;
};

#endif
