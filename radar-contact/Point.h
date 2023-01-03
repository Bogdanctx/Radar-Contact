#pragma once

#include <SFML/Graphics.hpp>

#include "AssetsManager.h"

class Point
{
public:
	Point();
	Point(AssetsManager *assetsManager, const std::string name, sf::Vector2f positionFactor);

	void render(sf::RenderTarget* window);
	void update(sf::Vector2i mousePosition);

private:
	sf::Vector2i mousePosition;

	sf::Text pointText;
	AssetsManager *assetsManager;

	sf::CircleShape point = sf::CircleShape(5, 3);
};

