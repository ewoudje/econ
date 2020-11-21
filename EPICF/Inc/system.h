//
// Created by ewoudje on 18/11/20.
//

#ifndef EPICF_SYSTEM_H
#define EPICF_SYSTEM_H

#include "default.h"
#include "platform.h"
#include "menu.h"

uint16_t testCall();

struct SystemContext {
    struct MenuItem currentMenuItems[6]; //This shouldn't be hard defined in the EPICF code but the max amount of menu entries on this display is 6
    uint8_t menuFlags;
    uint8_t systemFlags;
    struct MenuItem *selectedMenuItem;
};

extern struct SystemContext* currentSystem;

#define SYSTEM currentSystem
#define SYSFLAG_ENABLED 0x80

#endif //ECON_DEV_SYSTEM_H
