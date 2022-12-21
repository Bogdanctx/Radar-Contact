#pragma once

#include <SFML/Graphics.hpp>

#include "AssetsManager.h"
#include "Map.h"

class Game
{
public:
	Game();
	Game(AssetsManager assetsManager);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void processEvents(sf::Event event);

	bool isActive;

	Map map;

private:
	sf::Vector2i mousePosition;

	AssetsManager assetsManager;
};

