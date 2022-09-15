#include "Menu.h"

Menu::Menu()
{
	initSounds();
	initTextures();
	initSprites();
	initFonts();
	initButtons();
}

void Menu::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	continueCareer.CheckMouseHover(mousePosition);
	newCareer.CheckMouseHover(mousePosition);
	settingsButton.CheckMouseHover(mousePosition);

	if (settingsTab.draw == true)
	{
		settingsTab.update(mousePosition);
	}
	else if (career.drawLoadCareer || career.drawCreateCareer)
	{
		career.update(mousePosition);
	}

	return;
}

void Menu::render(sf::RenderTarget *window)
{
	window->draw(backgroundSprite);

	if (settingsTab.draw == true)
	{
		settingsTab.render(window);
	}
	else if (career.drawLoadCareer || career.drawCreateCareer)
	{
		career.render(window);
	}
	else
	{
		continueCareer.render(window);
		newCareer.render(window);
		settingsButton.render(window);
	}

	return;
}

void Menu::HandleClick()
{
	if (settingsTab.draw == true)
	{
		settingsTab.HandleClick();
	}
	else if (career.drawLoadCareer || career.drawCreateCareer)
	{
		career.HandleClick();
	}
	else
	{
		if (continueCareer.isButtonClicked(mousePosition))
		{
			career.LoadCareer();
			buttonClickSound.play();
			career.drawLoadCareer = true;
		}
		else if (newCareer.isButtonClicked(mousePosition))
		{
			career.CreateCareer();
			buttonClickSound.play();
			career.drawCreateCareer = true;
		}
		else if (settingsButton.isButtonClicked(mousePosition))
		{
			buttonClickSound.play();

			settingsTab.draw = true;
		}
	}
	

	return;
}

void Menu::HandleInput(unsigned unicode)
{
	if (career.drawCreateCareer)
	{
		career.HandleInput(unicode);
	}

	return;
}

void Menu::initSounds()
{
	buttonClickBuffer.loadFromFile("../Resources/sounds/buttonClick.wav");

	buttonClickSound.setBuffer(buttonClickBuffer);

	return;
}

void Menu::initTextures()
{
	backgroundTexture.loadFromFile("../Resources/images/menu/menu.png");

	return;
}

void Menu::initSprites()
{
	backgroundSprite.setTexture(backgroundTexture);

	return;
}

void Menu::initFonts()
{
	comfortaa.loadFromFile("../Resources/fonts/Comfortaa-Regular.ttf");

	return;
}

void Menu::initButtons()
{
	continueCareer.setSize(sf::Vector2f(300, 90));
	continueCareer.setPosition(sf::Vector2f(600, 350));
	continueCareer.setDefaultColor(sf::Color(24, 25, 26, 255));
	continueCareer.setBorderColor(sf::Color::White);
	continueCareer.setBorderThickness(2);
	continueCareer.setText(&comfortaa, "Continue career");
	continueCareer.setTextInMiddle();

	newCareer.setSize(sf::Vector2f(300, 90));
	newCareer.setPosition(sf::Vector2f(600, 480));
	newCareer.setDefaultColor(sf::Color(24, 25, 26, 255));
	newCareer.setBorderColor(sf::Color::White);
	newCareer.setBorderThickness(2);
	newCareer.setText(&comfortaa, "New career");
	newCareer.setTextInMiddle();

	settingsButton.setSize(sf::Vector2f(300, 90));
	settingsButton.setPosition(sf::Vector2f(600, 610));
	settingsButton.setDefaultColor(sf::Color(24, 25, 26, 255));
	settingsButton.setBorderColor(sf::Color::White);
	settingsButton.setBorderThickness(2);
	settingsButton.setText(&comfortaa, "Settings");
	settingsButton.setTextInMiddle();

	return;
}
