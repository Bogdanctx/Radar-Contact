#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "AssetsManager.h"
#include "Map.h"
#include "ControlArea.h"
#include "Airplane.h"

class Game
{
public:
	Game();
	Game(AssetsManager assetsManager);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void processEvents(sf::Event event);

	void initObjects();

	bool isActive;

	Map map;

private:
    void CreateAirplane();

	sf::Vector2i mousePosition;
	sf::Clock t_airplaneSpawn;

	AssetsManager assetsManager;
	ControlArea controlArea;

    std::vector<Airplane> airplanes;
};

