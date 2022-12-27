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

	std::pair<bool, std::string>handler;

private:
	void initObjects();

<<<<<<< Updated upstream
	AssetsManager assetsManager; 
=======
	AssetsManager assetsManager;
>>>>>>> Stashed changes

	std::vector<std::pair<Button, std::string>> airportsList;

	sf::Vector2i mousePosition;
};

