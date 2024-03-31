
// Pirate.cpp

#include "Pirate.hpp"
#include "Constants.hpp"
#include "Utilities.hpp"
#include "Vektor.hpp"

#include <SDL2/SDL_render.h>
#include <cstdlib>
#include <iostream>

using namespace Window;


int Pirate::ID_counter = 0;

Pirate::Pirate() {
    this->texture = nullptr;
    this->object_ID = Pirate::ID_counter;
    Pirate::ID_counter++;
    
    is_stopped = false;
    ms_atLastStop = ms_toWait = 0;
    player_detected = false;
}

Pirate::~Pirate() {
    std::cout << "Destroying pirate " << object_ID << std::endl;
    SDL_DestroyTexture(texture);
}

void Pirate::Initialize() {

    texture = LoadTexture("../../assets/images/level_3/pirate.png");
    if(texture == nullptr) {
        texture = LoadTexture("../assets/images/level_3/pirate.png");
    }
    if(texture == nullptr) {
        Logger::Warning("Failed to load pirate texture");
    }

//    container.w = container.h = 0;
    SDL_QueryTexture(texture, NULL, NULL, &container.w, &container.h);

    container.x = rand() % (Window::Width() - container.w);
    container.y = rand() % (Window::Height() - container.h);

//  hitbox.w = hitbox.h = 0;
    hitbox.w = container.w;
    hitbox.h = container.h ;

    hitbox.x = container.x + (container.w - hitbox.w) / 2;
    hitbox.y = container.y + (container.h - hitbox.h) / 2;

    dest_x = hitbox.x;
    dest_y = hitbox.y;

}

void Pirate::CheckCollisions() {
    // check for collisions
}

void Pirate::CheckBorders() {
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

void Pirate::Update() {
    /*
    About:
        - uporabi ze napisano funkcijo za sledenje koordinatam
        - ko igralca ne zazna:
            -> random movement, kot pri kitolovcu
        - ko je igralec zaznan:
            -> nek bool da ga je zaznal in se mu približuje
            -> pride do igralca, se ga dotakne, to mu (igralcu) vzame neki HPja
            -> pobegne

        - igralec ga ne more uničit
        - je hitrejši od igralca, zato se mu ne da uidt  
    */

   if(player_detected) {
        
        // top priority

    }
   	else if(is_stopped && (SDL_GetTicks64() - ms_atLastStop >= ms_toWait)) {
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
		update_movement(hitbox, dest_x, dest_y, PIRATE_IDLE_SPEED);
	}


    // send changes to container 
    container.x = hitbox.x - (container.w - hitbox.w) / 2;
    container.y = hitbox.y - (container.h - hitbox.h) / 2;

}


void Pirate::Render() {
    if(SDL_RenderCopy(Window::renderer, texture, NULL, &container) < 0) {
        Logger::Error("Failed to render pirate");
    }

    // hitbox for debugging
    SDL_SetRenderDrawColor(Window::renderer, 255, 255, 0, 255);
    SDL_RenderDrawRect(Window::renderer, &hitbox);
    SDL_SetRenderDrawColor(Window::renderer, 255, 255, 255, 255);
}


void Pirate::generate_dest_coords() {

    // zacasno, tole je treba izbolsat
    dest_x = rand() % (Window::Width() - container.w);
    dest_y = rand() % (Window::Height() - container.h);
}

void Pirate::CheckPlayerDistance(SDL_Rect player) {
    if(std::hypot(hitbox.x - player.x, hitbox.y - player.y) < 75.0) {
        player_detected = true;
    }
    else {
        player_detected = false;
    }
}