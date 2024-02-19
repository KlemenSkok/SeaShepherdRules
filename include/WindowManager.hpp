
// WindowManager.hpp

/*
Deals with:
- Creating and destroying the window
- Handling the window's events
- resizing the window
*/

// ne vem cist ce je nujen

#pragma once

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

class WindowManager {
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    WindowManager();
    ~WindowManager();


    //...
};