#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>

class Path
{
public:
	Path();

	void render(sf::RenderTarget* window);
	void update();
	void draw();

	sf::Vector2f GetPointPosition(int point);
	
	void AddPoint(sf::Vector2f position, int index);
	void HidePath();

	int length();

private:
	std::vector<sf::CircleShape>points;
	std::vector<int>pointsIndex;
};

