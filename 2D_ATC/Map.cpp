#include "Map.h"

Map::Map()
{

}

Map::Map(AssetsManager* assetsManager)
{
	this->assetsManager = assetsManager;
}

void Map::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	return;
}

void Map::render(sf::RenderTarget* window)
{
	window->draw(mapSprite);

	return;
}
#include <iostream>
void Map::LoadMap(const std::string country, const std::string position)
{
	if (position == "ground")
	{
		mapSprite.setTexture(assetsManager->GetTexture(country + "Ground.png"));
		mapSprite.setPosition(sf::Vector2f(0, 0));

		airportData.minAltitude = 1000;
		airportData.maxAltitude = 10000;

		read = std::ifstream("../Resources/airports/" + country + "/ground.txt");

		read >> airportData.numberOfRunways;

		for (int i = 0; i < airportData.numberOfRunways;i++)
		{
			read >> airportData.runways[i].direction; // left / right
			read >> airportData.runways[i].heading;
			read >> airportData.runways[i].x >> airportData.runways[i].y;
		}
		
		read.close();

		read = std::ifstream("../Resources/airports/" + country + "/arrivalRoutes.txt");
		read >> airportData.numberOfNodes;
		for (int i = 0; i < airportData.numberOfNodes; i++)
		{
			for (int j = 0; j < airportData.numberOfNodes; j++)
			{
				read >> airportData.connection[i][j];
			}
		}
		for (int i = 0; i < airportData.numberOfNodes; i++)
		{
			read >> airportData.nodes[i].x >> airportData.nodes[i].y >> airportData.nodes[i].finalNode;
		}
		for (int i = 0; i < airportData.numberOfNodes; i++)
		{
			read >> airportData.spawns[i].x >> airportData.spawns[i].y;
		}
	}
	else if (position == "radar")
	{
		mapSprite.setTexture(assetsManager->GetTexture(country + "Radar.png"));
	}

	return;
}
