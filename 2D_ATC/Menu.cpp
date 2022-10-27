#include "Menu.h"
#include <iostream>

Menu::Menu()
{
	
}

Menu::Menu(AssetsManager assetsManager)
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

	continueGame.CheckMouseHover(mousePosition);


	return;
}

void Menu::render(sf::RenderTarget *window)
{
	window->draw(backgroundSprite);

	continueGame.render(window);

	return;
}

void Menu::HandleClick()
{
	if (continueGame.isButtonClicked(mousePosition))
	{
		drawMenu = false;

		buttonClickSound.play();
	}
	

	return;
}

void Menu::HandleInput(unsigned unicode)
{
	

	return;
}

void Menu::initSounds()
{
	buttonClickSound.setBuffer(assetsManager.GetSoundBuffer("buttonClick.wav"));

	return;
}

void Menu::initSprites()
{
	backgroundSprite.setTexture(assetsManager.GetTexture("menu.png"));

	return;
}

void Menu::initButtons()
{
	continueGame = Button(sf::Vector2f(300, 90), sf::Vector2f(600, 350));

	continueGame.SetDefaultColor(sf::Color(24, 25, 26, 255));
	continueGame.SetBorder(2, sf::Color::White);
	continueGame.SetText(&assetsManager.GetFont("Comfortaa-Regular.ttf"), "Continue career");
	continueGame.CenterText();


	return;
}

void Menu::initObjects()
{

	return;
}