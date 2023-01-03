#pragma once

#include <SFML/Graphics.hpp>

#include "AssetsManager.h"

class Runway
{
public:
	Runway();
	Runway(AssetsManager assetsManager, sf::Vector2f positionFactor, unsigned short rotation, float length);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget *window);
	void processEvents(sf::Event event);

	sf::RectangleShape runway;

private:
    AssetsManager assetsManager;

    sf::Vector2i mousePosition;
};

