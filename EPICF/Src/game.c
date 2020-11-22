//
// Created by ewoudje on 21/11/20.
//

#include "game.h"
#include "system.h"

/**
 * @brief This function loads a game
 * @note If you provide no description it will take the existing one
 * @note This also unloads prev game if not already done (for safety)
 * @param description of the game you wanna load
 */
void loadGame(struct GameDescription* description) {
    if (!description) //I am allowing restarting the game by calling this function a second time with a nullptr
        description = SYSTEM->gameDesc;

    unloadGame();   //For insurance normaly unloadGame should be called before this but you never know
                    //And we don't want any memory leaks do we?

    SYSTEM->currentGame = malloc(description->gameCSize);
    SYSTEM->gameDesc = description;
}

/**
 * @brief This function unloads a game
 */
void unloadGame() {
    if (SYSTEM->currentGame)
        free(SYSTEM->currentGame);
    if (SYSTEM->gameDesc)
        free(SYSTEM->gameDesc);
}