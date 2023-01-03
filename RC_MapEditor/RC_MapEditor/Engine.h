#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include <vector>

#include "AssetsManager.h"


class Engine
{
public:
	Engine();

	void run();
	void load(const std::string icao, const std::string airportName);
	
private:
	void update();
	void processEvents();
	void render();

	sf::RenderWindow window;

	sf::Sprite sprite;
	sf::Texture texture;

	AssetsManager assetsManager;

	sf::Event event;

	std::string icao;
	std::string airportName;

	struct Point {
		public:
			Point();
			Point(float x, float y, const std::string name);
			sf::CircleShape point = sf::CircleShape(5, 3);
			std::string name;
			float x, y;

			void setPosition(float x, float y);
	};

	bool pointActive;

	std::vector<Point>points;
};

