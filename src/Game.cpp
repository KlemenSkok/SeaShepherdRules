
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
        
    Window::Create();

    Logger::Success("Game initialized");

    // show main manu on start
    screen.main_menu();

}

int Game::run(int levelNum) {

    // -- INITIALIZE EVERYTHING -- //

    Logger::Status("Starting level");

    Level level(levelNum);
    Game::_gameState = STATE_GAME_SCREEN;
    Game::_isRunning = true;

    Uint32 lastUpdate, currentTime;
    lastUpdate = currentTime = SDL_GetTicks();
    short return_code = -1;

    if(levelNum == 1) {
        // spuci prejsnji replay, ce obstaja
        Replay::StartRecording();
    }

    Logger::Success("--- START ---");

    auto drawLines = [=]() {
        SDL_SetRenderDrawColor(Window::renderer, 200, 200, 200, 255);

        for(int i = 1; i <= 20; i++)
            SDL_RenderDrawLine(Window::renderer, i * Window::Width() / 20, 0, i * Window::Width() / 20, Window::Height());
        for(int i = 1; i <= 10; i++)
            SDL_RenderDrawLine(Window::renderer, 0, i * Window::Height() / 10, Window::Width(), i * Window::Height() / 10);
        
        SDL_SetRenderDrawColor(Window::renderer, 255, 255, 255, 255);
    };


    while(Game::_isRunning) { // main loop


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

            // shrani trenutni frame
            Replay::AppendFrame(level.dumpFrame());
        }


        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                Game::_isRunning = false;
                return_code = EXIT_CODE_QUIT;
                break;
            }
            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    // override previous state
                    Game::_gameState = STATE_PAUSE_MENU;
                }
            }
        }

        switch(Game::_gameState) {

            case STATE_PAUSE_MENU:
                Logger::Status("Entered pause menu.");
                screen.pause_menu();
                break;

            case STATE_GAME_SCREEN:
                break;

            default:
                Game::_isRunning = false;
            
        }
        
    }

    level.Cleanup();


    switch(Game::_gameState) {
                        
        case STATE_VICTORY_SCREEN:
            if(levelNum < NUMBER_OF_LEVELS) {
                return_code = screen.level_done();
            }
            else {
                return_code = screen.victory_screen();
            }
            break;

        case STATE_DEFEAT_SCREEN:
            return_code = screen.defeat_screen();
            break;
    
        case STATE_MAIN_MENU:
            return_code = EXIT_CODE_RESTART;
            screen.main_menu();
            break;
    }

    return return_code;
}

void Game::cleanup() {
    std::cout << "Cleaning up game" << std::endl;
    Window::Destroy();
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}