#include "Menu.h"
#include <iostream>

Menu::Menu()
{
	
}

Menu::Menu(AssetsManager* assetsManager)
{
	this->assetsManager = assetsManager;

	initSounds();
	initSprites();
	initButtons();
	initObjects();
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
	else if (career.drawCreateCareer)
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
	else if (career.drawCreateCareer)
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
	else if (career.drawCreateCareer)
	{
		career.HandleClick();
	}
	else
	{
		if (continueCareer.isButtonClicked(mousePosition))
		{
			career.LoadCareer();
			buttonClickSound.play();
		}
		else if (newCareer.isButtonClicked(mousePosition))
		{
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
	buttonClickSound.setBuffer(assetsManager->GetSoundBuffer("buttonClick.wav"));

	return;
}

void Menu::initSprites()
{
	backgroundSprite.setTexture(assetsManager->GetTexture("menu.png"));

	return;
}

void Menu::initButtons()
{
	continueCareer = Button(sf::Vector2f(300, 90), sf::Vector2f(600, 350));
	newCareer = Button(sf::Vector2f(300, 90), sf::Vector2f(600, 480));
	settingsButton = Button(sf::Vector2f(300, 90), sf::Vector2f(600, 610));


	continueCareer.SetDefaultColor(sf::Color(24, 25, 26, 255));
	continueCareer.SetBorder(2, sf::Color::White);
	continueCareer.SetText(&assetsManager->GetFont("Comfortaa-Regular.ttf"), "Continue career");
	continueCareer.CenterText();
	
	newCareer.SetDefaultColor(sf::Color(24, 25, 26, 255));
	newCareer.SetBorder(2, sf::Color::White);
	newCareer.SetText(&assetsManager->GetFont("Comfortaa-Regular.ttf"), "New career");
	newCareer.CenterText();

	
	settingsButton.SetDefaultColor(sf::Color(24, 25, 26, 255));
	settingsButton.SetBorder(2, sf::Color::White);
	settingsButton.SetText(&assetsManager->GetFont("Comfortaa-Regular.ttf"), "Settings");
	settingsButton.CenterText();

	return;
}

void Menu::initObjects()
{
	settingsTab = Settings(assetsManager);
	career = Career(assetsManager);

	return;
}