#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "AssetsManager.h"
#include "Menu.h"

class Game
{
public:
	Game();

	void run();

private:
	void update();
	void render();
	void processEvents();

	void initAssets();

	AssetsManager assetsManager;
	Menu menu;

	sf::RenderWindow gameWindow;

	sf::Text creator;
};

