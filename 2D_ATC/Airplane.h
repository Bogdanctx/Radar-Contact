#pragma once

#include <SFML/Graphics.hpp>

class Airplane
{
public:
	Airplane();

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

private:
	sf::RectangleShape airplane;
	sf::Vector2i mousePosition;
	sf::Clock updateTimer;

	sf::Vector2f velocity;
	unsigned short altitude;
};

