#pragma once

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Map.h"

class Game
{
public:
	Game();

	void run();

private:
	Menu menu;
	Map map;

	sf::RenderWindow gameWindow;

	sf::Texture texture;
	sf::Sprite sprite;

	void update();
	void render();
	void processEvents();

	void initTextures();
	void initSprites();
};

