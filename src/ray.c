#include "../headers/header.h"

ray_t rays[NUM_RAYS];

static bool foundHorzWallHit, foundVertWallHit;
static float horzWallHitX, horzWallHitY, vertWallHitX, vertWallHitY;
static int horzWallContent, vertWallContent;

/**
 * h_intersection - Finds horizontal intersection with the wall
 * @ray_angle: current ray angle
 *
 */

void h_intersection(float ray_angle)
{
	float nextHorzTouchX, nextHorzTouchY, xintercept, yintercept, xstep, ystep;

	foundHorzWallHit = false;
	horzWallHitX = horzWallHitY = horzWallContent = 0;

	yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += rayfacing_down(ray_angle) ? TILE_SIZE : 0;

	xintercept = player.x + (yintercept - player.y) / tan(ray_angle);

	ystep = TILE_SIZE;
	ystep *= rayfacing_up(ray_angle) ? -1 : 1;
	xstep = TILE_SIZE / tan(ray_angle);
	xstep *= (rayfacing_left(ray_angle) && xstep > 0) ? -1 : 1;
	xstep *= (rayfacing_right(ray_angle) && xstep < 0) ? -1 : 1;
	nextHorzTouchX = xintercept;
	nextHorzTouchY = yintercept;

	while (is_in_map(nextHorzTouchX, nextHorzTouchY))
	{
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (rayfacing_up(ray_angle) ? -1 : 0);

		if (detect_collision(xToCheck, yToCheck))
		{
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallContent = map_value((int)floor(yToCheck / TILE_SIZE),
									   (int)floor(xToCheck / TILE_SIZE));
			foundHorzWallHit = true;
			break;
		}
		nextHorzTouchX += xstep;
		nextHorzTouchY += ystep;
	}
}

/**
 * v_intersection - Finds vertical intersection with the wall
 * @ray_angle: current ray angle
 *
 */

void v_intersection(float ray_angle)
{
	float nextVertTouchX, nextVertTouchY;
	float xintercept, yintercept, xstep, ystep;

	foundVertWallHit = false;
	vertWallHitX = 0;
	vertWallHitY = 0;
	vertWallContent = 0;

	xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += rayfacing_right(ray_angle) ? TILE_SIZE : 0;
	yintercept = player.y + (xintercept - player.x) * tan(ray_angle);

	xstep = TILE_SIZE;
	xstep *= rayfacing_left(ray_angle) ? -1 : 1;
	ystep = TILE_SIZE * tan(ray_angle);
	ystep *= (rayfacing_up(ray_angle) && ystep > 0) ? -1 : 1;
	ystep *= (rayfacing_down(ray_angle) && ystep < 0) ? -1 : 1;
	nextVertTouchX = xintercept;
	nextVertTouchY = yintercept;

	while (is_in_map(nextVertTouchX, nextVertTouchY))
	{
		float xToCheck = nextVertTouchX + (rayfacing_left(ray_angle) ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (detect_collision(xToCheck, yToCheck))
		{
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallContent = map_value((int)floor(yToCheck / TILE_SIZE),
									   (int)floor(xToCheck / TILE_SIZE));
			foundVertWallHit = true;
			break;
		}
		nextVertTouchX += xstep;
		nextVertTouchY += ystep;
	}
}

/**
 * cast_ray - casting of each ray
 * @ray_angle: current ray angle
 * @strip_id: ray strip identifier
 */

void cast_ray(float ray_angle, int strip_id)
{
	float horzHitDistance, vertHitDistance;

	ray_angle = remainder(ray_angle, TWO_PI);
	if (ray_angle < 0)
		ray_angle = TWO_PI + ray_angle;

	h_intersection(ray_angle);

	v_intersection(ray_angle);

	horzHitDistance = foundHorzWallHit
		? distance_points(player.x, player.y, horzWallHitX, horzWallHitY)
		: FLT_MAX;
	vertHitDistance = foundVertWallHit
		? distance_points(player.x, player.y, vertWallHitX, vertWallHitY)
		: FLT_MAX;

	if (vertHitDistance < horzHitDistance)
	{
		rays[strip_id].distance = vertHitDistance;
		rays[strip_id].wall_hitx = vertWallHitX;
		rays[strip_id].wall_hity = vertWallHitY;
		rays[strip_id].wall_hitc = vertWallContent;
		rays[strip_id].wall_hitv = true;
		rays[strip_id].ray_angle = ray_angle;
	}
	else
	{
		rays[strip_id].distance = horzHitDistance;
		rays[strip_id].wall_hitx = horzWallHitX;
		rays[strip_id].wall_hity = horzWallHitY;
		rays[strip_id].wall_hitc = horzWallContent;
		rays[strip_id].wall_hitv = false;
		rays[strip_id].ray_angle = ray_angle;
	}

}

/**
 * cast_allrays - cast of all rays
 *
 */

void cast_allrays(void)
{
	int col;

	for (col = 0; col < NUM_RAYS; col++)
	{
		float ray_angle = player.rotation_angle +
							atan((col - NUM_RAYS / 2) / PROJ_PLANE);
		cast_ray(ray_angle, col);
	}
}

/**
 * render_rays - draw all the rays
 *
 */

void render_rays(void)
{
	int i;

	for (i = 0; i < NUM_RAYS; i += 50)
	{
		draw_line(
			player.x * MINIMAP_SCALE_FACTOR,
			player.y * MINIMAP_SCALE_FACTOR,
			rays[i].wall_hitx * MINIMAP_SCALE_FACTOR,
			rays[i].wall_hity * MINIMAP_SCALE_FACTOR,
			0xFF0000FF
		);
	}
}