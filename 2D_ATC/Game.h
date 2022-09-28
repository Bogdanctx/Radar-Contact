#pragma once

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Map.h"
#include "AssetsManager.h"
#include "Airplane.h"

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

	Menu menu;
	AssetsManager assetsManager;
	Map map;
	std::vector<Airplane>airplanes;

	sf::RenderWindow gameWindow;
	sf::Clock airplaneSpawner;

	std::string playerName;
	std::string country;
	std::string position;
};

