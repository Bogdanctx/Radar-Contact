#include "Math.h"
#include <cmath>

#define PI 3.14159265

double Math::DistanceToPoint(sf::Vector2f pointA, sf::Vector2f pointB)
{
	double distance = sqrt(pow(pointB.x - pointA.x, 2) + pow(pointB.y - pointA.y, 2));

	return distance;
}

double Math::DirectionToPoint(sf::Vector2f pointA, sf::Vector2f pointB)
{
	double d = atan2(pointA.y - pointB.y, pointA.x - pointB.x);
	d *= 180 / PI;
	d -= 90;
	if (d < 0)
		d += 360;

	return d;
}