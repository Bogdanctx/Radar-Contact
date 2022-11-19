#include "Path.h"
#include "Math.h"

Path::Path()
{
	directLine.first.setFillColor(sf::Color::Green);
	directToPoint = -1;
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

	if (directLine.second)
		window->draw(directLine.first);

	return;
}

void Path::AddPoint(sf::Vector2f position)
{
	Point point;

	point.shape.setPosition(position);
	point.shape.setRadius(5);
	point.shape.setFillColor(sf::Color(255, 255, 255, 30));
	point.id = points.size();

	points.push_back(point);

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

void Path::CalculateDirectToPoint(sf::Vector2f linePos)
{
	directLine.second = 1;

	directLine.first.setSize(sf::Vector2f(1.8, Math::DistanceToPoint(
		directLine.first.getPosition(), sf::Vector2f(mousePosition.x, mousePosition.y)
	)));
	directLine.first.setRotation(Math::DirectionToPoint(
		sf::Vector2f(mousePosition.x, mousePosition.y),
		directLine.first.getPosition()
	));
	directLine.first.setPosition(linePos);

	for (auto it : points)
	{
		if (it.shape.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
		{
			if (it.id != points.front().id)
			{
				directToPoint = it.id;
			}

		}
	}

	return;
}

void Path::PerformDirectToPoint()
{
	if (directToPoint != -1)
	{
		points.erase(points.begin(), points.begin() + directToPoint - points.begin()->id);
	}
	directLine.second = false;
	directToPoint = -1;

	return;
}

int Path::length()
{
	return points.size();
}
