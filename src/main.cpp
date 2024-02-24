#include "Game.hpp"
#include "Vektor.hpp"

#include <iostream>
#include <ctime>


int main(int argc, char* argv[]) {
    srand(time(NULL));
/* 
    Game game;

    game.init();
    game.run();
    game.cleanup();
 */

    Vektor<int> v;
    v.push_back(69);
    v.push_front(42);
    v.push_front(123);
    v.push_back(420);

    std::cout << "Size: " << v.size() << std::endl;
    for(int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " " << v.at(i) <<std::endl;
    }


    return 0;
}