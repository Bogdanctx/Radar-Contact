#pragma once

#include <SFML/Graphics.hpp>
#include "AssetsManager.h"
#include "Map.h"

class Airplane
{
public:
	Airplane();
	Airplane(AssetsManager* assetsManager, Map *map);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);
	void HandleClick();

private:
	sf::RectangleShape airplane;
	sf::RectangleShape dataStick;
	sf::RectangleShape directionShape;
	sf::Vector2i mousePosition;
	sf::Clock updateTimer;

	sf::Vector2f velocity;
	unsigned short altitude;
	short heading;
	unsigned short cadrans[4] = { 0, 1, 2, 3 };
	bool airplaneSelected;

	AssetsManager* assetsManager;
	Map* map;

	sf::Text airplaneCallsign;
	sf::Text airplaneHeading;
	std::string s_callSign;
};

