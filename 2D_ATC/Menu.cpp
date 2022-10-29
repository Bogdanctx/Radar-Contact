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

	draw = true;
}

void Menu::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	if (continueGame.draw)
	{
		continueGame.update(mousePosition);
	}
	else if (newGame.draw)
	{
		newGame.update(mousePosition);
	}
	else
	{
		b_continueGame.CheckMouseHover(mousePosition);
		b_newGame.CheckMouseHover(mousePosition);
	}

	return;
}

void Menu::render(sf::RenderTarget *window)
{
	window->draw(backgroundSprite);

	if (continueGame.draw)
	{
		continueGame.render(window);
	}
	else if (newGame.draw)
	{
		newGame.render(window);
	}
	else
	{
		b_continueGame.render(window);
		b_newGame.render(window);
	}

	return;
}

void Menu::HandleClick()
{
	if (continueGame.draw)
	{
		continueGame.HandleClick();

		if (continueGame.option == 1 || continueGame.option == 2)
		{
			draw = false;
		}
	}
	else if (newGame.draw)
	{
		newGame.HandleClick();

		if (newGame.applyGame == true)
		{
			continueGame.draw = 1;
			newGame.draw = newGame.applyGame = false;
		}
	}

	if (b_continueGame.isButtonClicked(mousePosition))
	{
		continueGame.draw = true;

		buttonClickSound.play();
	}
	else if (b_newGame.isButtonClicked(mousePosition))
	{
		newGame.draw = true;

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
	b_continueGame = Button(sf::Vector2f(300, 90), sf::Vector2f(600, 350));
	b_newGame = Button(sf::Vector2f(300, 90), sf::Vector2f(600, 500));

	b_continueGame.SetDefaultColor(sf::Color(24, 25, 26, 255));
	b_continueGame.SetBorder(2, sf::Color::White);
	b_continueGame.SetText(&assetsManager.GetFont("Comfortaa-Regular.ttf"), "Continue game");
	b_continueGame.CenterText();

	b_newGame.SetDefaultColor(sf::Color(24, 25, 26, 255));
	b_newGame.SetBorder(2, sf::Color::White);
	b_newGame.SetText(&assetsManager.GetFont("Comfortaa-Regular.ttf"), "New game");
	b_newGame.CenterText();

	return;
}

void Menu::initObjects()
{
	continueGame = ContinueGame(assetsManager);
	newGame = NewGame(assetsManager);

	return;
}