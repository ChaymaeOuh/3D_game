#ifndef HEADER_H
#define HEADER_H

#include <C:\SDL2\include\SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <float.h>
#include "upng.h"

/* Constants */

#define PI 3.14159265
#define TWO_PI 6.28318530

#define TILE_SIZE 30 //64
#define MINIMAP_SCALE_FACTOR 0.25

#define SCREEN_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define SCREEN_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

#define FOV_ANGLE (60 * (PI / 180))

#define NUM_RAYS SCREEN_WIDTH

#define PROJ_PLANE ((SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2))

#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)

#define MAP_NUM_ROWS 12
#define MAP_NUM_COLS 20

#define NUM_TEXTURES 3

typedef uint32_t color_t;

/* Input */
void handle_input(void);
extern bool GameRunning;

/* Draw*/
bool window_init(void);
void window_destroy(void);
void clear_colorBuffer(color_t color);
void render_game(void);
void render_colorBuffer(void);
void draw_pixel(int x, int y, color_t color);
void draw_rect(int x, int y, int width, int height, color_t color);
void draw_line(int x0, int y0, int x1, int y1, color_t color);

/* Map */
bool detect_collision(float x, float y);
bool is_in_map(float x, float y);
void render_map(void);
int map_value(int row, int col);

/* Player */
/**
 * struct player_s - struct for the textures
 * @x: x coordinate
 * @y: y coordinate
 * @width: player width
 * @height: player height
 * @turn_direction: Turn Direction
 * @walk_direction: Walk Direction
 * @rotation_angle: player rotation angle
 * @walk_speed: walk speed
 * @turn_speed: turn speed
 */

typedef struct player_s
{
	float x;
	float y;
	float width;
	float height;
	int turn_direction;
	int walk_direction;
	float rotation_angle;
	float walk_speed;
	float turn_speed;
} player_t;

extern player_t player;

void move_player(float DeltaTime);
void render_player(void);

/* Ray */
/**
 * struct ray_s - struct for the textures
 * @ray_angle: ray angle
 * @wall_hitx: wall hit x coordinate
 * @wall_hity: wall hit x coordinate
 * @distance: ditance to the wall
 * @wall_hitv: verify hit vertical
 * @wall_hitc: wall hit content
 */

typedef struct ray_s
{
	float ray_angle;
	float wall_hitx;
	float wall_hity;
	float distance;
	bool wall_hitv;
	int wall_hitc;
} ray_t;

extern ray_t rays[NUM_RAYS];

float distance_points(float x1, float y1, float x2, float y2);
bool rayfacing_up(float angle);
bool rayfacing_down(float angle);
bool rayfacing_left(float angle);
bool rayfacing_right(float angle);
void cast_allrays(void);
void cast_ray(float ray_angle, int strip_id);
void render_rays(void);
void h_intersection(float ray_angle);
void v_intersection(float ray_angle);

/* Texture */
/**
 * struct texture_s - struct for the textures
 * @width: texture width
 * @height: texture height
 * @texture_buffer: pointer to texture buffer
 * @upngTexture: pointer to upng buffer
 *
 */

typedef struct texture_s
{
	int width;
	int height;
	color_t *texture_buffer;
	upng_t *upngTexture;
} texture_t;

texture_t wallTextures[NUM_TEXTURES];

void WallTexturesready(void);
void freeWallTextures(void);

/* wall */
void render_wall(void);

#endif /* HEADER_H */