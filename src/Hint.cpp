
// Hint.cpp

#include "Hint.hpp"
#include "Constants.hpp"
#include "Utilities.hpp"

#include <iostream>

using namespace Window;

Hint::Hint() {

    texture = nullptr;
    font = TTF_OpenFont("../../assets/fonts/LilitaOne-Regular.ttf", 24);
    container = {0, 0, 0, 0};

    hintActive = false;
    ms_toWait = rand() % 300 + 300; // najprej pocaka 10-15s
    toRefresh = false;

}

Hint::~Hint() {
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Hint::Refresh(SDL_Rect rect) {

    text = "Whaler detected in sector " + std::to_string(rect.x / (Window::Width() / SECTOR_COUNT_X) + 1) + (char)(SECTOR_COUNT_Y - (rect.y / (Window::Height() / SECTOR_COUNT_Y)) - 1 + 'A');

    texture = RenderText(text.c_str(), font, {0, 0, 0, 255});

    SDL_QueryTexture(texture, NULL, NULL, &container.w, &container.h);
    container.x = Window::Width() - container.w - 10;
    container.y = Window::Height() - container.h - 100;

    toRefresh = false;
}

void Hint::Render() {

    ms_toWait--;

    if(hintActive) {
        SDL_RenderCopy(Window::renderer, texture, NULL, &container);
    }
    if(ms_toWait == 0) {
        if(hintActive) {
            hintActive = false;
            ms_toWait = rand() % 300 + 300; // pocaka 10-15s preden prikaze novga
        }
        else {
            hintActive = true;
            toRefresh = true; // requests new text
            ms_toWait = HINT_TIME_TO_DISPLAY;
        }
    }

}


void Hint::Empty() {
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    text.clear();
}