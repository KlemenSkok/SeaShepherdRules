
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
    //screen.main_menu();

    PlayerInfo::Initialize();

}

int Game::run(int levelNum) {

    // -- INITIALIZE EVERYTHING -- //

    auto checkExit = [&]() {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                return EXIT_CODE_QUIT;
            }
        }
        return -1;
    };
    
    if(levelNum == 1) { 
        screen.main_menu();
        if(checkExit() != -1) 
            return EXIT_CODE_QUIT; // handle quit events before level setup

        PlayerInfo::Get();
        if(checkExit() != -1) 
            return EXIT_CODE_QUIT;
    }

    Level level(levelNum);
    Game::_gameState = STATE_GAME_SCREEN;
    Game::_isRunning = true;

    Uint32 lastUpdate, currentTime;
    lastUpdate = currentTime = SDL_GetTicks();
    short return_code = -1;
    SDL_Texture *grid_signs[30];
    for(int i = 0; i < 20; i++) {
        grid_signs[i] = RenderText(std::to_string(i+1).c_str(), TTF_OpenFont("../../assets/fonts/LilitaOne-Regular.ttf", 20), {200, 200, 200, 255});
    }
    for(int i = 0; i < 10; i++) {
        const char str[2] = {(char)(i + 'A'), '\0'};
        grid_signs[i+20] = RenderText(str, TTF_OpenFont("../../assets/fonts/LilitaOne-Regular.ttf", 20), {200, 200, 200, 255});
    }

    if(levelNum == 1) {
        // spuci prejsnji replay, ce obstaja
        Replay::StartRecording();
    }

    Logger::Success("STARTING LEVEL:");
    std::cout << "\b\b\b\b" << levelNum << std::endl;

    auto drawLines = [=]() {
        SDL_SetRenderDrawColor(Window::renderer, 200, 200, 200, 255);
        SDL_Rect textRect;

        for(int i = 1; i <= 20; ++i)
            SDL_RenderDrawLine(Window::renderer, i * Window::Width() / 20, 0, i * Window::Width() / 20, Window::Height());
        for(int i = 1; i <= 10; ++i)
            SDL_RenderDrawLine(Window::renderer, 0, i * Window::Height() / 10, Window::Width(), i * Window::Height() / 10);
        // narisi se crke in stevilke x in y
        for(int i = 1; i <= 20; ++i) {
            SDL_QueryTexture(grid_signs[i-1], NULL, NULL, &textRect.w, &textRect.h);
            textRect.x = i * Window::Width() / 20 - Window::Width() / 40 - textRect.w / 2;
            textRect.y = Window::Height() - textRect.h - 5;
            SDL_RenderCopy(Window::renderer, grid_signs[i-1], NULL, &textRect);
        }
        for(int i = 0; i < 10; ++i) {
            SDL_QueryTexture(grid_signs[20+i], NULL, NULL, &textRect.w, &textRect.h);
            textRect.x = 5;
            textRect.y = Window::Height() - (i+1) * Window::Height() / 10 - textRect.h / 2 + Window::Height() / 20;
            SDL_RenderCopy(Window::renderer, grid_signs[20+i], NULL, &textRect);
        }
        
        SDL_SetRenderDrawColor(Window::renderer, 255, 255, 255, 255);
    };

    // start measuring elapsed time
    auto start_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = start_time - start_time;

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

                // freeze duration counter
                elapsed_time += std::chrono::high_resolution_clock::now() - start_time;

                screen.pause_menu();
                start_time = std::chrono::high_resolution_clock::now();
                break;

            case STATE_GAME_SCREEN:
                break;

            default:
                Game::_isRunning = false;
            
        }
        
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    elapsed_time += end_time - start_time;

    std::cout << "Elapsed time: " << elapsed_time.count() << "s" << std::endl;
    PlayerInfo::SetLevelScore(levelNum, elapsed_time.count());

    level.Cleanup();


    switch(Game::_gameState) {
                        
        case STATE_VICTORY_SCREEN:
            if(levelNum < NUMBER_OF_LEVELS) {
                return_code = screen.level_done();
            }
            else {
                Leaderboard::AddEntry(PlayerInfo::dump());
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