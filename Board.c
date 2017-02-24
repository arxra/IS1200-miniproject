#include "Board.h"

#include "ImageData.h"

unsigned char backgroundColor[4] = {0xaa, 0xaa, 0xaa, 0xff};
unsigned char redColor[4] = {0xff, 0x00, 0x00, 55};
unsigned char greenColor[4] = {0x00, 0xff, 0x00, 55};

void init(enum tileType *b) {
	for(int col = 0; col < COLUMNS; ++ col)
		for(int row = 0; row < ROWS; ++ row)
			b[col + row * COLUMNS] = 0;
}

void printBoard(enum tileType *b) {
	int boardMinXPixel = XRES/2 - TILE_WIDTH /2 * COLUMNS;
	int boardMinYPixel = YRES/2 - TILE_HEIGHT/2 * ROWS;

	paint(colorsTo16Bit(backgroundColor));

	for(int y = 0; y < ROWS; ++ y) {
		for(int x = 0; x < COLUMNS; ++ x) {
			unsigned char drawArea[16*16*4];
			fillColor(drawArea, backgroundColor, 16, 16);
			if((b[x + y*COLUMNS] & TILE_IS_PLACING) &&
			   (b[x + y*COLUMNS] & TILE_SHIP))
				fillColor(drawArea, redColor, 16, 16);
			else if(b[x + y*COLUMNS] & TILE_IS_PLACING) {
				fillColor(drawArea, greenColor, 16, 16);
			}
			frame(drawArea);
			if(b[x + y*COLUMNS] & TILE_MISS)
				renderTile(missPicture, drawArea, 0, 0, 16, 16, 0, 0);
			if(b[x + y*COLUMNS] & TILE_HIT)
				renderTile(explodePicture, drawArea, 0, 0, 16, 16, 0, 0);
			if(b[x + y*COLUMNS] & TILE_SHIP)
				renderTile(shipPicture, drawArea, 0, 0, 16, 16, 0, 0);
			paintimg(drawArea, 16, 16, boardMinXPixel + x*16, boardMinYPixel + y*16);
		}
	}
}
