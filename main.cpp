#include<iostream>

using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TILE_SIZE = 40;
const int MAP_WIDTH = SCREEN_WIDTH / TILE_SIZE;
const int MAP_HEIGHT = SCREEN_HEIGHT / TILE_SIZE;
class Game
{
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    //function
    Game()
    {
        running = true;
        if(SDL_Init(SDL_INIT_VIDEO)<0)
        {
            cerr << "SDL could not :" << SDL_GetError() << endl;
            running = false;
        }
        window = SDL_CreateWindow("B", SDL_WINDOWPOS_CENTERED, SCREEN_HEIGHT, SCREEN_WIDTH,SDL_WINDOW_SHOWN);
        if(!window)
        {
            cerr << "window could not:" << SDL_GetError()<< endl;
            running false;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer)
        {
            cerr << "renderer could not:" << SDL_GetError()<< endl;
            running = false;

        }
    }
    void render()
    {
        SDL_SetRenderDrawColor(renderer, 128, 128,128,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        for(int i=1; i<MAP_HEIGHT-1; ++i)
        {
            for(int j=1;j<MAP_WIDTH-1;++j)
            {
                SDL_Rect tile = {j*TILE_SIZE, i*TILE_SIZE,}

            }

        }

    }
    void run() {}
    ~Game() {}

};
