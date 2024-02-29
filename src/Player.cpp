// Player.cpp

#include "Player.hpp"
#include "Constants.hpp"
#include "Utilities.hpp"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <cmath>

using namespace Window;

Player::Player() {

}

Player::~Player() {
    SDL_DestroyTexture(texture);
}

void Player::Initialize() {
    this->texture = LoadTexture("../assets/images/player.png");
    SDL_QueryTexture(texture, NULL, NULL, &container.w, &container.h); // get texture dimensions
    container.x = INITIAL_WINDOW_WIDTH / 2 - container.w / 2;
    container.y = INITIAL_WINDOW_HEIGHT / 2 - container.h / 2;
    hitbox.w = container.w * 0.85;
    hitbox.h = container.h * 0.85;
    hitbox.x = container.x + (container.w - hitbox.w) / 2;
    hitbox.y = container.y + (container.h - hitbox.h) / 2;
}

void Player::CheckCollisions() {
    // check for collisions
}

void Player::CheckBorders() {
    if(hitbox.x < 0) {
        hitbox.x = 0;
    }
    if(hitbox.x + hitbox.w > Window::Width()) {
        hitbox.x = Window::Width() - hitbox.w;
    }

    if(hitbox.y < 0) {
        hitbox.y = 0;
    }
    if(hitbox.y + hitbox.h > Window::Height()) {
        hitbox.y = Window::Height() - hitbox.h;
    }

}

void Player::Update() {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    float deltas[2] = {0.0f, 0.0f}; // x, y

    if (keystate[SDL_SCANCODE_W] && !keystate[SDL_SCANCODE_S])
        deltas[1] = -1.0f;
    else if (!keystate[SDL_SCANCODE_W] && keystate[SDL_SCANCODE_S])
        deltas[1] = 1.0f;

    if (keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_D])
        deltas[0] = -1.0f;
    else if (!keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_D])
        deltas[0] = 1.0f;

    // Normalize the vector (if it is not a zero vector)
    float length = sqrt(deltas[0] * deltas[0] + deltas[1] * deltas[1]);
    if (length != 0.0f) {
        deltas[0] /= length;
        deltas[1] /= length;
    }

    // Update movement
    hitbox.x += deltas[0] * PLAYER_SPEED;
    hitbox.y += deltas[1] * PLAYER_SPEED;

    container.x = hitbox.x - (container.w - hitbox.w) / 2;
    container.y = hitbox.y - (container.h - hitbox.h) / 2;

    // delete keystate; // free memory
}

void Player::Render() {
    SDL_RenderCopy(Window::renderer, texture, NULL, &container);

    // draw hitbox for debugging
    SDL_SetRenderDrawColor(Window::renderer, 0x00, 0x00, 0xFF, 0xFF); // blue
    SDL_RenderDrawRect(Window::renderer, &hitbox);
    SDL_SetRenderDrawColor(Window::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}


