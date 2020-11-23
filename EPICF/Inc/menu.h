//
// Created by ewoudje on 19/11/20.
//

#ifndef EPICF_MENU_H
#define EPICF_MENU_H

#include "default.h"

struct MenuEntry {
    char* text;
    uint16_t textColor;
    uint16_t (*callback)(void* xtra);
    void* xtra;
};

struct Menu {
    uint32_t size;
    struct MenuEntry* array;
};

void renderMenu();

uint8_t incMenuSelect();

uint8_t decMenuSelect();

struct MenuEntry newMenuEntry(uint16_t (*callback)(), char* text);

struct MenuEntry newMenuEntryX(uint16_t (*callback)(void*), char* text, void* xtra);

struct Menu* newMenu(uint32_t amount);

void useMenu(struct Menu* menu);

void freeMenu(struct Menu* menu);

#define MENUFLAG_SHOW 0x80
#define MENUFLAG_SCROLLABLE 0x20

//This shouldn't be hard defined in the EPICF code but the max amount of menu entries on this display is 6
#define MAX_MENU_ENTRIES 6

#endif //EPICF_MENU_H
