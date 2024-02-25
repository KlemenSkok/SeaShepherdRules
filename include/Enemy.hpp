
// Enemy.hpp

// kitolovci

#pragma once

#include "Entity.hpp"
//#include "Vektor.hpp"


class Enemy : public Entity {

    static int ID_counter;

public:
    int enemy_ID;

    Enemy();
    ~Enemy();

    void Initialize() override;
    void CheckCollisions() override;
    void CheckBorders() override;
    void Update() override;
    void Render() override;


    //...
};
