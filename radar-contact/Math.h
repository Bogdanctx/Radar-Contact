#pragma once
#include <SFML/System/Vector2.hpp>

class Math
{
public:
	Math();

	static double DistanceToPoint(sf::Vector2f pointA, sf::Vector2f pointB);
	static double DirectionToPoint(sf::Vector2f pointA, sf::Vector2f pointB);
};