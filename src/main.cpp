
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
                currLevel = 1;
            }
        }
    }    
    
    game.cleanup();


    //std::vector<Whaler*> v;
    //Vektor<Whaler*> k;

/*     Vektor<Whaler*> v;
    for(int i = 0; i < 5; i++) {
        Whaler *tmp = new Whaler;
        tmp->Initialize();
        v.push_front(tmp);
    }
    v.erase_id(3);
    v.erase_at(0);
    std::cout << v.size() << std::endl;
    v.erase_at(7);
    v.clear();
    v.erase_at(7); */
 


    return 0;
}