#include "Button.h"

Button::Button()
{

}

Button::Button(sf::Vector2f size, sf::Vector2f position)
{
	buttonBody.setSize(size);

	// Putting origin in middle
	/*sf::FloatRect buttonBounds = buttonBody.getGlobalBounds();
	sf::Vector2f newOrigin(buttonBounds.left + buttonBounds.width / 2,
		buttonBounds.top + buttonBounds.height / 2);
	buttonBody.setOrigin(newOrigin);
	*/
	buttonBody.setPosition(position);

	return;
}

void Button::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	checkMouseHover();
}

void Button::render(sf::RenderTarget* window)
{
	window->draw(buttonBody);
	window->draw(buttonText);

	return;
}

void Button::setText(sf::Font* font, sf::String string)
{
	buttonText.setFont(*font);
	buttonText.setString(string);

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

void Button::setHoverColor(sf::Color color)
{
	hoverColor = color;
}

void Button::setBorder(float thickness, sf::Color color)
{
	buttonBody.setOutlineThickness(thickness);
	buttonBody.setOutlineColor(color);
}

void Button::checkMouseHover()
{
	if (buttonBody.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
	{
		buttonBody.setFillColor(hoverColor);
	}
	else
	{
		buttonBody.setFillColor(defaultColor);
	}

	return;
}

bool Button::isButtonClicked(sf::Vector2i mousePosition)
{
	return buttonBody.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y));
}

void Button::centerText()
{
	sf::FloatRect bounds = buttonText.getGlobalBounds();
	sf::Vector2f newOrigin(bounds.left + bounds.width / 2,
		bounds.top + bounds.height / 2);
	
	bounds = buttonBody.getGlobalBounds();

	buttonText.setOrigin(newOrigin);
	buttonText.setPosition(sf::Vector2f(
		bounds.left + bounds.width / 2, bounds.top + bounds.height / 2
	));
	

	return;
}

void Button::setCharSize(unsigned short size)
{
	buttonText.setCharacterSize(size);
}
