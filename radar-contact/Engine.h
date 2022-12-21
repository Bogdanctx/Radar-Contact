#pragma once

#include <SFML/Graphics.hpp>

#include "AssetsManager.h"
#include "Game.h"
#include "Menu.h"

class Engine
{
public:
	Engine();

	void run();

private:
	void update();
	void render();
	void processEvents();

	void initAssets();

	AssetsManager assetsManager;
	
	Game game;
	Menu menu;

	sf::RenderWindow window;

	sf::Text creator;
};

