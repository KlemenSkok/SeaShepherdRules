
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

    isVanishing = false;
    textureOpacity = 255;

    timeout = true;
    ticksCounter = rand() % 1500 + 1;
}

void Atol::CheckCollisions() {
    // check for collisions
}

void Atol::CheckBorders() {
    // check if entity is out of bounds
}

void Atol::Update() {

    if(timeout) { // wait before growing
        ticksCounter--;
        if(ticksCounter <= 0) {

            // reset size
            container.w = container.h = 0;
            hitbox.w = hitbox.h = 0;

            // reposition
            container.x = rand() % (Window::Width() - container.w);
            container.y = rand() % (Window::Height() - container.h);
            hitbox.x = container.x + (container.w - hitbox.w) / 2;
            hitbox.y = container.y + (container.h - hitbox.h) / 2;
            
            // reset flags
            timeout = false;
            isVanishing = false;
            ticksCounter = 0;
            textureOpacity = 255;

            maxSize = rand() % 200 + 51;
        }
        return;
    }
    // update atole size (++)
    ticksCounter++;

    if(!isVanishing) { // raste

        if(textureOpacity != 255) {
            textureOpacity = 255;
            SDL_SetTextureAlphaMod(this->texture, textureOpacity);
        }
        if(ticksCounter % 20 % 5 == 0) {
            int delta = 1;
            container.w += delta;

            // maintain aspect ratio
            SDL_Rect tmp;
            SDL_QueryTexture(this->texture, NULL, NULL, &tmp.w, &tmp.h);
            container.h = container.w * tmp.h / tmp.w;
            hitbox.w = container.w * 0.85;
            hitbox.h = container.h * 0.85;

            if(ticksCounter % 40 == 0) { // usak drug update       
                container.x -= delta;
                container.y -= delta;
            }
            hitbox.x = container.x + (container.w - hitbox.w) / 2;
            hitbox.y = container.y + (container.h - hitbox.h) / 2;
        }
        if(hitbox.w > maxSize) {
            isVanishing = true;
        }
    }
    else { // že zrasel do max velikosti, zdej izginja
        if(ticksCounter % 10 == 0) {
            if(textureOpacity > 5) { // prevent underflow
                textureOpacity -= 5;
            }
            else { // start waiting
                ticksCounter = rand() % 500 + 1;
                timeout = true;
                textureOpacity = 255;
                hitbox.h = hitbox.w = 0;
                container.h = container.w = 0;
                hitbox.x = hitbox.y = container.x = container.y = 0;
            }
            SDL_SetTextureAlphaMod(this->texture, textureOpacity);
        }
    }  
}

void Atol::Render() {
    if(!timeout) {
        SDL_RenderCopy(Window::renderer, this->texture, NULL, &container);

        // draw hitbox
/*         SDL_SetRenderDrawColor(Window::renderer, 0, 255, 0, 255);
        SDL_RenderDrawRect(Window::renderer, &hitbox);
        SDL_SetRenderDrawColor(Window::renderer, 255, 255, 255, 255); */
    }
}

SDL_Rect Atol::get_hitbox() { // ce je ukloplen timeout, lahko player ignorira atol
    /* if(!timeout)
        return &hitbox;
    return nullptr; */
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


struct ReplayObject Atol::dumpObject() {
    struct ReplayObject obj;
    obj.type = TYPE_ATOL;
    obj.container = this->container;

    return obj;
}