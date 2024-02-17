#include "../headers/header.h"

bool GameRunning = false;
int TicksLastFrame;
player_t player;

/**
 * setup_game - initialize player variables and load wall textures
 *
*/

void setup_game(void)
{

	player.x = SCREEN_WIDTH / 2;
	player.y = SCREEN_HEIGHT / 2;
	player.width = 1;
	player.height = 30;
	player.walk_direction = 0;
	player.walk_speed = 100;
	player.turn_direction = 0;
	player.turn_speed = 45 * (PI / 180);
	player.rotation_angle = PI / 2;
	WallTexturesready();
}

/**
 * update_game - update_game delta time, the ticks last frame
 *          the player movement and the ray casting
 *
*/
void update_game(void)
{
	float DeltaTime;
	int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - TicksLastFrame);

	if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH)
	{
		SDL_Delay(timeToWait);
	}
	DeltaTime = (SDL_GetTicks() - TicksLastFrame) / 1000.0f;

	TicksLastFrame = SDL_GetTicks();

	move_player(DeltaTime);
	cast_allrays();
}

/**
 * render_game - calls all functions needed for on-screen rendering
 *
*/

void render_game(void)
{
	clear_colorBuffer(0xFF000000);

	render_wall();

	render_map();
	render_rays();
	render_player();

	render_colorBuffer();
}

/**
 * Destroy - free wall textures and destroy window
 *
*/
void destroy_game(void)
{
	freeWallTextures();
	window_destroy();
}

/**
 * main - main function
 * Return: 0
*/

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	GameRunning = window_init();

	setup_game();

	while (GameRunning)
	{
		handle_input();
		update_game();
		render_game();
	}
	destroy_game();
	return (0);
}