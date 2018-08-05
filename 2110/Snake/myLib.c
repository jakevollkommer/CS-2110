#include "myLib.h"

unsigned short *videoBuffer = (unsigned short*) 0x6000000;
/* drawimage3
 * A function that will draw an arbitrary sized image
 * onto the screen (with DMA) .
 * @param r row to draw the image
 * @param c column to draw the image
 * @param width width of the image
 * @param height height of the image
 * @param image Pointer to the first element of the image.
 */
void drawImage3 (int row, int col, int width, int height, const u16* image) {

    for(int r = 0; r<height; r++)
    {
        DMA[DMA_CHANNEL_3].src = image + OFFSET(r, 0, width);
        DMA[DMA_CHANNEL_3].dst = videoBuffer + OFFSET(row+r, col, 240);
        DMA[DMA_CHANNEL_3].cnt = width |
            DMA_SOURCE_INCREMENT |
            DMA_DESTINATION_INCREMENT |
            DMA_ON;
    }
    /*
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            videoBuffer[(r + col) * 240 + (c + row)] = *image;
            image++;
        }
    }
    */

}


void fillScreen3(unsigned short color) {
    DMA[3].src = &color;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = 240 * 160 | DMA_ON | DMA_SOURCE_FIXED;
}

void waitForVblank() {
    while (SCANLINECOUNTER > 160);
    while (SCANLINECOUNTER < 159);
}

void setPixel(int row, int col, unsigned short color)
{
    videoBuffer[OFFSET(row, col, 240)] = color;
}
/*
void drawRect(int row, int col, int height, int width, unsigned short color)
{
    for(int r = 0; r<height; r++)
    {
        for(int c=0; c<width; c++)
        {
            setPixel(r+row, c+col, color);
        }
    }
}
*/
void drawRect(int row, int col, int height, int width, unsigned short color)
{
    for(int r = 0; r<height; r++)
    {
        /*
        for(int c=0; c<width; c++)
        {
            setPixel(r+row, c+col, color);
        }
        */
        DMA[3].src = &color;
        //DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)];
        DMA[3].dst = videoBuffer + OFFSET(row+r, col, 240);
        DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_ON;
    }
}

void delay(int n)
{
    int volatile x = 0;
    for(int i =0; i<n*8000; i++)
    {
        x = x + 1;
    }
}


