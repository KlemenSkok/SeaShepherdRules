 
// Player.hpp

//igralec

#pragma once

#include "Entity.hpp"

//#include <SDL2/SDL_image.h>

/*
About:
    - igralec lovi kitolovce
    - ubije jih tako, da se jih dotakne
    - če bo cajt -> orožje na delč?? --> edit: ne bo cajt
*/

class Player : public Entity {

    short health;

public:
    Player();
    ~Player();

    void Initialize() override;
    void CheckCollisions() override;
    void CheckBorders() override;
    void Update() override;
    void Render() override;

    void UpdateMouseMovement(); // TO-DO
    bool operator==(const SDL_Rect&);
    void avoid_entity(const SDL_Rect&);

    SDL_Rect get_hitbox();
    short get_health();
    void recieve_damage(short);
    //...
};