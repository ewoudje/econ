//
// Created by ewoudje on 21/11/20.
//

#include "EPICF/game.h"
#include "EPICF/system.h"
#include "platform/display.h"


struct {
    uint16_t posX, posY;
    uint16_t counterX, counterY;
}* gameState;

uint16_t resume() {
    GAME_LOOP_START
        GAME_INPUT(UP)
        if (GAME_INPUT_PRESSED) {
            gameState->counterY += delta;
        }

        GAME_INPUT(DOWN)
        if (GAME_INPUT_PRESSED) {
            gameState->counterY -= delta;
        }

        GAME_INPUT(RIGHT)
        if (GAME_INPUT_PRESSED) {
            gameState->counterX += delta;
        }

        if (gameState->counterX > 100) {
            gameState->posX++;
        }

        if (gameState->counterY > 100) {
            gameState->posY++;
        }
    GAME_LOOP_END
}

uint16_t start() {
    gameState = SYSTEM->currentGame;

    //INIT
    gameState->posX = DISPLAY_WIDTH / 2;
    gameState->posY = DISPLAY_HEIGHT / 2;
    gameState->counterX = 0;
    gameState->counterY = 0;

    resume();
}

struct GameDescription TestGame = {
        .name = "Test Game",
        .gameCSize = sizeof(*gameState),
        .start = start,
        .resume = resume
};