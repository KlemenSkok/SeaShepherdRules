
// Level.cpp

#include "Level.hpp"

Level::Level(int levelNum) {
    player.Initialize();

    switch(levelNum) {
        case 1:
            // create whalers
            numWhalers = BASE_WHALER_COUNT + levelNum*2;
            for(int i = 0; i < numWhalers; i++) {
                Whaler *w = new Whaler;
                w->Initialize();
                whalers.push_back(w);
            }

            break;
        case 2:

            break;
        case 3:

            break;
        default:
            Logger::Error("@ Level - Invalid level number");
    }
}

Level::~Level() {
    // destructor   
}

void Level::Update() {
    for(int i = 0; i < whalers.size(); i++) {
        whalers[i]->CheckBorders();
        whalers[i]->CheckCollisions();
        whalers[i]->Update();
    }
    player.CheckBorders();
    player.CheckCollisions();
    player.Update();

}

void Level::Render() {
    for(int i = 0; i < whalers.size(); i++) {
        whalers[i]->Render();
    }
    player.Render();
}

void Level::Cleanup() {
    whalers.clear();
}
