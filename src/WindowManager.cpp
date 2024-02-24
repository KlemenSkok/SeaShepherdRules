
// WindowManager.cpp


#include "WindowManager.hpp"

WindowManager::WindowManager() {
    window = nullptr;
    renderer = nullptr;    
}

WindowManager::~WindowManager() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
} 

void WindowManager::windowMaximize(SDL_Window *param_window) {
    SDL_MaximizeWindow(param_window);
}

void WindowManager::windowFullscreen(SDL_Window *param_window) {
    SDL_SetWindowFullscreen(param_window, SDL_WINDOW_FULLSCREEN);
}