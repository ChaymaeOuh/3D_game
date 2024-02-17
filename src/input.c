#include "../headers/header.h"

/**
 * SDL_KEYDOWN_FUNC - process input when a key is down
 * @event: union that contains structures for the different event types
*/

void SDL_KEYDOWN_FUNC(SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_ESCAPE)
		GameRunning = false;
	if (event.key.keysym.sym == SDLK_UP)
		player.walk_direction = +1;
	if (event.key.keysym.sym == SDLK_DOWN)
		player.walk_direction = -1;
	if (event.key.keysym.sym == SDLK_RIGHT)
		player.turn_direction = +1;
	if (event.key.keysym.sym == SDLK_LEFT)
		player.turn_direction = -1;
	if (event.key.keysym.sym == SDLK_w)
		player.walk_direction = +1;
	if (event.key.keysym.sym == SDLK_s)
		player.walk_direction = -1;
	if (event.key.keysym.sym == SDLK_a)
		player.turn_direction = -1;
	if (event.key.keysym.sym == SDLK_d)
		player.turn_direction = +1;
}

/**
 * SDL_KEYUP_FUNC - process input when a key is up
 * @event: union that contains structures for the different event types
*/

void SDL_KEYUP_FUNC(SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_UP)
		player.walk_direction = 0;
	if (event.key.keysym.sym == SDLK_DOWN)
		player.walk_direction = 0;
	if (event.key.keysym.sym == SDLK_RIGHT)
		player.turn_direction = 0;
	if (event.key.keysym.sym == SDLK_LEFT)
		player.turn_direction = 0;
	if (event.key.keysym.sym == SDLK_w)
		player.walk_direction = 0;
	if (event.key.keysym.sym == SDLK_s)
		player.walk_direction = 0;
	if (event.key.keysym.sym == SDLK_a)
		player.turn_direction = 0;
	if (event.key.keysym.sym == SDLK_d)
		player.turn_direction = 0;
}

/**
 * handle_input - process input from the keyboard
 *
*/
void handle_input(void)
{
	SDL_Event event;

	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT)
		GameRunning = false;
	else if (event.type == SDL_KEYDOWN)
		SDL_KEYDOWN_FUNC(event);
	else if (event.type == SDL_KEYUP)
		SDL_KEYUP_FUNC(event);
}