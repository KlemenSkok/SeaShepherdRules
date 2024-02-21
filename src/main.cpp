#include <iostream>
#include "Game.hpp"


int main(int argc, char* argv[]) {

    Game game;

    game.init();
    game.run();
    game.cleanup();


    return 0;
}