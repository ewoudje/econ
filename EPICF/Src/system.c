//
// Created by ewoudje on 18/11/20.
//

#include "system.h"
#include "platform/system.h"
#include "platform/input.h"
#include "platform/display.h"

#define LOOPFLAG_RMENU 0x01

struct SystemContext* currentSystem;

EPICF_INPUT_VAR(prev_buttons)

int EPICF_initSystem() {
    SYSTEM = malloc(sizeof(*SYSTEM));
    SYSTEM->systemFlags = SYSFLAG_ENABLED;
    SYSTEM->menuFlags = MENUFLAG_SHOW | 6;
    SYSTEM->selectedMenuItem = &SYSTEM->currentMenuItems[3];

    testCall();

    display_init();

    return 0;
}

int EPICF_startLoop() {

    renderMenu();

    uint8_t loopFlags;

    prev_buttons = EPICF_buttons;

    while(SYSTEM->systemFlags & SYSFLAG_ENABLED) {
        EPICF_LOOP_CALLBACK

        EPICF_UPDATE_INPUT

        loopFlags = 0;

        if (EPICF_INPUT_BUTTON_DOWN(EPICF_buttons) != EPICF_INPUT_BUTTON_DOWN(prev_buttons)) {
            if (EPICF_INPUT_BUTTON_DOWN(EPICF_buttons)) {
                //ON RELEASE
                loopFlags |= incMenuSelect() ? LOOPFLAG_RMENU : 0;
            } else {
                //ON PRESS
            }
        }

        if (EPICF_INPUT_BUTTON_UP(EPICF_buttons) != EPICF_INPUT_BUTTON_UP(prev_buttons)) {
            if (EPICF_INPUT_BUTTON_UP(EPICF_buttons)) {
                //ON RELEASE
                loopFlags |= decMenuSelect() ? LOOPFLAG_RMENU : 0;
            } else {
                //ON PRESS
            }
        }

        if (EPICF_INPUT_BUTTON_RIGHT(EPICF_buttons) != EPICF_INPUT_BUTTON_RIGHT(prev_buttons)) {
            if (EPICF_INPUT_BUTTON_RIGHT(EPICF_buttons)) {
                //ON RELEASE
                loopFlags |= SYSTEM->selectedMenuItem->callback() & 0x0F;
            } else {
                //ON PRESS
            }
        }

        if (loopFlags & LOOPFLAG_RMENU) {
            renderMenu();
        }

        prev_buttons = EPICF_buttons;
    }

    return -1;
}

uint8_t toggle = 1;

uint16_t testCall() {

    if (toggle) {
        SYSTEM->currentMenuItems[0].text = "Hello";
        SYSTEM->currentMenuItems[0].callback = renderMenu;
        SYSTEM->currentMenuItems[1].text = "World";
        SYSTEM->currentMenuItems[1].callback = renderMenu;
        SYSTEM->currentMenuItems[2].text = "!";
        SYSTEM->currentMenuItems[2].callback = renderMenu;
        SYSTEM->currentMenuItems[3].text = "By Ewoud";
        SYSTEM->currentMenuItems[3].callback = testCall;
        SYSTEM->currentMenuItems[4].text = "Test4";
        SYSTEM->currentMenuItems[5].text = "Test5";
        toggle = 0;
    } else {
        SYSTEM->currentMenuItems[0].text = "Ewoud";
        SYSTEM->currentMenuItems[1].text = "Is";
        SYSTEM->currentMenuItems[2].text = "GOD";
        toggle = 1;
    }

    return LOOPFLAG_RMENU;
}

