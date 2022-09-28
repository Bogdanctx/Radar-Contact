#pragma once

#include <SFML/Graphics.hpp>
#include "AssetsManager.h"

class Map
{
public:
	Map();
	Map(AssetsManager* assetsManager);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void LoadMap(const std::string country, const std::string position);


private:
	AssetsManager* assetsManager;
	
	sf::Sprite mapSprite;
	sf::Vector2i mousePosition;
};