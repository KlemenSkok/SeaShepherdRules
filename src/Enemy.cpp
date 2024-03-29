
// Enemy.cpp

#include "Enemy.hpp"
#include "Constants.hpp"
#include "Utilities.hpp"
#include "Vektor.hpp"

#include <SDL2/SDL_render.h>
#include <cstdlib>
#include <iostream>

using namespace Window;


int Enemy::ID_counter = 0;

Enemy::Enemy() {
    texture = nullptr;
    object_ID = Enemy::ID_counter;
    Enemy::ID_counter++;
}

Enemy::~Enemy() {
    std::cout << "Destroying enemy " << object_ID << std::endl;
    SDL_DestroyTexture(texture);
}

void Enemy::Initialize() {
    this->texture = LoadTexture("../assets/images/player.png");
    // get texture width and height
    SDL_QueryTexture(texture, NULL, NULL, &container.w, &container.h);
    container.x = rand()%INITIAL_WINDOW_WIDTH;
    container.y = rand()%INITIAL_WINDOW_HEIGHT;
    hitbox.w = container.w * 0.85;
    hitbox.h = container.h * 0.85;
    hitbox.x = container.x + (container.w - hitbox.w) / 2;
    hitbox.y = container.y + (container.h - hitbox.h) / 2;
}

void Enemy::CheckCollisions() {
    // check for collisions
}

void Enemy::CheckBorders() {
    // check for borders
}

void Enemy::Update() {
    // update movement
}

void Enemy::Render() {
    // render enemy
}

//-------------------------------------------------//
//              overloads for Vektor               //
//-------------------------------------------------//

#include "Vektor.hpp"

template <>
void Vektor<Enemy*>::erase_id(int id) {
    if(start == nullptr) {
        Logger::Warning("@ Vektor - cannot erase from empty list");
    }
    else {
        Node *tmp = start;
        while(tmp != nullptr && tmp->data->object_ID != id) {
            tmp = tmp->next;
        }
        if(tmp == nullptr) {
            Logger::Error("@ Vektor - id not found");
        }
        else if(tmp == start) { // first element
            if(start == konc) { //only element
                start = konc = nullptr;
                delete tmp->data;
                delete tmp;
            }
            else { // just first
                start = start->next;
                start->prev = nullptr;
                delete tmp->data;
                delete tmp;
            }
        }
        else if(tmp == konc) { // last element
            konc = konc->prev;
            konc->next = nullptr;
            delete tmp->data;
            delete tmp;
        }
        else {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            delete tmp->data;
            delete tmp;
        }
    }
}

template <>
void Vektor<Enemy*>::clear() {
    while(start != nullptr) {
        Node *tmp = start;
        start = start->next;
        delete tmp->data;
        delete tmp;
    }
    start = konc = nullptr;
}

template<>
Vektor<Enemy*>::~Vektor() {
    clear();
}

template <>
void Vektor<Enemy*>::pop_back() {
    if(start == nullptr) {
        Logger::Warning("@ Vektor - cannot erase from empty list");
    }
    else if(start == konc) {
        delete start->data;
        delete start;
        start = konc = nullptr;
    }
    else {
        Node *tmp = konc;
        konc = konc->prev;
        konc->next = nullptr;
        delete tmp->data;
        delete tmp;
    }
}

template <>
void Vektor<Enemy*>::pop_front() {
    if(start == nullptr) {
        Logger::Warning("@ Vektor - cannot erase from empty list");
    }
    else if(start == konc) {
        delete start->data;
        delete start;
        start = konc = nullptr;
    }
    else {
        Node *tmp = konc;
        start = start->next;
        start->prev = nullptr;
        delete tmp->data;
        delete tmp;
    }
}

template <>
void Vektor<Enemy*>::erase_at(int index) {
    if(start == nullptr) {
        Logger::Warning("@ Vektor - cannot erase from empty list");
    }
    else if(index < 0 || index >= size()) {
        Logger::Error("@ Vektor - index out of range");
    }
    else {
        Node *tmp = start;
        while(index > 0) {
            tmp = tmp->next;
            index--;
        }
        if(tmp == start) {
            if(start == konc) {
                start = konc = nullptr;
                delete tmp->data;
                delete tmp;
            }
            else {
                start = start->next;
                start->prev = nullptr;
                delete tmp->data;
                delete tmp;
            }
        }
        else if(tmp == konc) {
            konc = konc->prev;
            konc->next = nullptr;
            delete tmp->data;
            delete tmp;
        }
        else {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            delete tmp->data;
            delete tmp;
        }
    }
}
