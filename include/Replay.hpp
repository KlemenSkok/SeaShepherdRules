
// Replay.hpp

#pragma once

#include "Vektor.hpp"
#include "Utilities.hpp"
#include "Constants.hpp"

#include <SDL2/SDL_ttf.h>

using namespace Window;


/*
About:
    - replay system za igrco
    - shrani polozaje igralca in ostalih objektov
    - zapisuje v binarno datoteko
    - replay lahko tudi predvaja
*/

class Replay {


public:

    Replay() = default;
    ~Replay() = default;

    static void StartRecording();
    static void StopRecording();
    static void AppendRecord(ReplayObject *record);
    static void AppendFrame(Vektor<struct ReplayObject>*);

    static void StartPlayback();

};