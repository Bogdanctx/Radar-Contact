#include "Input.h"

Input::Input()
{
	initFonts();
	initTexts();
}

void Input::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	return;
}

void Input::render(sf::RenderTarget *window)
{
	window->draw(inputBody);
	window->draw(inputDescription);

	return;
}

void Input::setPosition(sf::Vector2f position)
{
	inputBody.setPosition(position);

	sf::Vector2f inputBodySize = inputBody.getSize();
	inputDescription.setPosition(sf::Vector2f(position.x-inputBodySize.x/2, position.y - inputBodySize.y));

	return;
}

void Input::setSize(sf::Vector2f size)
{
	inputBody.setSize(size);

	sf::FloatRect inputBounds = inputBody.getGlobalBounds();
	inputBody.setOrigin(sf::Vector2f(inputBounds.left + inputBounds.width / 2, inputBounds.top + inputBounds.height / 2));

	return;
}

void Input::setBackgroundColor(sf::Color color)
{
	inputBody.setFillColor(color);

	return;
}

void Input::setBorderColor(sf::Color color)
{
	inputBody.setOutlineColor(color);

	return;
}

void Input::setBorderThickness(float thickness)
{
	inputBody.setOutlineThickness(thickness);

	return;
}

void Input::setMaxChars(unsigned max)
{
	maxChars = max;

	return;
}

void Input::setCharactersSize(unsigned size)
{
	inputDescription.setCharacterSize(size);

	return;
}

void Input::setInputDescription(std::string text)
{
	inputDescription.setString(text);
	inputDescription.setFont(merriweather);

	return;
}

void Input::initFonts()
{
	merriweather.loadFromFile("../Resources/fonts/MerriweatherSans-Regular.ttf");

	return;
}

void Input::initTexts()
{
	

	return;
}