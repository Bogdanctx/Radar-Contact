#include "Path.h"
#include "Math.h"

Path::Path()
{

}

void Path::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;
	
	return;
}

sf::Vector2f Path::NextPointPosition()
{
	return points.front().shape.getPosition();
}

void Path::render(sf::RenderTarget* window)
{
	for (auto it : points)
	{
		window->draw(it.shape);
	}

	return;
}

void Path::AddPoint(sf::Vector2f position)
{
	Point point;

	point.shape.setPosition(position);
	point.shape.setRadius(5);
	point.shape.setFillColor(sf::Color(255, 255, 255, 30));
	point.id = points.size();

	points.push_front(point);

	return;
}

void Path::draw()
{
	for (auto &it : points)
	{
		it.shape.setFillColor(sf::Color(255, 255, 255, 255));
	}

	return;
}

void Path::HidePath()
{
	for (auto &it : points)
	{
		it.shape.setFillColor(sf::Color(255, 255, 255, 30));
	}

	return;
}

void Path::RemoveFirstPoint()
{
	points.pop_front();

	return;
}

short Path::PointHovered()
{
	for (auto it : points)
	{
		if (it.shape.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
		{
			return it.id;
		}
	}
	return -1;
}

void Path::RemoveUntilPoint(short& pointId)
{
	if (pointId == -1)
		return;

	while (points.front().id != pointId)
	{
		points.pop_front();
	}

	pointId = -1;
}

int Path::length()
{
	return points.size();
}
