
// Screen.cpp

#include "Screen.hpp"
#include "Utilities.hpp"
#include "Constants.hpp"
#include "Logger.hpp"
#include "Replay.hpp"

#include <SDL2/SDL.h>


Screen::Screen() {
    texture = nullptr;
    container = {0, 0, 0, 0};
}

Screen::~Screen() {
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Screen::main_menu() {
    texture = LoadTexture("../../assets/images/menus/main_menu.png");
    bool exit = false;
    SDL_Event e;

    while(!exit) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                exit = true;
                // quit event se prenese v main loop da se lohk program zapre
                SDL_PushEvent(&e);
            }
            else if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_1) {
                    exit = true;
                }
            }
        }
        container = {0, 0, Window::Width(), Window::Height()};
        SDL_RenderClear(Window::renderer);
        SDL_RenderCopy(Window::renderer, texture, NULL, &container);
        SDL_RenderPresent(Window::renderer);
    }
}

void Screen::pause_menu() {
    texture = LoadTexture("../../assets/images/menus/pause_menu.png");
    bool exit = false;
    SDL_Event e;

    while(!exit) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                exit = true;
                // quit event se prenese v main loop da se lohk program zapre
                SDL_PushEvent(&e);
            }
            else if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_1:
                        // continue
                        exit = true;
                        break;
                    case SDLK_3:
                        // quit
                        exit = true;
                        SDL_Event quit_event; // create a quit event
                        quit_event.type = SDL_QUIT;
                        quit_event.quit.timestamp = SDL_GetTicks();
                        SDL_PushEvent(&quit_event);
                        break;
                }
            }
        }
        container = {0, 0, Window::Width(), Window::Height()};
        SDL_RenderClear(Window::renderer);
        SDL_RenderCopy(Window::renderer, texture, NULL, &container);
        SDL_RenderPresent(Window::renderer);
    }

}

int Screen::defeat_screen() {
    texture = LoadTexture("../../assets/images/menus/defeat_screen.png");
    bool exit = false;
    SDL_Event e;

    while(!exit) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                exit = true;
                // quit event se prenese v main loop da se lohk program zapre
                return EXIT_CODE_QUIT;
            }
            else if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_1) {
                    // retry
                    exit = true;
                    return EXIT_CODE_RETRY;
                    break;
                }
                else if(e.key.keysym.sym == SDLK_3) {
                    // quit
                    exit = true;
                    return EXIT_CODE_QUIT;
                    break;
                }
            }
        }
        container = {0, 0, Window::Width(), Window::Height()};
        SDL_RenderClear(Window::renderer);
        SDL_RenderCopy(Window::renderer, texture, NULL, &container);
        SDL_RenderPresent(Window::renderer);
    }
    return EXIT_CODE_QUIT;
}

int Screen::victory_screen() {
    texture = LoadTexture("../../assets/images/menus/victory_screen.png");
    bool exit = false;
    SDL_Event e;

    while(!exit) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                exit = true;
                // quit event se prenese v main loop da se lohk program zapre
                return EXIT_CODE_QUIT;
            }
            else if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {

                    case SDLK_1:
                        // return to main menu
                        exit = true;
                        Logger::Status("nazaj na main menu");
                        return EXIT_CODE_RESTART;
                        break;

                    case SDLK_2: // view replay
                        Replay::StartPlayback();
                        break;
                        
                    case SDLK_3:
                        // quit
                        exit = true;
                        Logger::Status("Quitam iz igre");
                        return EXIT_CODE_QUIT;  
                        break;
                }
            }
        }
        container = {0, 0, Window::Width(), Window::Height()};
        SDL_RenderClear(Window::renderer);
        SDL_RenderCopy(Window::renderer, texture, NULL, &container);
        SDL_RenderPresent(Window::renderer);
    }
    return EXIT_CODE_QUIT;
}


int Screen::level_done() {
    texture = LoadTexture("../../assets/images/menus/level_done.png");
    bool exit = false;
    SDL_Event e;

    while(!exit) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                exit = true;
                // quit event se prenese v main loop da se lohk program zapre
                return EXIT_CODE_QUIT;
            }
            else if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {

                    case SDLK_1:
                        // continue
                        exit = true;
                        Logger::Status("grem na nov level");
                        return EXIT_CODE_CONTINUE;
                        break;
                        
                    case SDLK_3:
                        // quit
                        exit = true;
                        Logger::Status("Quitam iz igre");
                        return EXIT_CODE_QUIT;  
                        break;
                }
            }
        }
        container = {0, 0, Window::Width(), Window::Height()};
        SDL_RenderClear(Window::renderer);
        SDL_RenderCopy(Window::renderer, texture, NULL, &container);
        SDL_RenderPresent(Window::renderer);
    }
    return EXIT_CODE_QUIT;
}