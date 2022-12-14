#pragma once

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Map.h"
#include "AssetsManager.h"
#include "Airplane.h"
#include "Path.h"
#include <list>

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

	void CheckCollision(Airplane planeA, Airplane planeB);

	Menu menu;
	AssetsManager assetsManager;
	Map map;
	std::list<Airplane>airplanes;

	sf::RenderWindow gameWindow;
	sf::Clock airplanesSpawner;

	std::string playerName;
	std::string country;
	std::string position;

	sf::Text creator;

	unsigned long long planeIds;
};

