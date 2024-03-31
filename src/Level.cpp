
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
            for(int i = 0; i < BASE_PIRATE_COUNT; i++) {
                Pirate *p = new Pirate;
                p->Initialize();
                pirates.push_back(p);
            }
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
        whalers[i]->CheckPlayerDistance(player.get_hitbox());
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
    for(int i = 0; i < pirates.size(); i++) {
        pirates[i]->CheckBorders();
        pirates[i]->Update();
    }

    player.CheckBorders();
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
    for(int i = 0; i < atols.size(); i++) {
        atols[i]->Render();
    }
    for(int i = 0; i < pirates.size(); i++) {
        pirates[i]->Render();
    }

    player.Render();
}

void Level::Cleanup() {
    whalers.clear();
    icebergs.clear();
    atols.clear();
    pirates.clear();
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
    //check collisions between player and atols
    for(int i = 0; i < atols.size(); i++) {
        if(atols[i]->get_hitbox() != nullptr && player == *atols[i]->get_hitbox()) {
            player.avoid_atol(atols[i]->get_hitbox());
        }
    }
}