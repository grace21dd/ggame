#ifndef GTEXTURE_H
#define GTEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class GTexture {
public:
    GTexture();
    ~GTexture();
    bool LoadFromFile(std::string path, SDL_Renderer* renderer);
    void Render(int x, int y, SDL_Renderer* renderer);
    void Free();

private:
    SDL_Texture* mTexture;
    int mWidth, mHeight;
};

#endif
