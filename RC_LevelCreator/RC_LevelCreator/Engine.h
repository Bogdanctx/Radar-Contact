#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "AssetsManager.h"
#include "Runway.h"

class Engine
{
public:
	Engine();

	void run();
	void load(std::string icao, std::string airportName);

private:

	void initAssets();

	void update();
	void render();
	void processEvents();

	sf::RenderWindow window;

	sf::Texture texture;
	sf::Sprite sprite;

	AssetsManager assetsManager;
	std::vector<Runway>runways;

	std::ofstream out;

};