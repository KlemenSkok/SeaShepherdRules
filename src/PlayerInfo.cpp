
// PlayerInfo.cpp

#include "PlayerInfo.hpp"



void PlayerInfo::Initialize() {
    
    for(int i = 0; i < 3; i++) {
        score[i] = 0.0f;
    }

    Logger::Success("PlayerInfo initialized");

}


void PlayerInfo::Get() {
    TTF_Font *_font = TTF_OpenFont("../../assets/fonts/LilitaOne-Regular.ttf", 24);
    if (!_font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }

    SDL_Window* _window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 120, SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
    if (!_window) {
        SDL_Log("Failed to create popup window: %s", SDL_GetError());
        TTF_CloseFont(_font);
        return;
    }

    SDL_Renderer* _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        SDL_Log("Failed to create popup renderer: %s", SDL_GetError());
        SDL_DestroyWindow(_window);
        TTF_CloseFont(_font);
        return;
    }

    SDL_Color color = {0, 0, 0, 255};
    SDL_Surface* s_tmp = TTF_RenderText_Solid(_font, "Enter your username:", color);
    SDL_Texture* introTexture = SDL_CreateTextureFromSurface(_renderer, s_tmp);

    SDL_Rect introTextureRect;
    introTextureRect.x = 20;
    introTextureRect.y = 10;
    introTextureRect.w = s_tmp->w;
    introTextureRect.h = s_tmp->h;

    SDL_Color InputColor = {105, 105, 105, 255};

    username[0] = '\0';
    short cursor_pos = 0;

    SDL_FreeSurface(s_tmp);


    // --- vnos besedila --- //

    SDL_Rect InputBox = {20, 45, 260, 40};

    SDL_SetTextInputRect(&InputBox);


    SDL_Event e;
    bool running = true;
    //std::string name = "";
    SDL_StartTextInput();

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            else if(e.type == SDL_WINDOWEVENT) {
                if(e.window.event == SDL_WINDOWEVENT_CLOSE) {
                    if(e.window.windowID == SDL_GetWindowID(_window)) {
                        // no escape :)
                        //running = false;
                    }
                }
            }
            else if(e.type == SDL_TEXTINPUT) {
                //name += e.text.text;
                strcpy(username + cursor_pos, e.text.text);
                cursor_pos += strlen(e.text.text);
                if(cursor_pos > max_username_length) {
                    cursor_pos = max_username_length;
                    *(username + max_username_length) = '\0';
                }
            }
            else if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_BACKSPACE && strlen(username) > 0) {
                    cursor_pos--;
                    *(username + cursor_pos) = '\0';
                }
                else if(e.key.keysym.sym == SDLK_RETURN && strlen(username) > 0) { // confirm username (ne sme bit prazen)
                    running = false;
                }
            }
        }

        if(SDL_GetTicks() % FRAME_TARGET_TIME == 0) {

            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
            SDL_RenderClear(_renderer);

            SDL_RenderCopy(_renderer, introTexture, NULL, &introTextureRect); // "enter your username:"
            
            SDL_SetRenderDrawColor(_renderer, InputColor.r, InputColor.g, InputColor.b, InputColor.a);
            SDL_RenderDrawRect(_renderer, &InputBox); // narisi input box

            // render read username
            SDL_Surface *s = TTF_RenderText_Solid(_font, username, InputColor);
            SDL_Texture *InputText = SDL_CreateTextureFromSurface(_renderer, s);
            SDL_Rect InputTextRect = {InputBox.x + 5, InputBox.y + 5, 1, 1};
            SDL_QueryTexture(InputText, NULL, NULL, &InputTextRect.w, &InputTextRect.h);
            SDL_RenderCopy(_renderer, InputText, NULL, &InputTextRect);

            SDL_FreeSurface(s);
            SDL_DestroyTexture(InputText);

            SDL_RenderPresent(_renderer);
            
        }

    }

    SDL_StopTextInput();

    SDL_DestroyTexture(introTexture);
    SDL_DestroyRenderer(_renderer);
    TTF_CloseFont(_font);
    SDL_DestroyWindow(_window);

    std::cout << "collected username: " << username << std::endl;

}

void PlayerInfo::Clean() {

}

void PlayerInfo::SetLevelScore(uint8_t levelNum, double time) {
    if(levelNum < 3) {
        score[levelNum] = time;
    }
    else {
        Logger::Error("Invalid level number");
    }
}