#include "Slider.h"

Slider::Slider()
{

}

void Slider::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		short distFromOrigin = Math::DistanceToPoint(line.getPosition(), sf::Vector2f(mousePosition.x, mousePosition.y));

		if(circle.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)) &&
            line.getPosition().x <= mousePosition.x && mousePosition.x <= line.getPosition().x+line.getSize().x)
		{
			circle.setPosition(mousePosition.x, circle.getPosition().y);
			sliderValue = distFromOrigin / (line.getSize().x  / (max-min+1));
			sliderValue += min;
			value.setString(std::to_string(sliderValue));
		}
	}
}

void Slider::render(sf::RenderTarget* window)
{
	window->draw(line);
	window->draw(circle);
	window->draw(name);
	window->draw(value);
}

void Slider::setPosition(sf::Vector2f position)
{
	line.setPosition(position);
	circle.setPosition(position);

	name.setPosition(position.x-circle.getRadius(), position.y - 4 * circle.getRadius());
	value.setPosition(line.getGlobalBounds().left + line.getGlobalBounds().width, name.getPosition().y);
}

void Slider::setSize(int length, float radius)
{
	line.setSize(sf::Vector2f(length, 3));

	circle.setRadius(radius);
	circle.setOrigin(sf::Vector2f(radius, radius));

	sliderLength = length;
}

void Slider::setLineColor(sf::Color color)
{
	line.setFillColor(color);
}

void Slider::setName(const std::string name, unsigned short size)
{
	this->name.setString(name);
	this->name.setCharacterSize(size);

	value.setCharacterSize(size);
}

void Slider::setFont(sf::Font* font)
{
	name.setFont(*font);
	value.setFont(*font);
}

void Slider::setBounds(int min, int max)
{
	this->max = max;
	this->min = min;

	sliderValue = min;
}

void Slider::processEvents(sf::Event event)
{
	switch (event.type)
	{
        default:
            break;
	}
}
