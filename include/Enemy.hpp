
// Enemy.hpp

// kitolovci

#include "Entity.hpp"


class Enemy : public Entity {

    static int ID_counter;

public:
    int enemy_ID;

    Enemy(SDL_Texture *texture);
    ~Enemy();

    void CheckCollisions() override;
    void Update() override;
    void Render() override;

    //...
};