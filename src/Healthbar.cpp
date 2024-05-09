
// Healthbar.cpp

#include "Healthbar.hpp"
#include "Utilities.hpp"
#include "Constants.hpp"

using namespace Window;


Healthbar::Healthbar() {
    outer = {0,0,HEALTHBAR_WIDTH,HEALTHBAR_HEIGHT};
    inner = {0,0,0,0};

    color = {0, 255, 0, 255};
}

void Healthbar::Update(Uint8 health) {
    outer.x = Window::Width() / 2 - outer.w / 2;
    outer.y = Window::Height() - outer.h - 30;

    inner.x = outer.x + HBAR_INNER_OFFSET;
    inner.y = outer.y + HBAR_INNER_OFFSET;
    inner.w = (outer.w - HBAR_INNER_OFFSET*2) * health / 100;
    inner.h = outer.h - HBAR_INNER_OFFSET*2;

    if(health >= 66) {
        color = {0, 255, 0, 255};
    }
    else if(health >= 33)  {
        color = {255, 255, 0, 255};
    }
    else {
        color = {255, 0, 0, 255};
    }
}

void  Healthbar::Render() {
    SDL_SetRenderDrawColor(Window::renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(Window::renderer, &outer);

    SDL_SetRenderDrawColor(Window::renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(Window::renderer, &inner);

    SDL_Rect rect = {inner.x + inner.w, inner.y, outer.w - inner.w - HBAR_INNER_OFFSET*2, inner.h};
    SDL_SetRenderDrawColor(Window::renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(Window::renderer, &rect);

}