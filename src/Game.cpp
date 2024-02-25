
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

int Game::run(int level) {
    //main loop

    //check inputs, process events
    //update game state
    //check for collisions
    //render game state

    Player player;
    player.Initialize();


    while(Game::_isRunning) { // main loop
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                Game::_isRunning = false;
            }
        }
        player.Update();

        SDL_RenderClear(Window::renderer); // clear screen
        // render everything
        player.Render();

        // refresh screen
        SDL_RenderPresent(Window::renderer);


        SDL_Delay(FRAME_TARGET_TIME);
    }
    return EXIT_CODE_QUIT;
}

void Game::cleanup() {
    std::cout << "Cleaning up game" << std::endl;
    Window::Destroy();
    SDL_Quit();
}