
// PlayerInfo.cpp

#include "PlayerInfo.hpp"



void PlayerInfo::Initialize() {
    
    for(int i = 0; i < 3; i++) {
        score[i] = 0;
    }
    username[0] = '\0';

    Logger::Success("PlayerInfo initialized");

}


void PlayerInfo::Get() {
    TTF_Font *_font = TTF_OpenFont("../../assets/fonts/LilitaOne-Regular.ttf", 24);
    if (!_font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }

    SDL_Window* _window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 120, SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
    if (!_window) {
        SDL_Log("Failed to create popup window: %s", SDL_GetError());
        TTF_CloseFont(_font);
        return;
    }

    SDL_Renderer* _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        SDL_Log("Failed to create popup renderer: %s", SDL_GetError());
        SDL_DestroyWindow(_window);
        TTF_CloseFont(_font);
        return;
    }

    SDL_Color color = {0, 0, 0, 255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(_font, "Enter your username:", color);
    SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);

    SDL_Rect messageRect;
    messageRect.x = 20;
    messageRect.y = 10;
    messageRect.w = surfaceMessage->w;
    messageRect.h = surfaceMessage->h;

    SDL_FreeSurface(surfaceMessage);


    // --- vnos besedila --- //

    SDL_Rect InputBox = {20, 45, 260, 40};

    SDL_StartTextInput();


    SDL_Event e;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            else if(e.type == SDL_WINDOWEVENT) {
                if(e.window.event == SDL_WINDOWEVENT_CLOSE) {
                    if(e.window.windowID == SDL_GetWindowID(_window)) {
                        running = false;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
        SDL_RenderClear(_renderer);
        SDL_RenderCopy(_renderer, messageTexture, NULL, &messageRect);

        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(_renderer, &InputBox);


        SDL_RenderPresent(_renderer);
    }

    SDL_StopTextInput();

    SDL_DestroyTexture(messageTexture);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    TTF_CloseFont(_font);
}

void PlayerInfo::Clean() {
    //SDL_DestroyTexture(_IntroTextT);
    //TTF_CloseFont(_font);
}
