#include "Path.h"

Path::Path()
{

}

void Path::update()
{
	
}

sf::Vector2f Path::GetPointPosition(unsigned short point)
{
	if (point == points.size())
		return sf::Vector2f(0, 0);
	return points[point].getPosition();
}

void Path::render(sf::RenderTarget* window)
{
	for (auto it : points)
	{
		window->draw(it);
	}

	return;
}

void Path::AddPoint(sf::Vector2f position, unsigned short index)
{
	sf::CircleShape point;

	point.setPosition(position);
	point.setRadius(5);
	point.setFillColor(sf::Color(255, 255, 255, 30));

	points.push_back(point);
	pointsIndex.push_back(index);

	return;
}

void Path::draw()
{
	for (auto &it : points)
	{
		it.setFillColor(sf::Color(255, 255, 255, 255));
	}

	return;
}

void Path::HidePath()
{
	for (auto &it : points)
	{
		it.setFillColor(sf::Color(255, 255, 255, 30));
	}

	return;
}

int Path::length()
{
	return points.size();
}
