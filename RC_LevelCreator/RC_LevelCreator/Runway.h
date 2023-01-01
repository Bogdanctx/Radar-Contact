#pragma once

#include <SFML/Graphics.hpp>

#include "AssetsManager.h"

class Runway
{
public:
	Runway();
	Runway(AssetsManager *assetsManager);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);
	void processEvent(sf::Event event);

	void setPosition(sf::Vector2f position);
	void setRotation(int rotation);

	bool isSelected = true;

	sf::Vector2f factor;
	int heading;

private:
	AssetsManager *assetsManager;
	sf::Vector2i mousePosition;

	sf::RectangleShape runway;
	sf::Text heading_text;
};

