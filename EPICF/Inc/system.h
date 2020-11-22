//
// Created by ewoudje on 18/11/20.
//

#ifndef EPICF_SYSTEM_H
#define EPICF_SYSTEM_H

#include "default.h"
#include "platform.h"
#include "platform/system.h"
#include "platform/input.h"
#include "game.h"
#include "menu.h"

uint8_t gameLoopCall();

struct SystemContext {
    struct MenuItem currentMenuItems[6]; //This shouldn't be hard defined in the EPICF code but the max amount of menu entries on this display is 6
    uint8_t menuFlags;
    uint8_t systemFlags;
    struct MenuItem *selectedMenuItem;
    void* currentGame;
    struct GameDescription* gameDesc;
    struct GameDescription** totalGames;
    uint8_t totalGamesCount;
};

extern struct SystemContext* currentSystem;

#define SYSTEM currentSystem
#define SYSFLAG_ENABLED 0x80
#define GAME_LOOP_START \
    uint8_t loopCode;   \
    uint16_t inputChange;\
    EPICF_INPUT_VAR(prevInput) \
    while((loopCode = gameLoopCall())) {

#define GAME_LOOP_END \
    prevInput = EPICF_buttons; \
    EPICF_LOOP_CALLBACK \
    EPICF_UPDATE_INPUT \
    }

#define GAME_INPUT(w) \
    inputChange = (EPICF_INPUT_BUTTON_ ## w (EPICF_buttons) != EPICF_INPUT_BUTTON_ ## w (EPICF_buttons)) | (EPICF_INPUT_BUTTON_ ## w (EPICF_buttons) << 8);

#define GAME_INPUT_RELEASE (inputChange & 0xFF00) && (inputChange & 0x00FF)
#define GAME_INPUT_PRESS (inputChange & 0xFF00) && (inputChange & 0x00FF)

#endif //ECON_DEV_SYSTEM_H
