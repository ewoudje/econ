//
// Created by ewoudje on 21/11/20.
//

#ifndef EPICF_GAME_H
#define EPICF_GAME_H

#include "default.h"

struct GameDescription {
    char* name;
    int gameCSize;
    uint16_t (*start)();
    uint16_t (*resume)();
};

void loadGame(struct GameDescription* description);

void unloadGame();

#endif //EPICF_GAME_H
