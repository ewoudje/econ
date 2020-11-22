//
// Created by ewoudje on 18/11/20.
//

#include "system.h"
#include "platform/input.h"
#include "platform/display.h"
#include "error.h"

#define LOOPFLAG_RMENU 0x01

uint16_t testCall();

struct SystemContext* currentSystem;

/**
 * @brief Allocates and initializes the SystemContext, should be called at the start of our platform
 * @return an possible error code 0 if none
 */
ERROR_CODE EPICF_initSystem() {
    SYSTEM = malloc(sizeof(*SYSTEM));
    SYSTEM->systemFlags = SYSFLAG_ENABLED;
    SYSTEM->menuFlags = MENUFLAG_SHOW | 6;
    SYSTEM->selectedMenuItem = &SYSTEM->currentMenuItems[3];
    SYSTEM->totalGames = 0;
    SYSTEM->totalGamesCount = 0;

    testCall();

    display_init();

    return 0;
}

/**
 * @brief Sets the possible games, this should be called before startLoop but after initSystem
 * @param length of the games
 * @param games pointer to an array of GameDescriptions
 */
void EPICF_initGames(uint8_t length, void** games) {
    SYSTEM->totalGames = (struct GameDescription**)games;
    SYSTEM->totalGamesCount = length;
}

/**
 * Call as the last function in your platform code, this start the *normally* infinite loop
 * @return An possible error code, this should never return 0
 */
ERROR_CODE EPICF_startLoop() {

    if (!SYSTEM->totalGamesCount)
        return EPICF_ERROR_NO_GAMES;

    renderMenu();

    uint8_t loopFlags;
    uint16_t inputChange;
    EPICF_INPUT_VAR(prevInput);

    prevInput = EPICF_buttons;

    while(SYSTEM->systemFlags & SYSFLAG_ENABLED) {
        EPICF_LOOP_CALLBACK

        EPICF_UPDATE_INPUT

        loopFlags = 0;

        GAME_INPUT(DOWN)
        if (GAME_INPUT_ON_RELEASE) {
            loopFlags |= incMenuSelect() ? LOOPFLAG_RMENU : 0;
        }

        GAME_INPUT(UP)
        if (GAME_INPUT_ON_RELEASE) {
            //ON RELEASE
            loopFlags |= decMenuSelect() ? LOOPFLAG_RMENU : 0;
        }

        GAME_INPUT(RIGHT)
        if (GAME_INPUT_ON_RELEASE) {
            //ON RELEASE
            loopFlags |= SYSTEM->selectedMenuItem->callback() & 0x0F;
        }

        if (loopFlags & LOOPFLAG_RMENU) {
            renderMenu();
        }

        prevInput = EPICF_buttons;
    }

    return EPICF_ERROR_SYS_DISABLED;
}

uint8_t toggle = 1;

uint16_t testCall() {

    if (toggle) {
        SYSTEM->currentMenuItems[0].text = "Hello";
        SYSTEM->currentMenuItems[0].callback = renderMenu;
        SYSTEM->currentMenuItems[0].textColor = WHITE;
        SYSTEM->currentMenuItems[1].text = "World";
        SYSTEM->currentMenuItems[1].callback = renderMenu;
        SYSTEM->currentMenuItems[1].textColor = WHITE;
        SYSTEM->currentMenuItems[2].text = "!";
        SYSTEM->currentMenuItems[2].callback = renderMenu;
        SYSTEM->currentMenuItems[2].textColor = WHITE;
        SYSTEM->currentMenuItems[3].text = "By Ewoud";
        SYSTEM->currentMenuItems[3].callback = testCall;
        SYSTEM->currentMenuItems[3].textColor = WHITE;
        SYSTEM->currentMenuItems[4].text = "Test4";
        SYSTEM->currentMenuItems[4].textColor = WHITE;
        SYSTEM->currentMenuItems[5].text = "Test5";
        SYSTEM->currentMenuItems[5].textColor = WHITE;
        toggle = 0;
    } else {
        SYSTEM->currentMenuItems[0].text = "Ewoud";
        SYSTEM->currentMenuItems[0].textColor = RED;
        SYSTEM->currentMenuItems[1].text = "Is";
        SYSTEM->currentMenuItems[2].text = "GOD";
        toggle = 1;
    }

    return LOOPFLAG_RMENU;
}

/**
 * @brief gets called by the game to give the system some cpu time and response
 * @return If it is 0 the game should stop executing and give cpu to system otherwise it can contain flags
 */
uint8_t gameLoopCall() {
    return !EPICF_INPUT_BUTTON_F1(EPICF_buttons);
}

