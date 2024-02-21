
// Game.cpp

#include "Game.hpp"
#include "Constants.hpp"

#include <iostream>

// define static variables
bool Game::_isRunning;
int Game::_currentLevel = 1;
SDL_Window *Game::_window = nullptr;
SDL_Renderer *Game::_renderer = nullptr;


Game::Game() {
    //std::cout << "Initializing game" << std::endl;
    testTexture = nullptr;
}


Game::~Game() {
    std::cout << "Game destructor" << std::endl;
}

void Game::init() {
    std::cout << "Initializing game" << std::endl;
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    Game::_window = SDL_CreateWindow("Sea Shepherd Rules", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    Game::_renderer = SDL_CreateRenderer(Game::_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_SetRenderDrawColor(Game::_renderer, 0xFF, 0xFF, 0xFF, 255); // white
    Game::_isRunning = true;
    //SDL_MaximizeWindow(window);

    /* SDL_Surface *surface = IMG_Load("../assets/images/player.png");
    testTexture = SDL_CreateTextureFromSurface(Game::_renderer, surface);
    SDL_FreeSurface(surface); */
    testTexture = ResourceManager::LoadPlayerTexture();
}

void Game::run() {
    //main loop

    //check inputs, process events
    //update game state
    //check for collisions
    //render game state

    SDL_Rect srcRect;
    srcRect.x = WINDOW_WIDTH / 2 - 100;
    srcRect.y = WINDOW_HEIGHT / 2 - 35;
    srcRect.w = 200;
    srcRect.h = 70;

    while(Game::_isRunning) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                Game::_isRunning = false;
            }
        }

        
        SDL_RenderClear(Game::_renderer);
        SDL_RenderCopy(Game::_renderer, testTexture, NULL/* &srcRect */, &srcRect);
        SDL_RenderPresent(Game::_renderer);

        SDL_Delay(FRAME_TARGET_TIME);
    }
}

void Game::cleanup() {
    std::cout << "Cleaning up game" << std::endl;
    SDL_DestroyRenderer(Game::_renderer);
    SDL_DestroyWindow(Game::_window);
    SDL_Quit();
}