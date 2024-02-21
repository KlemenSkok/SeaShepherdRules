
// LevelManager.hpp

#pragma once

#include "Level.hpp"
#include <vector>

class LevelManager {

    int currentLevel;
    std::vector<Level> levels;

public:
    LevelManager();

    void LoadLevels();
    void SwitchToLevel(int levelNumber);
    void UpdateCurrentLevel();
    void RenderCurrentLevel();
};