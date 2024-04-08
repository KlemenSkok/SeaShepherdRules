
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

    // -- INITIALIZE EVERYTHING -- //

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

            // -- RENDER EVERYTHING -- //
            SDL_RenderClear(Window::renderer); // clear screen
            
            drawLines();
            level.Render();

            SDL_RenderPresent(Window::renderer); // refresh screen


            lastUpdate = currentTime;
        }


        if(Game::_gameState != STATE_GAME_SCREEN)
            Game::_isRunning = false;
        
    }



/*     switch(Game::_gameState) {
            
        case STATE_VICTORY_SCREEN:
            Logger::Status("Level completed!");
            Game::_isRunning = false;
            break;

        case STATE_DEFEAT_SCREEN:
            Logger::Status("Player died!");
            Game::_isRunning = false;
            break;

        case STATE_MAIN_MENU:
            Logger::Status("Entered main menu.");
            Game::_isRunning = false;
            break;

        case STATE_PAUSE_MENU:
            Logger::Status("Entered pause menu.");
            Game::_isRunning = false;
            break;
        
        default:
            // do nothing
    } */

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