#include "Career.h"

Career::Career()
{
	initSounds();
	initFonts();
	initButtons();
	initInputs();

	draw = drawLoadCareer = drawCreateCareer = false;
}

void Career::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	if (drawCreateCareer)
	{
		playerName.update(mousePosition);
	}

	cancelButton.CheckMouseHover(mousePosition);

	return;
}

void Career::render(sf::RenderTarget* window)
{
	if (drawCreateCareer)
	{
		playerName.render(window);
	}

	cancelButton.render(window);

	return;
}

void Career::LoadCareer()
{
	drawLoadCareer = true;

	return;
}

void Career::CreateCareer()
{
	drawCreateCareer = true;

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

void Career::initInputs()
{
	playerName.setSize(sf::Vector2f(700, 50));
	playerName.setBackgroundColor(sf::Color(29, 30, 31));
	playerName.setPosition(sf::Vector2f(600, 300));
	playerName.setBorderColor(sf::Color::White);
	playerName.setBorderThickness(1);
	playerName.setInputDescription("YOUR NAME");
	playerName.setMaxChars(20);
	playerName.setCharactersSize(15);

	return;
}
