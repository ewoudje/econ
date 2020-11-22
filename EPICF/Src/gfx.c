//
// Created by ewoudje on 19/11/20.
//

#include "gfx.h"
#include "font.h"

/**
 * @brief Draws a char at a certain position with a certain color
 * @todo this could be optimized? ATM it draws pixel per pixel?
 * @param x
 * @param y
 * @param chr the char you want to draw
 * @param size of the character
 * @param color
 */
void gfx_drawChar(uint16_t x, uint16_t y, char chr, uint16_t size, uint16_t color)
{
    uint8_t 	function_char;
    uint8_t 	i,j;

    function_char = chr;

    if (function_char < ' ') {
        chr = 0;
    } else {
        function_char -= 32;
    }

    char temp[CHAR_WIDTH];
    for(uint8_t k = 0; k<CHAR_WIDTH; k++)
    {
        temp[k] = font[function_char][k];
    }

    // Draw pixels
    for (j=0; j<CHAR_WIDTH; j++) {
        for (i=0; i<CHAR_HEIGHT; i++) {
            if (temp[j] & (1<<i)) {
                if(size == 1)
                {
                    display_setPixel(x+j, y+i, color);
                }
                else
                {
                    display_setRect(x+(j*size), y+(i*size), size, size, color);
                }
            }
        }
    }
}

/**
 * @brief draws a whole string with gfx_drawChar
 * @note for more info see gfx_drawChar
 * @param x
 * @param y
 * @param text
 * @param size
 * @param color
 */
void gfx_drawText(uint16_t x, uint16_t y, char* text, uint16_t size, uint16_t color) {
    while (*text) {
        gfx_drawChar(*text++, x, y, BLACK, size);
        x += CHAR_WIDTH * size;
    }
}
