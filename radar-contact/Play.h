#pragma once

#include <vector>
#include <cstring>
#include <filesystem>
#include <fstream>

#include "SFML/Graphics.hpp"
#include "AssetsManager.h"

#include "Button.h"

class Play
{
public:
	Play();
	Play(AssetsManager assetsManager);

	void processEvents(sf::Event event);
	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	bool isActive;

	struct Handler {
        bool airportSelected = true;
        std::string airportIcao = "EHAM";
	};

	Handler handler;

private:
	void initObjects();

	AssetsManager assetsManager;

	struct Airport {
        Button button;
        std::string airportName;
	};

	std::vector<Airport> airportsList;

	sf::Vector2i mousePosition;
};

