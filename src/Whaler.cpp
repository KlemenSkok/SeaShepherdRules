
// Whaler.cpp

#include "Whaler.hpp"
#include "Constants.hpp"
#include "Utilities.hpp"
#include "Vektor.hpp"

#include <SDL2/SDL_render.h>
#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace Window;


int Whaler::ID_counter = 0;

Whaler::Whaler() {
    this->texture = nullptr;
    this->object_ID = Whaler::ID_counter;
    Whaler::ID_counter++;
	is_stopped = false;
	ms_atLastStop = ms_toWait = 0;
}

Whaler::~Whaler() {
    Logger::Status("Destroying Whaler");
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Whaler::Initialize() {
    this->texture = LoadTexture("../../assets/images/whaler.png");
    // get texture width and height
    SDL_QueryTexture(texture, NULL, NULL, &container.w, &container.h);
    container.x = rand() % (Window::Width() - container.w);
    container.y = rand() % (Window::Height() - container.h);
    hitbox.w = container.w * 0.85;
    hitbox.h = container.h * 0.85;
    hitbox.x = container.x + (container.w - hitbox.w) / 2;
    hitbox.y = container.y + (container.h - hitbox.h) / 2;
	dest_x = hitbox.x;
	dest_y = hitbox.y;
}

void Whaler::CheckCollisions() {
    // check collisions with other entities
}

void Whaler::CheckBorders() {
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

void Whaler::Update() {
    /*
    About:
        - uporabm ze napisano funkcijo za deseganje koordinate x,y
        - objekt se pocasi premika do destinacije
        - ko pride tja, se shrani cas prihoda in nastavi bool o ustavitvi na true
        - ko cas potece, gre bool na false
        - generirajo se nove koordinate
    */

   	if(is_stopped && (SDL_GetTicks64() - ms_atLastStop >= ms_toWait)) {
		// the wait time is up, get new destination
		is_stopped = false;
		generate_dest_coords();
	}
	else if(!is_stopped && hitbox.x == dest_x && hitbox.y == dest_y) {
		// got there, start waiting
		is_stopped = true;
		ms_atLastStop = SDL_GetTicks64();
		ms_toWait = rand() % 2500 + 1500;
	}
	else if(is_stopped && hitbox.x == dest_x && hitbox.y == dest_y) {
		// wait
	}
	else {
		update_movement(hitbox, dest_x, dest_y, PLAYER_SPEED);
	}

    // send changes to container 
    container.x = hitbox.x - (container.w - hitbox.w) / 2;
    container.y = hitbox.y - (container.h - hitbox.h) / 2;
}

void Whaler::Render() {
    SDL_RenderCopy(Window::renderer, this->texture, NULL, &container);
	//std::cout << "Whaler " << object_ID << " coords: " << hitbox.x << ", " << hitbox.y << std::endl;
	//std::cout << "Whaler " << object_ID << " destination coords: " << dest_x << ", " << dest_y << std::endl;
    
    // draw hitbox for debugging
    SDL_SetRenderDrawColor(Window::renderer, 0xFF, 0x00, 0x00, 0xFF); // red
    SDL_RenderDrawRect(Window::renderer, &hitbox);
    SDL_SetRenderDrawColor(Window::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

/*
omejitve:
    3*velikost_texture <= oddaljenost <= 4*velikost_texture (glej whiteboard)
*/
void Whaler::generate_dest_coords() {
/*     bool ok = false;
    double texture_size = sqrt(container.w * container.w + container.h * container.h); // diagonally
    double min_distance = texture_size * 3;
    double max_distance = texture_size * 4;

    double angle = rand() % 360; */

    // zacasno samo random koordinate okna
    dest_x = rand() % (Window::Width() - hitbox.w);
    dest_y = rand() % (Window::Height() - hitbox.h);

}

SDL_Rect Whaler::get_hitbox() {
    return this->hitbox;
}