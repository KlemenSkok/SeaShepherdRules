
// Game.cpp

#include "Game.hpp"


using namespace Window;

// define static variables
bool Game::_isRunning = false;
int Game::_currentLevel = 1;


Game::Game() {}
Game::~Game() {}


void Game::init() {
    std::cout << "Initializing game" << std::endl;
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    Game::_isRunning = true;
    
    Window::Create();
}

int Game::run(int levelNum) {

// -- INITIATE EVERYTHING -- //

    Level level(levelNum);
    


    while(Game::_isRunning) { // main loop
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                Game::_isRunning = false;
            }
        }
// -- UPDATE EVERYTHING -- //
        level.Update();

        SDL_RenderClear(Window::renderer); // clear screen

// -- RENDER EVERYTHING -- //
        level.Render();

        SDL_RenderPresent(Window::renderer); // refresh screen

        SDL_Delay(FRAME_TARGET_TIME);
    }


    level.Cleanup();

    return EXIT_CODE_QUIT;
}

void Game::cleanup() {
    std::cout << "Cleaning up game" << std::endl;
    Window::Destroy();
    SDL_Quit();
}