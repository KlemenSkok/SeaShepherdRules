
// PlayerInfo.hpp

#pragma once

#include "Utilities.hpp"
#include "Logger.hpp"
#include "Constants.hpp"




class PlayerInfo {

    const static uint8_t max_username_length = 20;
    static LeaderboardEntry *player;


public:
    PlayerInfo() = default;

    static void Initialize();
    static void Get();
    static void SetLevelScore(uint8_t levelNum, double time);
    static void Clean();
    static LeaderboardEntry* dump();

};


class Leaderboard {

public:
    Leaderboard() = default;

    static void AddEntry(LeaderboardEntry *entry);
    static void Display();
};