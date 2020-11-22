//
// Created by ewoudje on 21/11/20.
//

#include "platform/display.h"

#include "EPICF/game.h"
#include "EPICF/system.h"

//This game is a simple test game where you can move around as a white dot with the buttons
//The Joystick isn't used here since i have yet to have that component...
struct GameState {
    uint16_t posX, posY;
    uint16_t counterX, counterY;
};

//I might want to do this differently
//I also tried making a global variable and give it the current pointer but it would be risky
//if i would be moving gamestate data around in memory
#define gameState ((struct GameState*)(SYSTEM->currentGame))

uint16_t resume() {
    //You are supposed to fully redraw the screen on resume
    //Since the system can have drawn other things at the surface
    //This could be beter but slower peformance if i would copy the framebuffer of the screen to my chip to backup it
    // and then draw it on resume.

    display_clear(BLACK);
    display_setRect(gameState->posX - 5, gameState->posY - 5, gameState->posX + 5, gameState->posY + 5, WHITE);

    //You can also make a game without this macro as long as you call the correct calls
    //But other macros might depend on it, so this is the recommended way of doing things
    GAME_LOOP_START

        //Here we add the delta to the side we want to go
        GAME_INPUT(UP)
        if (GAME_INPUT_PRESSED) {
            gameState->counterY += delta;
        }

        GAME_INPUT(DOWN)
        if (GAME_INPUT_PRESSED) {
            gameState->counterY -= delta;
        }

        GAME_INPUT(RIGHT)
        if (GAME_INPUT_PRESSED) {
            gameState->counterX += delta;
        }

        GAME_INPUT(LEFT)
        if (GAME_INPUT_PRESSED) {
            gameState->counterX -= delta;
        }

        //If the counters reach above 100 we move our white block by 1 pixel
        //So this means we move 10 pixels per second if we hold the key in
        //As you can see i also don't set the counters to 0 when we reach it, this i bad practice since
        // you can skip time if you do that (ofc in this example it doesn't matter much)

        //I know this can beter but this is a test game and otherwise i have to think...
        if (gameState->counterX > 100) {
            display_setRect(gameState->posX - 5, gameState->posY - 5, gameState->posX - 4, gameState->posY + 5, BLACK);
            gameState->posX++;
            display_setRect(gameState->posX + 5, gameState->posY - 5, gameState->posX + 4, gameState->posY + 5, WHITE);
            gameState->counterX -= 100;
        }

        if (gameState->counterY > 100) {
            display_setRect(gameState->posX - 5, gameState->posY - 5, gameState->posX - 5, gameState->posY - 4, BLACK);
            gameState->posY++;
            display_setRect(gameState->posX + 5, gameState->posY + 4, gameState->posX + 5, gameState->posY + 5, WHITE);
            gameState->counterY -= 100;
        }

        if (gameState->counterX < 0) {
            display_setRect(gameState->posX + 5, gameState->posY - 5, gameState->posX + 4, gameState->posY + 5, BLACK);
            gameState->posX--;
            display_setRect(gameState->posX - 5, gameState->posY - 5, gameState->posX - 4, gameState->posY + 5, WHITE);
            gameState->counterX += 100;
        }

        if (gameState->counterY < 0) {
            display_setRect(gameState->posX + 5, gameState->posY + 4, gameState->posX + 5, gameState->posY + 5, BLACK);
            gameState->posY--;
            display_setRect(gameState->posX - 5, gameState->posY - 5, gameState->posX - 5, gameState->posY - 4, WHITE);
            gameState->counterY += 100;
        }
    GAME_LOOP_END //END OF LOOP macro
}

//This is called on the initialization, so if this is called you have to prepare your gamestate
//with correct starting data.
uint16_t start() {
    //INIT
    gameState->posX = DISPLAY_WIDTH / 2;
    gameState->posY = DISPLAY_HEIGHT / 2;
    gameState->counterX = 0;
    gameState->counterY = 0;

    //And of course call resume to start the actual game
    //If you need to other things at resume then at startup you can always split it with another function
    resume();
}

//This is an in memory definition of my game
//This will be used by the system to display the name on the menu's to allocate the gamestate
// and starting/resuming the game

//There is an important detail do about the naming of this variable...
//This data is accessed by extern definition so this name must be equal as specified in CMake files
struct GameDescription TestGame = {
        .name = "Test Game",
        .gameCSize = sizeof(*gameState),
        .start = start,
        .resume = resume
};