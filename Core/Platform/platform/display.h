//
// Created by ewoudje on 19/11/20.
//

#ifndef ECON_DISPLAY_H
#define ECON_DISPLAY_H

#include <stdint.h>

#define DISPLAY_HEIGHT   240
#define DISPLAY_WIDTH    320

#define BLACK       0x0000
#define NAVY        0x000F
#define DARKGREEN   0x03E0
#define DARKCYAN    0x03EF
#define MAROON      0x7800
#define PURPLE      0x780F
#define OLIVE       0x7BE0
#define LIGHTGREY   0xC618
#define DARKGREY    0x7BEF
#define BLUE        0x001F
#define GREEN       0x07E0
#define CYAN        0x07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF
#define ORANGE      0xFD20
#define GREENYELLOW 0xAFE5
#define PINK        0xF81F

void display_setPixel(uint16_t x, uint16_t y, uint16_t color);

void display_setRect(uint16_t x, uint16_t y, uint16_t xx, uint16_t yy, uint16_t color);

void display_init();

#endif //ECON_DISPLAY_H
