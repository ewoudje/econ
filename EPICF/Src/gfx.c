//
// Created by ewoudje on 19/11/20.
//

#include "gfx.h"
#include "font.h"

/*Draws a character (fonts imported from fonts.h) at X,Y location with specified font colour, size and Background colour*/
/*See fonts.h implementation of font on what is required for changing to a different font when switching fonts libraries*/
void gfx_drawChar(char chr, uint16_t x, uint16_t y, uint16_t color, uint16_t size)
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

void gfx_drawText(uint16_t x, uint16_t y, char* text, uint16_t size) {
    while (*text) {
        gfx_drawChar(*text++, x, y, BLACK, size);
        x += CHAR_WIDTH * size;
    }
}
