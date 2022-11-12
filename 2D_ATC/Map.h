#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include "Path.h"

class Map
{
public:
	Map();

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void LoadMap(const unsigned short position);

	struct AirportData {
		struct Nodes {
			unsigned short x, y;
		} nodes[15];

		struct Runways {
			unsigned short heading; // runway heading
			unsigned short x, y; // position
		} runways[15];

		unsigned short numberOfRunways, numberOfNodes;
		unsigned short minAltitude, maxAltitude;
		sf::Vector2i airportsBoundsTopLeft, airportBoundsBottomRight;

		std::vector<std::vector<short>>map;

		void GenerateRoute(Path &path, sf::Vector2f pointA, sf::Vector2f pointB);
	};

	AirportData airportData;

private:
	sf::Sprite mapSprite;
	sf::Texture mapTexture;
	sf::Vector2i mousePosition;
};