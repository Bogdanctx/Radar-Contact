#pragma once

#include <SFML/Graphics.hpp>
#include <deque>

class Path
{
public:
	Path();

	void render(sf::RenderTarget* window);
	void update(sf::Vector2i mousePosition);
	void draw();

	sf::Vector2f NextPointPosition();
	
	void AddPoint(sf::Vector2f position);
	void HidePath();
	void RemoveFirstPoint();

	short PointHovered();
	void RemoveUntilPoint(short &pointId);

	int length();

private:
	struct Point {
		short id;
		sf::CircleShape shape;
		bool remove = false;
	};
	

	std::deque<Point>points;

	sf::Vector2i mousePosition;
};

