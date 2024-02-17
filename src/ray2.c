#include "../headers/header.h"

/**
 * distance_points - Finds horizontal intersection with the wall
 * @x1: x coordinate of the starting point
 * @y1: y coordinate oh the starting point
 * @x2: x coordinate of the end point
 * @y2: y coordinate of the end point
 * Return: the distance between two points
 */

float distance_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}

/**
 * rayfacing_down - check if the ray is facing down
 * @angle: current ray angle
 * Return: true or false
 */

bool rayfacing_down(float angle)
{
	return (angle > 0 && angle < PI);
}

/**
 * rayfacing_up - check if the ray is facing up
 * @angle: current ray angle
 * Return: true or false
 */

bool rayfacing_up(float angle)
{
	return (!rayfacing_down(angle));
}

/**
 * rayfacing_right - check if the ray is facing to the right
 * @angle: current ray angle
 * Return: true or false
 */

bool rayfacing_right(float angle)
{
	return (angle < 0.5 * PI || angle > 1.5 * PI);
}

/**
 * rayfacing_left - check if the ray is facing to the right
 * @angle: current ray angle
 * Return: true or false
 */

bool rayfacing_left(float angle)
{
	return (!rayfacing_right(angle));
}