#include "Career.h"

Career::Career()
{
	initSounds();
	initFonts();
	initButtons();

	draw = false;
}

void Career::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	cancelButton.CheckMouseHover(mousePosition);

	return;
}

void Career::render(sf::RenderTarget* window)
{
	cancelButton.render(window);

	return;
}

void Career::LoadCareer()
{

	return;
}

void Career::CreateCareer()
{

	return;
}

void Career::HandleClick()
{
	if (cancelButton.isButtonClicked(mousePosition))
	{
		buttonClickSound.play();
		draw = false;
	}

	return;
}

void Career::initSounds()
{
	buttonClickBuffer.loadFromFile("../Resources/sounds/buttonClick.wav");

	buttonClickSound.setBuffer(buttonClickBuffer);

	return;
}

void Career::initButtons()
{
	cancelButton.setSize(sf::Vector2f(300, 90));
	cancelButton.setPosition(sf::Vector2f(600, 750));
	cancelButton.setDefaultColor(sf::Color(24, 25, 26, 255));
	cancelButton.setBorderColor(sf::Color::White);
	cancelButton.setBorderThickness(2);
	cancelButton.setText(&comfortaa, "Cancel");
	cancelButton.setTextInMiddle();

	return;
}

void Career::initFonts()
{
	comfortaa.loadFromFile("../Resources/fonts/Comfortaa-Regular.ttf");

	return;
}
