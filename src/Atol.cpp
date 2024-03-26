
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
    // try loading texture from project directory (debugging)
    this->texture = LoadTexture("../../assets/images/level_2/atol.png");
    // or try loading it from final directory (final compiled version)
    if(this->texture == nullptr) {
        this->texture = LoadTexture("../assets/images/level_2/atol.png");
    }
    if(this->texture == nullptr) {
        Logger::Warning("Failed to load atoll texture");
    }

    // SDL_QueryTexture(texture, NULL, NULL, &container.w, &container.h);
    container.w = container.h = 0;
    container.x = rand() % (Window::Width() - container.w);
    container.y = rand() % (Window::Height() - container.h);
    
    hitbox.w = hitbox.h = 0;
    hitbox.x = container.x + (container.w - hitbox.w) / 2;
    hitbox.y = container.y + (container.h - hitbox.h) / 2;

    this->ticksCounter = 0;
    this->isVanishing = false;
    this->textureOpacity = 255;

    this->timeout = true;
    this->waitTimer = rand() % 150 + 1;
}

void Atol::CheckCollisions() {
    // check for collisions
}

void Atol::CheckBorders() {
    // check if entity is out of bounds
}

void Atol::Update() {
    
    if(timeout) { // wait before growing
        waitTimer--;
        if(waitTimer <= 0) {
            timeout = false; // start growing
            isVanishing = false;
            waitTimer = 0;
            ticksCounter = 0;
            textureOpacity = 255;

            // reset size
            container.w = 0;
            container.h = 0;
            hitbox.w = hitbox.h = 0;

            // reset opacity
            textureOpacity = 255;
            isVanishing = false;

            std::cout << "Atol st " << object_ID << " ma konc timeoutea\n";
        }
        Logger::Status("logger called");
        return;
    }
    // update atole size (++)
    this->ticksCounter++;

    if(!isVanishing) { // raste

        std::cout << "Atol st " << object_ID << " ima " << ticksCounter << "ticksov in raste\n";
        if(textureOpacity != 255) {
            textureOpacity = 255;
            SDL_SetTextureAlphaMod(this->texture, textureOpacity);
        }
        if(this->ticksCounter % 20 == 0) {
            int delta = 1;
            container.w += delta;

            // maintain aspect ratio
            SDL_Rect tmp;
            SDL_QueryTexture(this->texture, NULL, NULL, &tmp.w, &tmp.h);
            container.h = container.w * tmp.h / tmp.w;
            hitbox.w = container.w * 0.85;
            hitbox.h = container.h * 0.85;

            if(this->ticksCounter % 40 == 0) { // usak drug update       
                container.x -= delta;
                container.y -= delta;
            }
            hitbox.x = container.x + (container.w - hitbox.w) / 2;
            hitbox.y = container.y + (container.h - hitbox.h) / 2;
        }
        if(hitbox.w > 100) {
            isVanishing = true;
            std::cout << "ATOL " << object_ID << " DOSEGEL MAX VELIKOST\n";
        }
    }
    else { // že zrasel do max velikosti, zdej izginja
        Logger::Warning("KLICAN VANISHING!");
        if(this->ticksCounter % 5 == 0) {
            if(textureOpacity > 5) { // prevent underflow
                textureOpacity -= 5;
                Logger::Status("Zmanjšujem opacity za 5");
            }
            else { // reset
                //reposition
                container.x = rand() % (Window::Width() - container.w);
                container.y = rand() % (Window::Height() - container.h);
                hitbox.x = container.x + (container.w - hitbox.w) / 2;
                hitbox.y = container.y + (container.h - hitbox.h) / 2;

                // reset size
                container.w = 0;
                container.h = 0;
                hitbox.w = hitbox.h = 0;


                // reset opacity
                textureOpacity = 255;
                isVanishing = false;

                waitTimer = rand() % 100 + 1; // wait up to 5 secs before next apperarance
                timeout = true;
            }
            SDL_SetTextureAlphaMod(this->texture, textureOpacity);
        }
    }  
}

void Atol::Render() {
    if(!timeout) {
        Logger::Status("RENDERAM");
        SDL_RenderCopy(Window::renderer, this->texture, NULL, &container);

        // draw hitbox
        SDL_SetRenderDrawColor(Window::renderer, 0, 255, 0, 255);
        SDL_RenderDrawRect(Window::renderer, &hitbox);
        SDL_SetRenderDrawColor(Window::renderer, 255, 255, 255, 255);

        std::cout << "x, y: " << container.x << ", " << container.y << std::endl;
    }
}

SDL_Rect Atol::get_hitbox() {
    return hitbox;
}

bool Atol::operator==(const SDL_Rect &rect) const {
    return (
        (this->hitbox.x + this->hitbox.w >= rect.x) &&
        (this->hitbox.y + this->hitbox.h >= rect.y) &&
        (rect.x + rect.w >= this->hitbox.x) &&
        (rect.y + rect.h >= this->hitbox.y)
    );
}