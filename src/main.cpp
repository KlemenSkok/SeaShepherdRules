
// main.cpp

#include "Game.hpp"
#include "Vektor.hpp"
#include "Enemy.hpp"
#include "Constants.hpp"

#include <iostream>
#include <ctime>



int main(int argc, char* argv[]) {
    srand(time(NULL));

    Game game;

    game.init();
    game.run();
    game.cleanup();
 
    return 0;
}