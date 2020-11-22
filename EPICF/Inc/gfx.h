//
// Created by ewoudje on 19/11/20.
//

#ifndef EPICF_GFX_H
#define EPICF_GFX_H

#include "platform/display.h"
#include "default.h"

void gfx_drawText(uint16_t x, uint16_t y, char* text, uint16_t size, uint16_t color);
void gfx_drawChar(uint16_t x, uint16_t y, char chr, uint16_t size, uint16_t color);

#endif //EPICF_GFX_H
