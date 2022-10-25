#include "Path.h"

Path::Path()
{

}

void Path::update()
{

}

void Path::render(sf::RenderTarget* window)
{
	for (auto& it : points)
	{
		window->draw(it);
	}

	return;
}

void Path::AddPoint(sf::Vector2f position)
{
	sf::CircleShape point;

	point.setPosition(position);
	point.setRadius(5);
	point.setFillColor(sf::Color(255, 255, 255, 100));

	points.push_back(point);

	return;
}

void Path::DrawRoute()
{
	for (auto &it : points)
	{
		it.setFillColor(sf::Color(255, 255, 255, 255));
	}

	return;
}

void Path::HideRoute()
{
	for (auto &it : points)
	{
		it.setFillColor(sf::Color(255, 255, 255, 100));
	}

	return;
}