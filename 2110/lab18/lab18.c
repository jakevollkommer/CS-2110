typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;


#define REG_DISPCTL *(u16 *)0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)

#define COLOR(r,g,b) ((r) | (g) << 5 | (b) << 10)
#define RED COLOR(31,0,0)
#define WHITE COLOR(31,31,31)
#define GREEN COLOR(0, 31, 0)
#define BLACK 0

#define OFFSET(r,c) ((r)*240+(c))


unsigned short *videoBuffer = (u16 *)0x6000000;

void setPixel(int row, int col, u16 color);
void drawRectangle(int row, int col, int width, int height, u16 color);
void drawHollowRectangle(int row, int col, int width, int height, u16 color);

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	//use the functions you wrote to draw a pretty picture here!

	setPixel(10, 10, RED);
	drawRectangle(20, 20, 20, 20, WHITE);
	drawHollowRectangle(40, 40, 20, 20, GREEN);

	while(1);
}

void setPixel(int row, int col, u16 color)
{
    videoBuffer[OFFSET(row, col)] = color;
}

void drawRectangle(int row, int col, int width, int height, u16 color)
{
    for (int r = 0; r<height; r++) {
        for (int c = 0; c < width; c++) {
            setPixel(r+row, c+col, color);
        }
    }
}

void drawHollowRectangle(int row, int col, int width, int height, u16 color)
{
    for (int w = 0; w < width; w++) {
        setPixel(row, row + w, color);
    }
    for (int i = 0; i < height; i++) {
        setPixel(row + i, col, color);
        setPixel(row + i, col + width, color);
    }
    for (int x = 0; x <= width; x++) {
        setPixel(row + height, row + x, color);
    }
}
