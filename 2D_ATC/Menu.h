#pragma once

#include <SFML/Graphics.hpp>

class Menu
{
public:
	Menu();

	void update();
	void render(sf::RenderTarget* window);

	bool drawMenu = true;

private:
	void initTextures();
	void initSprites();
	void initFonts();
	void initText();

	sf::Font comfortaa;
	sf::Text menuTitle;
};

