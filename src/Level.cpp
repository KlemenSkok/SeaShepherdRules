
// Level.cpp

#include "Level.hpp"

Level::Level(int levelNum) {
    player.Initialize();

    // create whalers
    initialWhalerCount = BASE_WHALER_COUNT + levelNum*2;
    for(int i = 0; i < initialWhalerCount; i++) {
        Whaler *w = new Whaler;
        w->Initialize();
        whalers.push_back(w);
    }

    switch(levelNum) {
        case 1:
            // set direction of the icebergs
            Iceberg::setDirection(rand() % 360);
            // generate icebergs
            for(int i = 0; i < BASE_ICEBERG_COUNT; i++) {
                Iceberg *l = new Iceberg;
                l->Initialize();
                icebergs.push_back(l);
            }
            break;
        case 2:
            // generate atols
            for(int i = 0; i < BASE_ATOL_COUNT; i++) {
                Atol *a = new Atol;
                a->Initialize();
                atols.push_back(a);
            }
            break;
        case 3:
            // generate pirates
            break;
        default:
            Logger::Error("@ Level - Invalid level number");
    }
}

Level::~Level() {
    // destructor   
}

int Level::Update() {

    checkCollisions();

    for(int i = 0; i < whalers.size(); i++) {
        whalers[i]->CheckBorders();
        //whalers[i]->CheckCollisions();
        whalers[i]->Update();
    }
    for(int i = 0; i < icebergs.size(); i++) {
        icebergs[i]->CheckBorders();
        icebergs[i]->Update();
    }
    for(int i = 0; i < atols.size(); i++) {
        atols[i]->CheckBorders();
        atols[i]->Update();
    }

    player.CheckBorders();
    //player.CheckCollisions();
    player.Update();

    if(whalers.empty()) {
        return STATE_VICTORY_SCREEN; // killed all whalers, won
    }
    return STATE_GAME_SCREEN; // not finished, continue playing
}

void Level::Render() {
    for(int i = 0; i < whalers.size(); i++) {
        whalers[i]->Render();
    }
    for(int i = 0; i < icebergs.size(); i++) {
        icebergs[i]->Render();
    }
    player.Render();
}

void Level::Cleanup() {
    whalers.clear();
    icebergs.clear();
}

void Level::checkCollisions() {
    // check collision between player and whalers 
    for(int i = 0; i < whalers.size(); i++) {
        if(player == whalers[i]->get_hitbox()) {
            whalers.erase_id(whalers[i]->object_ID);
            i--;
        }
    }
    //check collisions between player and icebergs
    for(int i = 0; i < icebergs.size(); i++) {
        if(player == icebergs[i]->get_hitbox()) {
            player.avoid_iceberg(icebergs[i]->get_hitbox());
        }
    }

}