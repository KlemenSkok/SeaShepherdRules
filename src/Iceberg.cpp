
// Iceberg.cpp

#include "Iceberg.hpp"

#include <cstdlib>



double Iceberg::direction = 0;
int Iceberg::ID_counter = 0;

Iceberg::Iceberg() {
    this->texture = nullptr;
    this->object_ID = Iceberg::ID_counter;
    Iceberg::ID_counter++;
}

Iceberg::~Iceberg() {
    Logger::Status("Destroying iceberg");
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Iceberg::Initialize() {
    // try loading texture from project directory (debugging)
    this->texture = LoadTexture("../../assets/images/level_1/iceberg.png");
    // or try loading it from final directory (final compiled version)
    if(this->texture == nullptr) {
        this->texture = LoadTexture("../assets/images/level_1/iceberg.png");
    }
    if(this->texture == nullptr) {
        Logger::Warning("Failed to load iceberg texture");
    }
    
    SDL_QueryTexture(texture, NULL, NULL, &container.w, &container.h);
    container.x = rand() % (Window::Width() - container.w);
    container.y = rand() % (Window::Height() - container.h);
    hitbox.w = container.w * 0.85;
    hitbox.h = container.h * 0.85;
    hitbox.x = container.x + (container.w - hitbox.w) / 2;
    hitbox.y = container.y + (container.h - hitbox.h) / 2;

    this->ticksCounter = 0;

    std::cout << "Iceberg direction: " << Iceberg::direction <<std::endl;
}

void Iceberg::CheckCollisions() {
    // tega ne rabmo
}

void Iceberg::CheckBorders() {
    // če ledena gora zaide s polja, navidezno izgine, nato se premakne na drugo stran in ponovi
    if(hitbox.x < -hitbox.w && direction > 90 && direction < 270) {
        hitbox.x = Window::Width() + hitbox.w;
        hitbox.y = rand() % (Window::Height() - hitbox.h);
    }
    if(hitbox.x > Window::Width() && (direction < 90 || direction > 270)) {
        hitbox.x = -hitbox.w * 2;
        hitbox.y = rand() % (Window::Height() - hitbox.h);
    }
    if(hitbox.y < -hitbox.h && direction > 0 && direction < 180) {
        hitbox.y = Window::Height() + hitbox.h;
        hitbox.x = rand() % (Window::Width() - hitbox.w);
    }
    if(hitbox.y > Window::Height() && direction > 180) {
        hitbox.y = -hitbox.h * 2;
        hitbox.x = rand() % (Window::Width() - hitbox.w);
    }
}

void Iceberg::Update() {
        this->ticksCounter++;

        if(ticksCounter % 5 == 0) { // usak peti frame
            double delta_x = ICEBERG_SPEED * cos(direction * M_PI / 180.0),
                delta_y = -ICEBERG_SPEED * sin(direction * M_PI / 180.0);

            hitbox.x += static_cast<int>(delta_x);
            hitbox.y += static_cast<int>(delta_y);

            container.x = hitbox.x - (container.w - hitbox.w) / 2;
            container.y = hitbox.y - (container.h - hitbox.h) / 2;            
        }
}

void Iceberg::Render() {
    SDL_RenderCopy(Window::renderer, this->texture, NULL, &container);
}

SDL_Rect Iceberg::get_hitbox() {
    return this->hitbox;
}

void Iceberg::setDirection(int d) {
    Iceberg::direction = d % 360;
}