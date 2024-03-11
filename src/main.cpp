
// main.cpp

#include "Constants.hpp"
#include "Logger.hpp"
#include "Enemy.hpp"
//#include "Whaler.hpp"
#include "Vektor.hpp"
#include "Game.hpp"


#include <iostream>
#include <ctime>
#include <filesystem>
#include <string>

#include <vector>


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
                //currLevel = 1;
                break;
            }
        }
    }
    
    game.cleanup();


    return 0;
}