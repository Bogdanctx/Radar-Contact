#include "Menu.h"

Menu::Menu()
{
	initTextures();
	initSprites();
	initFonts();
	initText();
}

void Menu::update()
{


	return;
}

void Menu::render(sf::RenderTarget *window)
{
	window->draw(menuCardSprite);

	return;
}

void Menu::initTextures()
{
	menuCardTexture.loadFromFile("../Resources/images/menu/menu1.png");

	return;
}

void Menu::initSprites()
{
	menuCardSprite.setTexture(menuCardTexture);

	return;
}

void Menu::initFonts()
{
	comfortaa.loadFromFile("../Resources/fonts/Comfortaa-Regular.ttf");

	return;
}

void Menu::initText()
{
	menuTitle.setFont(comfortaa);

	return;
}