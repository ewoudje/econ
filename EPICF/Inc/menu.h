//
// Created by ewoudje on 19/11/20.
//

#ifndef EPICF_MENU_H
#define EPICF_MENU_H

#include "default.h"

struct MenuItem {
    char* text;
    uint16_t textColor;
    uint16_t (*callback)();
};

void renderMenu();

uint8_t incMenuSelect();

uint8_t decMenuSelect();

#define MENUFLAG_SHOW 0x80

#endif //EPICF_MENU_H
