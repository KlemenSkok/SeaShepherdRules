
// Atol.cpp

#include "Atol.hpp"



int Atol::ID_counter = 0;

Atol::Atol() {
    this->texture = nullptr;
    this->object_ID = Atol::ID_counter;
    Atol::ID_counter++;
}

Atol::~Atol() {
    Logger::Status("Destroying Atol");
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Atol::Initialize() {
    // load texture
    //...
}

void Atol::CheckCollisions() {
    // check for collisions
}

void Atol::CheckBorders() {
    // check if entity is out of bounds
}

void Atol::Update() {
    // update entity
}

void Atol::Render() {
    // render entity
}
