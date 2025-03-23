#ifndef GTEXTURE_H
#define GTEXTURE_H

#include <SDL.h>
#include <string>

class GTexture {
public:
    GTexture(SDL_Renderer* renderer);
    ~GTexture();

    bool loadFromFile(const std::string& path);
    void free();
    void render(int x, int y, SDL_Rect* clip = nullptr);

    int getWidth();
    int getHeight();

private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
    SDL_Renderer* mRenderer;
};

#endif
