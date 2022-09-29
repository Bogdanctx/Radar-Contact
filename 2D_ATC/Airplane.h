#pragma once

#include <SFML/Graphics.hpp>
#include "AssetsManager.h"

class Airplane
{
public:
	Airplane();
	Airplane(AssetsManager* assetsManager);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

private:
	sf::RectangleShape airplane;
	sf::RectangleShape dataStick;
	sf::Vector2i mousePosition;
	sf::Clock updateTimer;

	sf::Vector2f velocity;
	unsigned short altitude, heading;
	unsigned short cadrans[4] = { 0, 1, 2, 3 };

	AssetsManager* assetsManager;
	sf::Text airplaneCallsign;
	sf::Text airplaneHeading;
	std::string s_callSign;
};

