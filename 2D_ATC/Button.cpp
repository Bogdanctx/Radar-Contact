#include "Button.h"

Button::Button()
{

}

Button::Button(sf::Vector2f size, sf::Vector2f position)
{
	buttonBody.setSize(size);

	// Putting origin in middle
	sf::FloatRect buttonBounds = buttonBody.getGlobalBounds();
	sf::Vector2f newOrigin(buttonBounds.left + buttonBounds.width / 2,
						buttonBounds.top + buttonBounds.height / 2);
	buttonBody.setOrigin(newOrigin);

	buttonBody.setPosition(position);

	return;
}

Button::~Button()
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

void Button::SetText(sf::Font *font, sf::String string)
{
	buttonText.setFont(*font);
	buttonText.setString(string);
	
	return;
}


void Button::SetDefaultColor(sf::Color color)
{
	defaultColor = color;

	hoverColor.r = defaultColor.r + 20;
	hoverColor.g = defaultColor.g + 20;
	hoverColor.b = defaultColor.b + 20;

	buttonBody.setFillColor(color);

	return;
}

void Button::SetBorder(float thickness, sf::Color color)
{
	buttonBody.setOutlineThickness(thickness);
	buttonBody.setOutlineColor(color);
}

void Button::CheckMouseHover(sf::Vector2i mousePosition)
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
	if (buttonBody.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
	{
		return true;	
	}

	return false;
}

void Button::CenterText()
{


	return;
}