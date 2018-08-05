#include <stdlib.h>
#include <stdio.h>

#include "myLib.h"
#include "text.h"
#include "game.h"
#include "images.h"

// State enum definition
enum GBAState {
    START,
    START_NODRAW,
    PLAY,
    GAME_OVER,
    GAME_ENDED,
};

enum GBAState state = START;

int offset = 30;
int isPressed = 0;
int wait = 30;
int frames = 0;

void startGame() {
    fillScreen3(BLACK);
    drawImage3(0,0,240,160,startscreen);
    drawString(20, 30, "Press start to begin!", WHITE);
    state = START_NODRAW;
}

void startNoDraw() {
    if (KEY_DOWN_NOW(BUTTON_START) && !isPressed) {
        state = PLAY;
        fillScreen3(BLACK);
        makeNewBox();
        isPressed = 1;
        offset = 30;
    }
}

void play() {
    if (!isPressed) {
        if (KEY_DOWN_NOW(BUTTON_LEFT)) {
            //direction is left, new head is one column left
            offset = -1;
        }
        if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
            //direction is left, new head is one column right
            offset = 1;
        }
        if (KEY_DOWN_NOW(BUTTON_UP)) {
            //direction is left, new head is one row up
            offset = -30;
        }
        if (KEY_DOWN_NOW(BUTTON_DOWN)) {
            //direction is left, new head is one row down
            offset = 30;
        }
        isPressed = 1;
        if (frames >= wait) {
            if (!updateSnake(offset)) {
                state = GAME_OVER;
            }
            frames = 0;
        }
    }
}

void endGame() {
    gameOver();
    state = GAME_ENDED;
}

int main() {

    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    while(1) {
        waitForVblank();
        switch(state) {
        case START:
            startGame();
        case START_NODRAW:
            startNoDraw();
            break;
        case PLAY:
            play();
            break;
        case GAME_OVER:
            endGame();
            break;
        case GAME_ENDED:
            if (KEY_DOWN_NOW(BUTTON_START) && !isPressed) {
                startGame();
                isPressed = 1;
            }
            break;
        }
        if (!KEY_DOWN_NOW(BUTTON_START)) {
            isPressed = 0;
        }
        frames++;
    }
    return 0;
}

