//
// Created by ewoudje on 18/11/20.
//

#ifndef EPICF_H
#define EPICF_H

#include "../Inc/error.h"

ERROR_CODE EPICF_startLoop();

ERROR_CODE EPICF_initSystem();

void EPICF_initGames(uint8_t length, void** games);

#endif //EPICF_H
