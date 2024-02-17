#include "../headers/header.h"

static const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6},
	{6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0, 6},
	{6, 0, 7, 0, 0, 0, 0, 7, 0, 0, 0, 6, 0, 7, 7, 7, 0, 0, 0, 6},
	{6, 0, 7, 0, 0, 0, 0, 7, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6},
	{6, 0, 7, 7, 7, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
	{6, 0, 0, 0, 0, 0, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0, 6},
	{6, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 6},
	{6, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 7, 0, 6},
	{6, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 7, 0, 0, 0, 0, 7, 7, 6},
	{6, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 6},
	{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6}
};

/**
 * detect_collision - Checks for collisions
 * with the wall in the next player advance
 * @x: next x coordinate
 * @y: next y coordinate
 * Return: True (collision detected) False: Otherwise
*/

bool detect_collision(float x, float y)
{
	int mapGridX, mapGridY;

	if (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE ||
			y < 0 || y >= MAP_NUM_ROWS * TILE_SIZE)
		return (true);

	mapGridX = floor(x / TILE_SIZE);
	mapGridY = floor(y / TILE_SIZE);
	return (map[mapGridY][mapGridX] != 0);
}

/**
 * is_in_map - check if we continue within the map
 * @x: next x coordinate
 * @y: next y coordinate
 * @Return: True (within the map), False : Otherwise
*/

bool is_in_map(float x, float y)
{
	return (x >= 0 && x <= MAP_NUM_COLS * TILE_SIZE &&
				y >= 0 && y <= MAP_NUM_ROWS * TILE_SIZE);
}

/**
 * map_value - get the map value
 * @row: map row to check
 * @col: map column to check
 * @Return: The position value in the map
*/

int map_value(int row, int col)
{

	return (map[row][col]);

}

/**
 * render_map - render the map
 *
*/

void render_map(void)
{
	int i, j, tileX, tileY;
	color_t tileColor;

	for (i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (j = 0; j < MAP_NUM_COLS; j++)
		{
			tileX = j * TILE_SIZE;
			tileY = i * TILE_SIZE;
			tileColor = map[i][j] != 0 ? 0xFFFFFFFF : 0x00000000;

			draw_rect(
				tileX * MINIMAP_SCALE_FACTOR,
				tileY * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR,
				tileColor
			);
		}
	}
}