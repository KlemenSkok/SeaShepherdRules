
// Replay.cpp

#include "Replay.hpp"

#include <fstream>



void Replay::StartRecording() {
    std::ifstream in("replay.bin", std::ios::binary);
    if(in.is_open()) {
        in.close();
        std::remove("replay.bin");
    }
}

void Replay::StopRecording() {
    // TODO
}

void Replay::AppendRecord(ReplayObject *obj) {
    std::ofstream out("replay.bin", std::ios::binary | std::ios::app);
    out.write((char*) &obj, sizeof(struct ReplayObject));
    out.close();
}

void Replay::AppendFrame(Vektor<struct ReplayObject> *frame) {
    std::ofstream out("replay.bin", std::ios::binary | std::ios::app);

    struct ReplayObject ctrl_frame;
    ctrl_frame.container = {0, 0, 0, 0};
    // oznaci zacetek frejma
    //ctrl_frame.type = START_FRAME;
    //out.write((char*) &ctrl_frame, sizeof(struct ReplayObject));

    while(!frame->empty()) {
        ReplayObject obj = frame->front();
        out.write((char*) &obj, sizeof(struct ReplayObject));
        frame->pop_front();
    }

    // oznaci konec frejma
    ctrl_frame.type = END_FRAME;
    out.write((char*) &ctrl_frame, sizeof(struct ReplayObject));


    out.close();

    delete frame;
}


void Replay::StartPlayback() {

    std::ifstream in("replay.bin", std::ios::binary);

    if(!in.is_open()) {
        Logger::Error("Replay file not found!");
        return;
    }

    bool exit = false;
    uint8_t currLvl = 1;

    SDL_Texture *player_texture = LoadTexture("../../assets/images/player.png"),
                *whaler_texture = LoadTexture("../../assets/images/Level_1/whaler1.png"),
                *iceberg_texture = LoadTexture("../../assets/images/Level_1/iceberg.png"),
                *atol_texture = LoadTexture("../../assets/images/Level_2/atol.png"),
                *pirate_texture = LoadTexture("../../assets/images/Level_3/pirate.png"),
                *exit_text = RenderText("Press 'E' to exit replay", TTF_OpenFont("../../assets/fonts/LilitaOne-Regular.ttf", 24), {0, 0, 0, 255});

    SDL_Rect exit_rect = {10, 10, 0, 0};
    SDL_QueryTexture(exit_text, NULL, NULL, &exit_rect.w, &exit_rect.h);

    if(exit_text == nullptr) {
        Logger::Error("Failed to render text!");
    }

    Uint32 lastUpdate, currentTime;
    lastUpdate = currentTime = SDL_GetTicks();

    while(!exit) {
        currentTime = SDL_GetTicks();
        if(currentTime - lastUpdate >= FRAME_TARGET_TIME) {
            lastUpdate = currentTime;

            SDL_RenderClear(Window::renderer); // clear screen

            // read new
            bool reading = true;
            struct ReplayObject obj;
            while(reading) {
                if(!in.read((char*) &obj, sizeof(struct ReplayObject))) {
                    exit = true;
                    break;
                }

                switch(obj.type) {
                    case END_FRAME: // end frame
                        reading = false;
                        break;
                    case TYPE_PLAYER: // player
                        SDL_RenderCopy(Window::renderer, player_texture, NULL, &obj.container);
                        break;
                    case TYPE_PIRATE: // pirate
                        SDL_RenderCopy(Window::renderer, pirate_texture, NULL, &obj.container);
                        break;
                    case TYPE_ICEBERG: // iceberg
                        SDL_RenderCopy(Window::renderer, iceberg_texture, NULL, &obj.container);
                        break;
                    case TYPE_ATOL: // atol
                        SDL_RenderCopy(Window::renderer, atol_texture, NULL, &obj.container);
                        break;
                    case TYPE_WHALER:
                        if(obj.level == currLvl) {
                            SDL_RenderCopy(Window::renderer, whaler_texture, NULL, &obj.container);
                        }
                        else {
                            currLvl = obj.level;
                            LoadWhaler(whaler_texture, currLvl);
                            SDL_RenderCopy(Window::renderer, whaler_texture, NULL, &obj.container);
                        }
                        break;

                    default:
                        Logger::Error("Invalid object type in replay!");
                }

            }
            SDL_RenderCopy(Window::renderer, exit_text, NULL, &exit_rect);
            SDL_RenderPresent(Window::renderer); // refresh screen

        }

        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) { // exit game, close window
                exit = true;
                SDL_PushEvent(&e);
            }
            else if(e.type == SDL_KEYDOWN) { // exit replay
                if(e.key.keysym.sym == SDLK_e) {
                    exit = true;
                }
            }
        }

    }
}

