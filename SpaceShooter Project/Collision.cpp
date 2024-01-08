#include "Collision.h"

bool Collision::CircleCollision(float c1X, float c1Y, float r1, float c2X, float c2Y, float r2)
{
	//Calculate deltas (deltaX and deltaY)
	float dx = c2X - c1X;
	float dy = c2Y - c1Y;

	//Calculate Distance
	float distance = sqrt((dx * dx) + (dy * dy));

	//if distance between circles s less than the sum of radii -> overlap detected
	if (distance <= r1 + r2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
