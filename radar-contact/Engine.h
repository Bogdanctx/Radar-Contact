#pragma once

#include <fstream>

#include <SFML/Graphics.hpp>

#include "AssetsManager.h"
#include "Game.h"
#include "Menu.h"

#include "Runway.h"

#include <cstring>

class Engine
{
public:
	Engine();

	void run();

private:
	void update();
	void render();
	void processEvents();

	void createWindow();

	void initAssets();

	AssetsManager assetsManager;

	Game game;
	Menu menu;

	sf::RenderWindow window;

	sf::Text creator;
};
