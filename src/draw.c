#include "../headers/header.h"

/**
 * draw_rect - draw rectangle
 * @x: x coordinate
 * @y: y coordinate
 * @width: rectangle width
 * @height: rectangle height
 * @color: pixel color
*/

void draw_rect(int x, int y, int width, int height, color_t color)
{
	int i, j;
	for (i = x; i <= (x + width); i++)
		for (j = y; j <= (y + height); j++)
			draw_pixel(i, j, color);
}

/**
 * draw_line - draw line
 * @x0: x coordinate init
 * @y0: y coordinate init
 * @x1: x coordinate end
 * @y1: y coordinate end
 * @color: pixel color
*/

void draw_line(int x0, int y0, int x1, int y1, color_t color)
{
	float xInc, yInc, currentX, currentY;
	int i, longSideLength, deltaX,  deltaY;

	deltaX = (x1 - x0);
	deltaY = (y1 - y0);

	longSideLength = (abs(deltaX) >= abs(deltaY)) ? abs(deltaX) : abs(deltaY);

	xInc = deltaX / (float)longSideLength;
	yInc = deltaY / (float)longSideLength;

	currentX = x0;
	currentY = y0;

	for (i = 0; i < longSideLength; i++)
	{
		draw_pixel(round(currentX), round(currentY), color);
		currentX += xInc;
		currentY += yInc;
	}
}