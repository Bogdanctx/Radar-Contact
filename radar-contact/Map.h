#pragma once

#include <SFML/Graphics.hpp>

#include "AssetsManager.h"

class Map
{
public:
	Map();
	Map(AssetsManager assetsManager);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void processEvents(sf::Event event);

	void load(const std::string icao);

private:
	sf::Texture texture;
	sf::Sprite map;

	sf::Vector2i mousePosition;

	AssetsManager assetsManager;
};

