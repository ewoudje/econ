//
// Created by ewoudje on 19/11/20.
//

#include "system.h"
#include "gfx.h"
#include "font.h"
#include <string.h>

#define ENTRY_HEIGHT 40
#define MENU_TEXT_SIZE 4
#define MARGIN_SIZE 10
#define BORDER_SIZE 8
#define MENU_OFFSET (MARGIN_SIZE + BORDER_SIZE)
#define MENU_HEIGHT (DISPLAY_HEIGHT - (MENU_OFFSET * 2))
#define MENU_WIDTH  (DISPLAY_WIDTH - (MENU_OFFSET * 2))

#define MARGIN_COLOR GREEN
#define BORDER_COLOR BLACK
#define ENTRY_COLOR GREEN
#define SELECTED_COLOR WHITE
#define INSIDE_COLOR GREEN

//Not allot needed to explain here, this is just an internal function for renderMenu
void renderMenuEntry(int16_t y, struct MenuItem* item) {
    uint16_t off = (ENTRY_HEIGHT - (MENU_TEXT_SIZE * CHAR_HEIGHT)) / 2;
    uint16_t size = MENU_TEXT_SIZE * CHAR_WIDTH * strlen(item->text);
    uint16_t x = (MENU_WIDTH - size) / 2;
    display_setRect(MENU_OFFSET, y, MENU_WIDTH, ENTRY_HEIGHT, SYSTEM->selectedMenuItem == item ? SELECTED_COLOR : ENTRY_COLOR);
    gfx_drawText(x, y + off, item->text, MENU_TEXT_SIZE, item->textColor);
}

/**
 * @brief renders menu to screen based of the global SystemContext
 */
void renderMenu() {
    if (SYSTEM->menuFlags & MENUFLAG_SHOW) {
        uint8_t size = SYSTEM->menuFlags & 0x0F;
        uint16_t yy = ((MENU_HEIGHT - (ENTRY_HEIGHT * size)) / 2); // OFFSET OF TOP AND BOTTOM PART TO CENTER MENU's

        if (size < 6) { //If we want to display 6 entries on this small display we need to remove bottom and top margins
            //TOP MENU SIDE
            display_setRect(0, 0, DISPLAY_WIDTH, MARGIN_SIZE, MARGIN_COLOR);
            display_setRect(MARGIN_SIZE, MARGIN_SIZE, DISPLAY_WIDTH - (MARGIN_SIZE * 2), BORDER_SIZE, BORDER_COLOR);
            //BOTTOM MENU SIDE
            display_setRect(0, DISPLAY_HEIGHT - MARGIN_SIZE, DISPLAY_WIDTH, MARGIN_SIZE, MARGIN_COLOR);
            display_setRect(MARGIN_SIZE, DISPLAY_HEIGHT - MENU_OFFSET, DISPLAY_WIDTH - (MARGIN_SIZE * 2), BORDER_SIZE, BORDER_COLOR);
            //LEFT MENU SIDE
            display_setRect(0, 0, MARGIN_SIZE, DISPLAY_HEIGHT, MARGIN_COLOR);
            display_setRect(MARGIN_SIZE, MARGIN_SIZE, BORDER_SIZE, DISPLAY_HEIGHT - (MARGIN_SIZE * 2), BORDER_COLOR);
            //RIGHT MENU SIDE
            display_setRect(DISPLAY_WIDTH - MARGIN_SIZE, 0, MARGIN_SIZE, DISPLAY_HEIGHT, MARGIN_COLOR);
            display_setRect(DISPLAY_WIDTH - MENU_OFFSET, MARGIN_SIZE, BORDER_SIZE, DISPLAY_HEIGHT - (MARGIN_SIZE * 2), BORDER_COLOR);

            //INSIDE MENU
            display_setRect(MENU_OFFSET, MENU_OFFSET, MENU_WIDTH, yy, INSIDE_COLOR);
            display_setRect(MENU_OFFSET, DISPLAY_HEIGHT - MENU_OFFSET - yy, MENU_WIDTH, yy, INSIDE_COLOR);
        } else {
            //LEFT MENU SIDE
            display_setRect(0, 0, MARGIN_SIZE, DISPLAY_HEIGHT, MARGIN_COLOR);
            display_setRect(MARGIN_SIZE, 0, BORDER_SIZE, DISPLAY_HEIGHT, BORDER_COLOR);
            //RIGHT MENU SIDE
            display_setRect(DISPLAY_WIDTH - MARGIN_SIZE, 0, MARGIN_SIZE, DISPLAY_HEIGHT, MARGIN_COLOR);
            display_setRect(DISPLAY_WIDTH - MENU_OFFSET, 0, BORDER_SIZE, DISPLAY_HEIGHT, BORDER_COLOR);
        }

        uint16_t y = yy + MENU_OFFSET; //Y where entries will be added

        for (int i = 0; i < size; i++) {
            renderMenuEntry(y, &SYSTEM->currentMenuItems[i]);

            y += ENTRY_HEIGHT;
        }
    }
}

/**
 * @brief Increments the selected entry to the next menu entry
 * @return It returns 0 if it didn't change anything, this can happen when we are at the bottom of the menu
 */
uint8_t incMenuSelect() {
    uint8_t size = SYSTEM->menuFlags & 0x0F;
    for (int i = 0; i < size - 1; i++) {
        if (&SYSTEM->currentMenuItems[i] == SYSTEM->selectedMenuItem) {
            SYSTEM->selectedMenuItem = &SYSTEM->currentMenuItems[i + 1];

            return 1;
        }
    }

    return 0;
}

/**
 * @brief Decrements the selected entry to the prev menu entry
 * @return It returns 0 if it didn't change anything, this can happen when we are at the top of the menu
 */
uint8_t decMenuSelect() {
    uint8_t size = SYSTEM->menuFlags & 0x0F;
    for (int i = 1; i < size; i++) {
        if (&SYSTEM->currentMenuItems[i] == SYSTEM->selectedMenuItem) {
            SYSTEM->selectedMenuItem = &SYSTEM->currentMenuItems[i - 1];
            return 1;
        }
    }

    return 0;
}