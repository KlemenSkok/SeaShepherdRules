
// Utilities.hpp

//#pragma once

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

// Commonly used functions and structures

void update_movement(SDL_Rect &rect, int dest_x, int dest_y, int speed);

SDL_Texture *LoadTexture(const char *path);

void format_path(char *path);


// window management
namespace Window {
        extern SDL_Window *window;
        extern SDL_Renderer *renderer;

        void Create();
        void Destroy();

        void Maximize();
        void Fullscreen();

        int Width();
        int Height();
}

/*
? extern <variable>
*   The extern keyword, when used in a variable declaration, 
*   tells the compiler that the variable is declared but not defined in the current translation unit. 
*   Instead, the variable is defined elsewhere (usually in another translation unit), 
*   and the linker will resolve the actual definition during the linking phase.
*/