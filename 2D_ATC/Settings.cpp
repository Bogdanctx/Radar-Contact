#include "Settings.h"

Settings::Settings()
{
	initSounds();
	initFonts();
	initButtons();

	draw = false;
}

void Settings::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	applyButton.CheckMouseHover(mousePosition);

	return;
}

void Settings::render(sf::RenderTarget* window)
{
	applyButton.render(window);

	return;
}

void Settings::HandleClick()
{
	if (applyButton.isButtonClicked(mousePosition))
	{
		buttonClickSound.play();
		draw = false;
	}

	return;
}

void Settings::initSounds()
{
	buttonClickBuffer.loadFromFile("../Resources/sounds/buttonClick.wav");

	buttonClickSound.setBuffer(buttonClickBuffer);

	return;
}

void Settings::initButtons()
{
	applyButton.setSize(sf::Vector2f(300, 90));
	applyButton.setPosition(sf::Vector2f(600, 750));
	applyButton.setDefaultColor(sf::Color(24, 25, 26, 255));
	applyButton.setBorderColor(sf::Color::White);
	applyButton.setBorderThickness(2);
	applyButton.setText(&comfortaa, "Apply");
	applyButton.setTextInMiddle();

	return;
}

void Settings::initFonts()
{
	comfortaa.loadFromFile("../Resources/fonts/Comfortaa-Regular.ttf");

	return;
}
