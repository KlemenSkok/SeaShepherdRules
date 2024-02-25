
// main.cpp

#include "Game.hpp"
#include "Vektor.hpp"
#include "Enemy.hpp"
#include "Constants.hpp"

#include <iostream>
#include <ctime>
#include <filesystem>
#include <string>



int main(int argc, char* argv[]) {
    srand(time(NULL));

    Game game;
    int currLevel = 1;
    int prevCode = EXIT_CODE_CONTINUE;

    game.init();

    while(prevCode != EXIT_CODE_QUIT) {

        prevCode = game.run(currLevel);

        if(prevCode == EXIT_CODE_RETRY) {
            continue;
        }
        else if(prevCode == EXIT_CODE_CONTINUE) {
            currLevel++;
            if(currLevel > NUMBER_OF_LEVELS) {
                currLevel = 1;
            }
        }
    }    
    
    game.cleanup();



    return 0;
}