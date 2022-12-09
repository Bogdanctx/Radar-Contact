#pragma once

#include <vector>

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

private:
	void initObjects();

	AssetsManager assetsManager; 

	std::vector<Button>airportsList;

	sf::Vector2i mousePosition;
};

