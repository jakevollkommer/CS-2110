#include "game.h"
#include "myLib.h"
#include "text.h"
#include "images.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int size = 1;
int collision = 0;
int newBox;
int head = 0;
int tail = 0;
int prevDirection = 0;
int currDirection = 30;
int score = 0;
int mouthState = 0;

//boxes are 8x8 pixels
//30 boxes per row, 20 rows
//600 boxes on screen
int snakeBody[600];

int updateSnake(int offset) {
    //change the mouthState from open/closed mouth
    mouthState = (mouthState + 1) % 4;

    if ((offset * -1) == currDirection && size > 1) {
        //stop snake from going backwards
        offset = offset * -1;
    } else if (offset != currDirection) {
        //update current and previous directions
        prevDirection = currDirection;
        currDirection = offset;
    }

    int tailRow = (tail / 30) * 8;
    int tailColumn = (tail % 30) * 8;

    int headRow = (head / 30) * 8;
    int headColumn = (head % 30) * 8;

    //check for collision with self
    for (int i = 0; i < size; i++) {
        if (snakeBody[i] == head + offset) {
            return 0;
        }
    }

    //replace previous head with a body
    if (size > 1) {
        drawImage3(headRow, headColumn, 8, 8, snakebody);
    }
    //draw new head position
    int r = (offset / 30) * 8 + headRow;
    int c = (offset % 30) * 8 + headColumn;
    //check for collision with edges
    if (r >= 160 || c >= 240 || r < 0 || c < 0) {
        return 0;
    }
    drawHead(r, c, offset);
    drawRect(tailRow, tailColumn, 8, 8, BLACK);

    //check for collision with newBox
    if (head + offset == newBox) {
        growSnake();
    } else {
        //remove the tail
        drawRect(tailRow, tailColumn, 8, 8, BLACK);
    }

    //update body
    for (int i = 0; i < size - 1; i++) {
        snakeBody[i] = snakeBody[i + 1];
    }
    snakeBody[size - 1] = head + offset;

    //update head and tail pointer
    head = head + offset;
    tail = snakeBody[0];

    return 1;
}

void drawHead(int row, int column, int offset) {
    switch (offset) {
    case 1:
        if (mouthState < 2) {
            drawImage3(row, column, 8, 8, snakehead);
        } else {
            drawImage3(row, column, 8, 8, snakeheadb);
        }
        break;
    case -1:
        if (mouthState < 2) {
            drawImage3(row, column, 8, 8, snakehead2);
        } else {
            drawImage3(row, column, 8, 8, snakehead2b);
        }
        break;
    case 30:
        //use more natural turns based on which direction you turned from
        if (prevDirection == 1) {
            if (mouthState < 2) {
                drawImage3(row, column, 8, 8, snakehead3);
            } else {
                drawImage3(row, column, 8, 8, snakehead3b);
            }
        } else {
            if (mouthState < 2) {
                drawImage3(row, column, 8, 8, snakehead5);
            } else {
                drawImage3(row, column, 8, 8, snakehead5b);
            }
        }
        break;
    case -30:
        if (prevDirection == 1) {
            if (mouthState < 2) {
                drawImage3(row, column, 8, 8, snakehead6);
            } else {
                drawImage3(row, column, 8, 8, snakehead6b);
            }
        } else {
            if (mouthState < 2) {
                drawImage3(row, column, 8, 8, snakehead4);
            } else {
                drawImage3(row, column, 8, 8, snakehead4b);
            }
        }
        break;
    }
}

void gameOver() {
    drawString(10,10,"Game over!", WHITE);
    char str[1];
    sprintf(str, "Score: %d", score);
    drawString(20,10,str,WHITE);
    drawString(50,50,"Press start to play again!",WHITE);

    size = 1;
    collision = 0;
    newBox = -1;
    head = 0;
    tail = 0;
    prevDirection = 0;
    currDirection = 30;
    score = 0;
    mouthState = 0;

    memset(snakeBody, -1, sizeof(snakeBody));
}

void growSnake() {
    snakeBody[0] = tail;
    size++;
    score++;
    makeNewBox();
}

void clearBox(int box) {
    int row = (box / 30) * 8;
    int col = (box % 30) * 8;
    drawRect(row, col, 8, 8, BLACK);
}

void makeNewBox() {
    int boxNum = rand() % 601;
    int row = (boxNum / 30) * 8;
    int column = (boxNum % 30) * 8;
    drawImage3(row, column, 8, 8, cookie);
    newBox = boxNum;
}
