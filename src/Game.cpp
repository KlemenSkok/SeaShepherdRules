
// Game.cpp

#include "Game.hpp"


using namespace Window;

// define static variables
bool Game::_isRunning = false;
int Game::_currentLevel = 1;
int Game::_gameState = STATE_MAIN_MENU;


Game::Game() {}
Game::~Game() {}


void Game::init() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    

    Game::_isRunning = true;
    
    Window::Create();

    Logger::Success("Game initialized");
}

int Game::run(int levelNum) {

// -- INITIATE EVERYTHING -- //

    Logger::Status("Starting level");

    Level level(levelNum);

    Game::_gameState = STATE_GAME_SCREEN;

    Uint32 lastUpdate, currentTime;
    lastUpdate = currentTime = SDL_GetTicks();

    Logger::Success("--- START ---");

    auto drawLines = []() {
        SDL_SetRenderDrawColor(Window::renderer, 200, 200, 200, 255);

        for(int i = 1; i <= 20; i++) {
            SDL_RenderDrawLine(Window::renderer, i * Window::Width() / 20, 0, i * Window::Width() / 20, Window::Height());
        }
        for(int i = 1; i <= 10; i++) {
            SDL_RenderDrawLine(Window::renderer, 0, i * Window::Height() / 10, Window::Width(), i * Window::Height() / 10);
        }

        SDL_SetRenderDrawColor(Window::renderer, 255, 255, 255, 255);
    };


    while(Game::_isRunning) { // main loop
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                Game::_isRunning = false;
            }
        }

        currentTime = SDL_GetTicks();
        if(lastUpdate - currentTime >= FRAME_TARGET_TIME) {

            // -- UPDATE EVERYTHING -- //

            Game::_gameState = level.Update();

            SDL_RenderClear(Window::renderer); // clear screen

            // -- RENDER EVERYTHING -- //
            
            drawLines();
            level.Render();

            SDL_RenderPresent(Window::renderer); // refresh screen



            lastUpdate = currentTime;
        }

        //SDL_Delay(FRAME_TARGET_TIME);

        if(Game::_gameState == STATE_VICTORY_SCREEN)
            break;
    }


    level.Cleanup();

    switch(Game::_gameState) {
        case STATE_VICTORY_SCREEN:
            return EXIT_CODE_CONTINUE;
            break;
        case STATE_DEFEAT_SCREEN:
            return EXIT_CODE_QUIT;
            break;
    }

    return EXIT_CODE_QUIT;
}

void Game::cleanup() {
    std::cout << "Cleaning up game" << std::endl;
    Window::Destroy();
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}