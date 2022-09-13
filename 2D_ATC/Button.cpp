#include "Button.h"

Button::Button()
{

}

void Button::update()
{

}

void Button::render(sf::RenderTarget* window)
{
	window->draw(buttonBody);
	window->draw(buttonText);

	return;
}

void Button::setSize(sf::Vector2f size)
{
	buttonBody.setSize(size);

	sf::FloatRect buttonBounds = buttonBody.getGlobalBounds();
	buttonBody.setOrigin(sf::Vector2f(buttonBounds.left + buttonBounds.width / 2, buttonBounds.top + buttonBounds.height / 2));

	return;
}

void Button::setText(sf::Font *font, sf::String string)
{
	buttonText.setFont(*font);
	buttonText.setString(string);


	return;
}

void Button::setTextInMiddle()
{
	sf::FloatRect textBounds = buttonText.getGlobalBounds();
	sf::Vector2f buttonPosition = buttonBody.getPosition();

	float originX = textBounds.left + textBounds.width / 2,
		originY = textBounds.top + textBounds.height / 2;

	buttonText.setOrigin(sf::Vector2f(originX, originY));

	buttonText.setPosition(buttonPosition);
	
	return;
}

void Button::setPosition(sf::Vector2f position)
{
	buttonBody.setPosition(position);

	return;
}

void Button::setDefaultColor(sf::Color color)
{
	defaultColor = color;

	hoverColor.r = defaultColor.r + 20;
	hoverColor.g = defaultColor.g + 20;
	hoverColor.b = defaultColor.b + 20;

	buttonBody.setFillColor(color);

	return;
}

void Button::setBackgroundColor(sf::Color color)
{
	buttonBody.setFillColor(color);

	return;
}

void Button::setBorderColor(sf::Color color)
{
	buttonBody.setOutlineColor(color);

	return;
}

void Button::setBorderThickness(float thickness)
{
	buttonBody.setOutlineThickness(thickness);

	return;
}

void Button::CheckMouseHover(sf::Vector2i mousePosition)
{
	if (buttonBody.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
	{
		setBackgroundColor(hoverColor);
	}
	else
	{
		setBackgroundColor(defaultColor);
	}

	return;
}

bool Button::isButtonClicked(sf::Vector2i mousePosition)
{
	if (buttonBody.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
	{
		return true;	
	}

	return false;
}
