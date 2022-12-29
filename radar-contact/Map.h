#pragma once

#include <fstream>

#include <SFML/Graphics.hpp>

#include "AssetsManager.h"
#include "Runway.h"

class Map
{
public:
	Map();
	Map(AssetsManager assetsManager);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void processEvents(sf::Event event);

	void load(const std::string icao);

	std::vector<Runway> runways;

private:
	sf::Texture texture;
	sf::Sprite map;

	sf::Vector2i mousePosition;

	AssetsManager assetsManager;

	std::string airportIcao, airportName;
    unsigned short airportRunways;
};
