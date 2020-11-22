//
// Created by ewoudje on 21/11/20.
//

#include "EPICF/game.h"
#include "EPICF/system.h"


uint16_t resume() {
    GAME_LOOP_START

    GAME_LOOP_END
}

uint16_t start() {
    resume();
}

struct GameDescription TestGame = {
        .name = "Test Game",
        .gameCSize = sizeof(void),
        .start = start,
        .resume = resume
};