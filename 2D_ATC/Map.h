#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <queue>

#include "Path.h"
#include "AssetsManager.h"

class Map
{
public:
	Map();
	Map(AssetsManager assetsManager);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void LoadMap(const unsigned short position);

	struct MapData {
		struct Runways {
			unsigned short heading; // runway heading
			unsigned short x, y; // position

			sf::Vector2f coordsTowardsRunway;

		};
		struct AirportPin {
			AirportPin();
			void StylePin();

			AssetsManager *assetsManager;

			sf::Vector2f position;
			std::string icao;
			sf::Text icaoText;
			sf::CircleShape pin;
		};

		std::vector<AirportPin>airportsPin;
		std::vector<Runways>runways;

		unsigned short numberOfRunways, numberOfNodes, numberOfAirports;
		unsigned short minAltitude, maxAltitude;
		sf::Vector2i airportsBoundsTopLeft, airportBoundsBottomRight;

		std::vector<std::vector<unsigned short>>map;
		void GenerateRoute(Path& path, sf::Vector2f pointA, sf::Vector2f pointB);
	};

	MapData mapData;

private:

	AssetsManager assetsManager;

	sf::Sprite mapSprite;
	sf::Texture mapTexture;
	sf::Vector2i mousePosition;

	unsigned short gamemode;
};