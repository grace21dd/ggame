#include "gtexture.h"
#include <iostream>

GTexture::GTexture(SDL_Renderer* renderer) : mTexture(nullptr), mWidth(0), mHeight(0), mRenderer(renderer) {}

GTexture::~GTexture() {
    free();
}

bool GTexture::loadFromFile(const std::string& path) {
    free();

    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str()); // or SDL_LoadPNG,...
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF)); // Color key (transparent color)

    newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
    if (newTexture == nullptr) {
        std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);
    mTexture = newTexture;

    return true;
}

void GTexture::free() {
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void GTexture::render(int x, int y, SDL_Rect* clip) {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if (clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(mRenderer, mTexture, clip, &renderQuad);
}

int GTexture::getWidth() {
    return mWidth;
}

int GTexture::getHeight() {
    return mHeight;
}
