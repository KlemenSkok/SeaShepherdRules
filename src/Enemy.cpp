
// Enemy.cpp

#include "Enemy.hpp"
#include "Constants.hpp"
#include "Utilities.hpp"

#include <SDL2/SDL_render.h>
#include <cstdlib>

using namespace Window;


int Enemy::ID_counter = 0;

Enemy::Enemy(SDL_Texture *texture) {
    this->texture = texture;
    SDL_QueryTexture(texture, NULL, NULL, &container.w, &container.h);
    container.x = rand()%INITIAL_WINDOW_WIDTH;
    container.y = rand()%INITIAL_WINDOW_HEIGHT;
    hitbox.w = container.w * 0.85;
    hitbox.h = container.h * 0.85;
    hitbox.x = container.x + (container.w - hitbox.w) / 2;
    hitbox.y = container.y + (container.h - hitbox.h) / 2;
}

Enemy::~Enemy() {
    SDL_DestroyTexture(texture);
}

void Enemy::CheckCollisions() {
    // check for collisions
}

void Enemy::Update() {
    // update movement
}

void Enemy::Render() {
    // render enemy
}