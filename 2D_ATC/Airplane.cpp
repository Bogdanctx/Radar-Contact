#include "Airplane.h"

Airplane::Airplane()
{
	velocity.x = velocity.y = 1.5f;

	airplane.setSize(sf::Vector2f(10, 10));
	airplane.setFillColor(sf::Color::Transparent);
	airplane.setOutlineColor(sf::Color::White);
	airplane.setOutlineThickness(3);

	airplane.setPosition(sf::Vector2f(
		rand() % 900,
		rand() % 900
	));
}

void Airplane::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	if (updateTimer.getElapsedTime().asMilliseconds() >= 700)
	{
		airplane.move(velocity);

		updateTimer.restart();

	}

	return;
}

void Airplane::render(sf::RenderTarget* window)
{
	window->draw(airplane);

	return;
}

