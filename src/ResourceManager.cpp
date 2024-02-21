
// ResourceManager.cpp

#include "ResourceManager.hpp"
#include "Constants.hpp"
#include "Game.hpp"

#include <filesystem>

namespace fs = std::filesystem;


ResourceManager::ResourceManager() {
    //...
}

ResourceManager::~ResourceManager() {
    //...
}

SDL_Texture* ResourceManager::LoadTextures(std::string file, int currLevel) {
    //SDL_Surface *surface = IMG_Load(file);
    //SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
}

SDL_Texture* ResourceManager::LoadPlayerTexture() {
    SDL_Surface *surface = IMG_Load("../assets/images/player.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::_renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}