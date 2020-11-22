//
// Created by ewoudje on 18/11/20.
//

#ifndef ECON_SYSTEM_H
#define ECON_SYSTEM_H

#include "main.h"

#define EPICF_LOOP_CALLBACK EPICF_loopCallback();
#define CURRENT_TIME HAL_GetTick()

void EPICF_loopCallback();

#endif //ECON_SYSTEM_H
