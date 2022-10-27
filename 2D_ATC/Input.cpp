#include "Input.h"

Input::Input()
{

}

Input::Input(AssetsManager assetsManager, sf::Vector2f size, sf::Vector2f position)
{
	this->assetsManager = assetsManager;

	inputBody.setSize(size);

	sf::FloatRect inputBounds = inputBody.getGlobalBounds();
	sf::Vector2f newOrigin(
		inputBounds.left + inputBounds.width / 2,
		inputBounds.top + inputBounds.height / 2
	);

	inputBody.setOrigin(newOrigin);
	inputBody.setPosition(position);

	inputDescription.setPosition(sf::Vector2f(
		position.x - size.x / 2,
		position.y - size.y
	));
	inputDataText.setPosition(sf::Vector2f(
		position.x - size.x / 2 + 10,
		position.y - size.y / 2 + 10
	));

	inputDescription.setFont(assetsManager.GetFont("MerriweatherSans-Regular.ttf"));
	inputDataText.setFont(assetsManager.GetFont("MerriweatherSans-Regular.ttf"));
}

void Input::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;
}

void Input::render(sf::RenderTarget* window)
{
	window->draw(inputBody);
	window->draw(inputDescription);
	window->draw(inputDataText);

	return;
}

void Input::HandleInput(unsigned unicode)
{
	if (unicode >= 32 && unicode <= 126)
	{
		if (inputDataString.length() <= maxLength)
		{
			inputDataString += unicode;
		}

		inputDataText.setString(inputDataString);
	}
	else
	{
		if (unicode == 8 && inputDataString.length() > 0) // Backspace
		{
			inputDataString.pop_back();
			inputDataText.setString(inputDataString);
		}
	}

	return;
}

void Input::SetBorder(float thickness, sf::Color color)
{
	inputBody.setOutlineThickness(thickness);
	inputBody.setOutlineColor(color);

	return;
}

void Input::SetDescription(const std::string text)
{
	inputDescription.setString(text);

	sf::FloatRect descriptionBounds = inputDescription.getGlobalBounds();
	
	inputDescription.setPosition(sf::Vector2f(
		descriptionBounds.left,
		descriptionBounds.top - descriptionBounds.height
	));

	return;
}

void Input::SetMaxLength(const unsigned short max)
{
	maxLength = max;

	return;
}

void Input::SetCharsSize(const unsigned short size)
{
	inputDataText.setCharacterSize(size);

	return;
}

void Input::SetBackgroundColor(sf::Color color)
{
	inputBody.setFillColor(color);

	return;
}

std::string Input::GetInput()
{
	return inputDataString;
}
