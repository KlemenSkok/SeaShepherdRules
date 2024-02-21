
// Enemy.hpp

// kitolovci

#include "Entity.hpp"

class Enemy : public Entity {


public:
    Enemy();
    ~Enemy();

    void CheckCollisions() override;
    void Update() override;
    void Render(SDL_Texture *texture) override;

    //...
};