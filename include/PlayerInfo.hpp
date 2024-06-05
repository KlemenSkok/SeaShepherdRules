
// PlayerInfo.hpp

#pragma once

#include "Utilities.hpp"
#include "Logger.hpp"
#include "Constants.hpp"

#include <cstdint>
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include <SDL2/SDL_ttf.h>


class PlayerInfo {

    uint8_t max_username_length = 20;
    char username[21];
    uint32_t score[3];


public:
    PlayerInfo() = default;

    void Initialize();
    void Get();
    void Save();
    void SetLevelScore(uint8_t levelNum, int score);
    void Clean();

};