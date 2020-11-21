//
// Created by ewoudje on 19/11/20.
//

#ifndef ECON_INPUT_H
#define ECON_INPUT_H

#define EPICF_UPDATE_INPUT EPICF_updateInputCallback();

#define EPICF_INPUT_VAR(name) char name;

#define EPICF_INPUT_BUTTON_UP(var) (var & 0b000001)
#define EPICF_INPUT_BUTTON_DOWN(var) (var & 0b000010)
#define EPICF_INPUT_BUTTON_LEFT(var) (var & 0b000100)
#define EPICF_INPUT_BUTTON_RIGHT(var) (var & 0b001000)
#define EPICF_INPUT_BUTTON_F1(var) (var & 0b010000)
#define EPICF_INPUT_BUTTON_F2(var) (var & 0b100000)

extern EPICF_INPUT_VAR(EPICF_buttons)

void EPICF_updateInputCallback();

#endif //ECON_INPUT_H
