
// Whaler.hpp

// (kitolovci)

#pragma once

#include "Entity.hpp"

#include <SDL2/SDL_image.h>

/*
About:
    - Cilj igre je, da igralec lovi kitolovce.
    - premikajo se po polju, igralcu niso vidni izven določenega radija
    - sami se ne morejo braniti
    - če sta dva dovolj blizu, se lahko postavita skupaj
    - takrat lahko poškodujeta igralca
*/

class Whaler : public Entity {

    static int ID_counter;
    //int health;

public:
    int object_ID;

    Whaler();
    ~Whaler();

    void Initialize() override;
    void CheckCollisions() override;
    void CheckBorders() override;
    void Update() override;
    void Render() override;

};

//#include "Vektor.hpp"

//template class Vektor<Whaler*>;