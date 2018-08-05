// Name: YOUR NAME HERE

#include "myLib.h"
#include "student.h"
#include "math.h"
#include "bill1.h"
#include "bill2.h"

u16 *videoBuffer = (u16 *)0x6000000;

void rotateImageAndDraw(int width, int height, const unsigned short *image)
{
    for(int r = 0; r < height; r++) {
        DMA[DMA_CHANNEL_3].src = image + OFFSET(r, 120, width);
        DMA[DMA_CHANNEL_3].dst = videoBuffer + OFFSET(height - r, 120, 240);
        DMA[DMA_CHANNEL_3].cnt = width |
            DMA_SOURCE_INCREMENT |
            DMA_DESTINATION_DECREMENT |
            DMA_ON;
    }
    // This function takes an image and flips it both horizontally and vertically,
    // and then draws it in the top left quadrant of the GBA screen (with DMA).

}

void flipHorizontallyAndDraw(int width, int height, const unsigned short *image)
{
    for(int r = height; r > 0; r--) {
        DMA[DMA_CHANNEL_3].src = image + OFFSET(r, 120, width);
        DMA[DMA_CHANNEL_3].dst = videoBuffer + OFFSET(r, 120, 240);
        DMA[DMA_CHANNEL_3].cnt = width |
            DMA_SOURCE_DECREMENT |
            DMA_DESTINATION_INCREMENT |
            DMA_ON;
    }
    // This function takes an image and flips it horizontally,
    // and then draws it in the top right quadrant of the GBA screen (with DMA).

}

void drawImage3(int row, int col, int width, int height, const unsigned short *image)
{
    for(int r = 0; r<height; r++)
    {
        DMA[DMA_CHANNEL_3].src = image + OFFSET(r, 0, width);
        DMA[DMA_CHANNEL_3].dst = videoBuffer + OFFSET(row+r, col, 240);
        DMA[DMA_CHANNEL_3].cnt = width |
            DMA_SOURCE_INCREMENT |
            DMA_DESTINATION_INCREMENT |
            DMA_ON;
    }
    // This function  will draw an arbitrary sized image
    // onto the screen (with DMA).
}


int main(void)
{
    // so that whatever you want to draw actually gets drawn on the screen.
    REG_DISPCNT = 3 | BG2_ENABLE;

    waitForVblank();
    rotateImageAndDraw(120,80, student_data);
    flipHorizontallyAndDraw(120,80, math_data);
    drawImage3(80, 0, 120, 80, bill1_data);
    drawImage3(80, 120, 120, 80, bill2_data);

    // You want to draw the student image with the manipulation in the top left quadrant,
    // the math image with the manipulation in the top right quadrant,
    // the first Bill image in the bottom left quadrant,
    // and the second Bill image in the bottom right quadrant of the GBA screen.

    // Wait after drawing
    while (1);
}


void waitForVblank()
{
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);
}
