#include "main.h"
#include "../Platform/platform/input.h"

EPICF_INPUT_VAR(EPICF_buttons)

void EPICF_updateInputCallback() {
    EPICF_buttons = 0x00;
    EPICF_buttons |= HAL_GPIO_ReadPin(BUTTON_UP_GPIO_Port, BUTTON_UP_Pin) << 0;
    EPICF_buttons |= HAL_GPIO_ReadPin(BUTTON_DOWN_GPIO_Port, BUTTON_DOWN_Pin) << 1;
    EPICF_buttons |= HAL_GPIO_ReadPin(BUTTON_RIGHT_GPIO_Port, BUTTON_RIGHT_Pin) << 3;
    EPICF_buttons = ~(EPICF_buttons | 0xF4);
}