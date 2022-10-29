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

	void LoadMap(const int position);

	struct AirportData {
		bool connection[50][50];
		struct Nodes {
			int x, y;
			bool finalNode;
		} nodes[50];
		struct Spawns {
			int x, y;
		} spawns[50];
		struct Runways {
			bool direction; // 0 - left, 1 - right
			int heading; // runway heading
			int x, y; // position
		} runways[15];
		int numberOfRunways, numberOfNodes;
		short minAltitude, maxAltitude;

		void GenerateRoute(Path &path, int startingNode);
	};

	AirportData airportData;

private:
	sf::Sprite mapSprite;
	sf::Texture mapTexture;
	sf::Vector2i mousePosition;
};