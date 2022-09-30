#pragma once

#include <SFML/Graphics.hpp>
#include "AssetsManager.h"
#include <fstream>

class Map
{
public:
	Map();
	Map(AssetsManager* assetsManager);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void LoadMap(const std::string country, const std::string position);

	struct AirportData {
		struct Cadrans {
			int x1, x2;
			int y1, y2;
		} cadran[4];
		struct Runways {
			bool direction; // 0 - left, 1 - right
			int heading; // runway heading
			int x, y; // position
		} runways[15];
		int numberOfRunways;
	};

	AirportData airportData;

private:
	AssetsManager* assetsManager;
	
	std::ifstream read;

	sf::Sprite mapSprite;
	sf::Vector2i mousePosition;
};