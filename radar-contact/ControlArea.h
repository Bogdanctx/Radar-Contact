#pragma once

#include <SFML/Graphics.hpp>
#include "AssetsManager.h"

class ControlArea
{
public:
	ControlArea();
	ControlArea(AssetsManager assetsManager);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void processEvents(sf::Event event);

private:
	void initShapes();

	AssetsManager assetsManager;
	sf::Vector2i mousePosition;

	sf::RectangleShape area;
};

