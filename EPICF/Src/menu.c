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
void renderMenuEntry(int16_t y, struct MenuEntry* entry) {
    uint16_t off = (ENTRY_HEIGHT - (MENU_TEXT_SIZE * CHAR_HEIGHT)) / 2;
    uint16_t size = MENU_TEXT_SIZE * CHAR_WIDTH * strlen(entry->text);
    uint16_t x = (MENU_WIDTH - size) / 2;
    display_setRect(MENU_OFFSET, y, MENU_WIDTH, ENTRY_HEIGHT, SYSTEM->selectedMenuEntry == entry ? SELECTED_COLOR : ENTRY_COLOR);
    gfx_drawText(x, y + off, entry->text, MENU_TEXT_SIZE, entry->textColor);
}

/**
 * @brief renders menu to screen based of the global SystemContext
 */
void renderMenu() {
    if (SYSTEM->menuFlags & MENUFLAG_SHOW) {
        uint8_t size = SYSTEM->menuFlags & 0x0F;
        uint16_t yy = ((MENU_HEIGHT - (ENTRY_HEIGHT * size)) / 2); // OFFSET OF TOP AND BOTTOM PART TO CENTER MENU's

        if (size < MAX_MENU_ENTRIES) { //If we want to display 6 entries on this small display we need to remove bottom and top margins
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
            renderMenuEntry(y, &SYSTEM->currentMenuEntries[i]);

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
        if (&SYSTEM->currentMenuEntries[i] == SYSTEM->selectedMenuEntry) {
            SYSTEM->selectedMenuEntry = &SYSTEM->currentMenuEntries[i + 1];

            return 1;
        }
    }

    if ((SYSTEM->menuFlags & MENUFLAG_SCROLLABLE) && (SYSTEM->selectedMenuEntry != &SYSTEM->menu->array[SYSTEM->menu->size - 1])) {
        SYSTEM->currentMenuEntries += sizeof(struct MenuEntry);
        SYSTEM->selectedMenuEntry += sizeof(struct MenuEntry);

        return 1;
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
        if (&SYSTEM->currentMenuEntries[i] == SYSTEM->selectedMenuEntry) {
            SYSTEM->selectedMenuEntry = &SYSTEM->currentMenuEntries[i - 1];
            return 1;
        }
    }

    if ((SYSTEM->menuFlags & MENUFLAG_SCROLLABLE) && (SYSTEM->selectedMenuEntry != SYSTEM->menu->array)) {
        SYSTEM->currentMenuEntries -= sizeof(struct MenuEntry);
        SYSTEM->selectedMenuEntry -= sizeof(struct MenuEntry);

        return 1;
    }

    return 0;
}

/**
 * @brief Create a new entry with default values
 * Don't forget to DEALLOCATE the entries...
 * @param callback of the menu entry
 * @param text of the menu entry
 * @return An menu entry
 */
struct MenuEntry newMenuEntry(uint16_t (*callback)(), char* text) {
    struct MenuEntry entry;
    entry.textColor = WHITE;
    entry.callback = callback;
    entry.text = text;
    return entry;
}

/**
 * @brief Create a new menu (this isn't required for displaying a menu but recommended)
 * @param amount of the needed menu entries
 * @return
 */
struct Menu* newMenu(uint32_t amount) {
    struct Menu* menu = malloc(sizeof(struct Menu));
    menu->size = amount;
    menu->array = malloc(sizeof(struct MenuEntry) * amount);
    return menu;
}

/**
 * @brief Set menu entries based of menu
 * @param menu that wil be displayed
 */
void useMenu(struct Menu* menu) {
    SYSTEM->menuFlags = MENUFLAG_SHOW;

    uint8_t visSize = menu->size;

    if (menu->size > MAX_MENU_ENTRIES) {
        SYSTEM->menuFlags |= MENUFLAG_SCROLLABLE;
        visSize = MAX_MENU_ENTRIES;
    }

    SYSTEM->menuFlags |= visSize;
    SYSTEM->selectedMenuEntry = &menu->array[0];
    SYSTEM->currentMenuEntries = menu->array;
}

/**
 * @brief welp you should de allocate your menu's...
 * @param menu that gets de allocated
 */
void freeMenu(struct Menu* menu) {
    free(menu->array);
    free(menu);
}

