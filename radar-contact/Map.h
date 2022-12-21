#pragma once

#include <SFML/Graphics.hpp>

class Map
{
public:
	Map();

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void processEvents(sf::Event event);

	void load(const std::string icao);

private:
	sf::Texture texture;
	sf::Sprite map;

	sf::Vector2i mousePosition;
};

