
// ResourceManager.cpp

#include "ResourceManager.hpp"
#include "Constants.hpp"
#include "Utilities.hpp"

#include <filesystem>
#include <iostream>

using namespace Window;
namespace fs = std::filesystem;


ResourceManager::ResourceManager() {
    //...
}

ResourceManager::~ResourceManager() {
    //...
}

SDL_Texture* ResourceManager::LoadTextures(std::string file, int currLevel) {
    //SDL_Surface *surface = IMG_Load(file);
    //SDL_Texture *texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
    return nullptr;
}

SDL_Texture* ResourceManager::LoadPlayerTexture() {
    SDL_Surface *surface = IMG_Load("../assets/images/player.png");
    if(surface == NULL) {
        std::cout << "Failed to load player texture\n";
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}