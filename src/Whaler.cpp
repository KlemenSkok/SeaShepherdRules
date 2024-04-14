
// Whaler.cpp

#include "Whaler.hpp"
#include "Constants.hpp"
#include "Utilities.hpp"
#include "Vektor.hpp"

#include <SDL2/SDL.h>
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
    is_chased = false;
}

Whaler::~Whaler() {
    Logger::Status("Destroying Whaler");
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Whaler::setLevel(int lvl) {
    this->lvl = lvl;
}

void Whaler::Initialize() {
    LoadWhaler(texture, lvl);
    if(this->texture == nullptr) {
        Logger::Warning("Failed to load whaler texture");
    }
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
    if(is_chased) {
        // top priority
        update_movement(hitbox, dest_x, dest_y, WHALER_SPEED);
        is_stopped = false;
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
		update_movement(hitbox, dest_x, dest_y, WHALER_SPEED);
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
/*     SDL_SetRenderDrawColor(Window::renderer, 0xFF, 0x00, 0x00, 0xFF); // red
    SDL_RenderDrawRect(Window::renderer, &hitbox);
    SDL_SetRenderDrawColor(Window::renderer, 0xFF, 0xFF, 0xFF, 0xFF); */
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

void Whaler::CheckPlayerDistance(SDL_Rect player) {
    if(std::hypot(this->hitbox.x - player.x, this->hitbox.y - player.y) < 200.0) {
        // player is close -> RUN
        is_chased = true;

        // destination is opposite of player
        dest_x = 2 * hitbox.x - player.x;
        dest_y = 2 * hitbox.y - player.y;

        // make sure they dont get stuck in the borders
        if(dest_x < 0) {
            dest_x = 0;
        }
        if(dest_x + hitbox.w > Window::Width()) {
            dest_x = Window::Width() - hitbox.w;
        }
        if(dest_y < 0) {
            dest_y = 0;
        }
        if(dest_y + hitbox.h > Window::Height()) {
            dest_y = Window::Height() - hitbox.h;
        }
    }
    else {
        // move normally
        is_chased = false;
    }
}

bool Whaler::operator==(const SDL_Rect& rect) {
    return SDL_HasIntersection(&hitbox, &rect);
}

void Whaler::avoidEntity(const SDL_Rect& rect) {
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

struct ReplayObject Whaler::dumpObject() {
    struct ReplayObject obj;
    obj.type = TYPE_WHALER;
    obj.level = this->lvl;
    obj.container = this->container;

    return obj;
}