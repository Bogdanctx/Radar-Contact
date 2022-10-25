#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Path
{
public:
	Path();

	void render(sf::RenderTarget* window);
	void update();

	void AddPoint(sf::Vector2f position);
	void DrawRoute();
	void HideRoute();

private:
	std::vector<sf::CircleShape>points;
};

