#include "../headers/header.h"


/**
 * move_player - set the next position of the player
 * @DeltaTime: time elapsed since the last frame
*/

void move_player(float DeltaTime)
{
	float moveStep, newPlayerX, newPlayerY;

	player.rotation_angle += player.turn_direction * player.turn_speed * DeltaTime;
	moveStep = player.walk_direction * player.walk_speed * DeltaTime;

	newPlayerX = player.x + cos(player.rotation_angle) * moveStep;
	newPlayerY = player.y + sin(player.rotation_angle) * moveStep;

	if (!detect_collision(newPlayerX, newPlayerY))
	{
		player.x = newPlayerX;
		player.y = newPlayerY;
	}
}

/**
 * render_player - render the player
 *
*/

void render_player(void)
{
	draw_rect(
		player.x * MINIMAP_SCALE_FACTOR,
		player.y * MINIMAP_SCALE_FACTOR,
		player.width * MINIMAP_SCALE_FACTOR,
		player.height * MINIMAP_SCALE_FACTOR,
		0xFFFFFFFF
	);
}


