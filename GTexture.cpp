#include "GTexture.h"

GTexture::GTexture() : mTexture(nullptr), mWidth(0), mHeight(0) {}

GTexture::~GTexture() {
    Free();
}

bool GTexture::LoadFromFile(std::string path, SDL_Renderer* renderer) {
    Free();
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) return false;

    mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
    return mTexture != nullptr;
}

void GTexture::Render(int x, int y, SDL_Renderer* renderer) {
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy(renderer, mTexture, nullptr, &renderQuad);
}

void GTexture::Free() {
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}
