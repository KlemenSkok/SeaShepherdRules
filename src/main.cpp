
// main.cpp

#include "Game.hpp"


#include <iostream>
#include <ctime>


int main(int argc, char* argv[]) {
    srand(time(NULL));

    Game game;
    int currLevel = 1;
    int prevCode = EXIT_CODE_CONTINUE;

    game.init();

    while(prevCode != EXIT_CODE_QUIT) {

        prevCode = game.run(currLevel);
        
        switch(prevCode) {
            case EXIT_CODE_CONTINUE:
                currLevel++;
                break;
            case EXIT_CODE_RESTART:
                currLevel = 1;
                break;
            case EXIT_CODE_RETRY:
                break;
        }
    }
    
    game.cleanup();

    return 0;
}