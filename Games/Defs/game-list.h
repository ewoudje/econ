//
// Created by ewoudje on 21/11/20.
//

#ifndef GAME_LIST_H
#define GAME_LIST_H

#include "game.h"
#define GAMES_LENGTH 1
#define GAMES_LIST (void**)&gameList

extern struct GameDescription TestGame;

static const void* gameList[GAMES_LENGTH] = { (void*)&TestGame };



#endif //GAME_LIST_H
