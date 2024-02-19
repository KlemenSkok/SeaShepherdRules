
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