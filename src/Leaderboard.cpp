
// PlayerInfo.cpp

#include "Leaderboard.hpp"

#include <cstdint>
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>

// !!!!!!!!!!!!!! static variabli morjo bit definirani tud v cpp fajlu
LeaderboardEntry* PlayerInfo::player = new LeaderboardEntry() ;

void PlayerInfo::Initialize() {
    player = new LeaderboardEntry();

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

    player->name[0] = '\0';
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
                strcpy(player->name + cursor_pos, e.text.text);
                cursor_pos += strlen(e.text.text);
                if(cursor_pos > max_username_length) {
                    cursor_pos = max_username_length;
                    *(player->name + max_username_length) = '\0';
                }
            }
            else if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_BACKSPACE && strlen(player->name) > 0) {
                    cursor_pos--;
                    *(player->name + cursor_pos) = '\0';
                }
                else if(e.key.keysym.sym == SDLK_RETURN && strlen(player->name) > 0) { // confirm username (ne sme bit prazen)
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
            SDL_Surface *s = TTF_RenderText_Solid(_font, player->name, InputColor);
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

    std::cout << "collected username: " << player->name << std::endl;

}

void PlayerInfo::Clean() {
    delete player;
    Logger::Success("PlayerInfo cleaned");
}

void PlayerInfo::SetLevelScore(uint8_t levelNum, double time) {
    levelNum--;
    if(levelNum < 3) {
        player->score[levelNum] = time;
    }
    else {
        Logger::Error("Invalid level number");
        std::cout << "-> level: " << levelNum << std::endl;
    }
}

LeaderboardEntry* PlayerInfo::dump() {
    return player;
}


// ------------------------------------- //
// ------- LEADERBOARD FUNCTIONS ------- //
// ------------------------------------- //


void Leaderboard::AddEntry(LeaderboardEntry *entry) {
    
    std::ifstream in("Leaderboard.bin", std::ios::binary);

    if(!in.is_open()) { // datoteka se ne obstaja
        std::ofstream out("Leaderboard.bin", std::ios::binary);
        out.write((char*) entry, sizeof(*entry));
        out.close();
    }
    else {
        std::ofstream out("tmpout.bin", std::ios::binary);
        LeaderboardEntry tmp;
        bool is_written = false;

        while(in.read((char*)&tmp, sizeof(tmp))) {
            if(!is_written && entry->totalScore() < tmp.totalScore()) {
                out.write((char*) entry, sizeof(*entry));
                is_written = true;
            }
            out.write((char*) &tmp, sizeof(tmp));
        }
        if(!is_written) {
            out.write((char*) entry, sizeof(*entry));
        }
        out.close();
        in.close();

        remove("Leaderboard.bin");
        rename("tmpout.bin", "Leaderboard.bin");
    }

    Logger::Success("Leaderboard entry added");

}

void Leaderboard::Display() {
    std::vector<LeaderboardEntry> entries;
    int counter = 0;
    std::ifstream in("Leaderboard.bin", std::ios::binary);

    if(in.is_open()) {
        LeaderboardEntry tmp;
        while(in.read((char*)&tmp, sizeof(tmp)) && counter < 10) { // read top 10 entries
            entries.push_back(tmp);
            counter++;
        }
        in.close();
    }
    else {
        Logger::Warning("Leaderboard is empty");
    }



    // display everything
    TTF_Font *_font = TTF_OpenFont("../../assets/fonts/LilitaOne-Regular.ttf", 25);
    if (!_font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }
    SDL_Texture *background = LoadTexture("../../assets/images/menus/leaderboard_screen.png");
    if(!background) {
        Logger::Error("Failed to load leaderboard background");
        return;
    }
    
    auto onWindowResize = [&]() { // redraw everything
        
        SDL_RenderClear(Window::renderer);
        
        SDL_Rect backgroundRect = {0, 0, Window::Width(), Window::Height()};
        SDL_RenderCopy(Window::renderer, background, NULL, &backgroundRect);
        
        SDL_Texture *tileTexture = LoadTexture("../../assets/images/random/leaderboard_tile.png");
        if(!tileTexture) {
            Logger::Error("Failed to load leaderboard tile");
            //return;
        }
        TTF_CloseFont(_font);

        int fontSize = 0.0434 * Window::Height();
        int tileWidth = 0.4882 * Window::Width();
        int tileHeight = 0.0625 * Window::Height();
        int tileXOffset = 0.1736 * Window::Height();

        std::cout << "New font size: " << fontSize << std::endl;

        _font = TTF_OpenFont("../../assets/fonts/LilitaOne-Regular.ttf", fontSize);

        // TODO: render tiles
        for(int i = 0; i < entries.size(); ++i) {
            SDL_Rect tileRect = {Window::Width() / 2 - (tileWidth/2), tileXOffset + i * (tileHeight + 2), tileWidth, tileHeight};
            SDL_RenderCopy(Window::renderer, tileTexture, NULL, &tileRect);
            
            // username
            SDL_Texture *nameTexture = RenderText(entries[i].name, _font, {0, 0, 0, 255});
            SDL_Rect nameRect = {tileRect.x + int(tileWidth * 0.05f), tileRect.y + int(tileHeight * 0.08f), 1, 1};
            SDL_QueryTexture(nameTexture, NULL, NULL, &nameRect.w, &nameRect.h);
            SDL_RenderCopy(Window::renderer, nameTexture, NULL, &nameRect);

            //! score -> round on two decimals
            std::ostringstream stream;
            stream << std::fixed << std::setprecision(2) << entries[i].totalScore();
            std::string score_str = stream.str();
            score_str += 's';
            
            SDL_Texture *scoreTexture = RenderText(score_str.c_str(), _font, {0, 0, 0, 255});
            SDL_Rect scoreRect;
            SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreRect.w, &scoreRect.h);
            scoreRect.x = tileRect.x + tileRect.w - scoreRect.w - int(tileWidth * 0.05f);
            scoreRect.y = tileRect.y + int(tileHeight * 0.08f);
            SDL_RenderCopy(Window::renderer, scoreTexture, NULL, &scoreRect);

            SDL_DestroyTexture(nameTexture);
            SDL_DestroyTexture(scoreTexture);   

        }
        SDL_RenderPresent(Window::renderer);

    };

    onWindowResize();


    bool exit = false;
    while(!exit) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                SDL_PushEvent(&e);
                exit = true;
                break;
            }
            else if(e.type == SDL_WINDOWEVENT) {
                if(e.window.event == SDL_WINDOWEVENT_RESIZED) {
                    onWindowResize();
                }
            }
            else if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_1) {
                    exit = true;
                }
            }
        }

        SDL_Delay(FRAME_TARGET_TIME);
    }

}