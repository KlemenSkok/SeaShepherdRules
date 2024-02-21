
// ResourceManager.hpp

#pragma once

#include "Constants.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>


class ResourceManager {


public:
    ResourceManager();
    ~ResourceManager();

    static SDL_Texture* LoadTextures(std::string file, int currLevel); // odvisni od levela
    static SDL_Texture* LoadPlayerTexture(); // neodvisen od levela
    
    //...
};