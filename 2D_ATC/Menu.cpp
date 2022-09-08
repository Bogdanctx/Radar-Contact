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
	window->draw(menuTitle);

	return;
}

void Menu::initTextures()
{

	return;
}

void Menu::initSprites()
{

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