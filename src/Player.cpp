
// Player.cpp

#include "Player.hpp"
#include "Constants.hpp"
#include "Utilities.hpp"
#include "Logger.hpp"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <cmath>

using namespace Window;

Player::Player() {

}

Player::~Player() {
    Logger::Status("Destroying player");
    SDL_DestroyTexture(texture);
}

void Player::Initialize() {
    // relativna pot do slike glede na output folder (po novem bin/debug)
    this->texture = LoadTexture("../../assets/images/player.png");
    if(this->texture != nullptr) {
        Logger::Success("Loaded player texture");
    }
    else Logger::Error("Failed to load player texture");
    
    SDL_QueryTexture(texture, NULL, NULL, &container.w, &container.h); // get texture dimensions
    container.x = INITIAL_WINDOW_WIDTH / 2 - container.w / 2;
    container.y = INITIAL_WINDOW_HEIGHT / 2 - container.h / 2;
    hitbox.w = container.w * 0.85;
    hitbox.h = container.h * 0.85;
    hitbox.x = container.x + (container.w - hitbox.w) / 2;
    hitbox.y = container.y + (container.h - hitbox.h) / 2;

    health = 100;

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

bool Player::operator==(const SDL_Rect& rect) {
    return (
        (this->hitbox.x + this->hitbox.w >= rect.x) &&
        (this->hitbox.y + this->hitbox.h >= rect.y) &&
        (rect.x + rect.w >= this->hitbox.x) &&
        (rect.y + rect.h >= this->hitbox.y)
    );
}

void Player::avoid_entity(const SDL_Rect& rect) {
    // izračunamo prekrivanje na vsaki strani
    int overlapLeft = hitbox.x + hitbox.w - rect.x;
    int overlapRight = rect.x + rect.w - hitbox.x;
    int overlapTop = hitbox.y + hitbox.h - rect.y;
    int overlapBottom = rect.y + rect.h - hitbox.y;

    // najdemo najmanjse prekrivanje
    int minOverlapX = std::min(overlapLeft, overlapRight);
    int minOverlapY = std::min(overlapTop, overlapBottom);

    if (minOverlapX < minOverlapY) {
        // Adjust horizontally
        if (overlapLeft < overlapRight) {
            // Move player to the left of the rect
            hitbox.x -= overlapLeft;
        } else {
            // Move player to the right of the rect
            hitbox.x += overlapRight;
        }
    } else {
        // Adjust vertically
        if (overlapTop < overlapBottom) {
            // Move player above the rect
            hitbox.y -= overlapTop;
        } else {
            // Move player below the rect
            hitbox.y += overlapBottom;
        }
    }
}

SDL_Rect Player::get_hitbox() {
    return this->hitbox;
}

short Player::get_health() {
    return this->health;
}

void Player::recieve_damage(short damage) {
    this->health -= damage;
}

