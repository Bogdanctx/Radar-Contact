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

void Map::LoadMap(const std::string country, const std::string position)
{
	if (position == "ground")
	{
		mapSprite.setTexture(assetsManager->GetTexture(country + "Ground.png"));
		airportData.minAltitude = 1000;
		airportData.maxAltitude = 10000;

		read = std::ifstream("../Resources/airports/" + country + "/ground.txt");

		read >> airportData.cadran[0].x1 >> airportData.cadran[0].x2 >> airportData.cadran[0].y1 >> airportData.cadran[0].y2;
		read >> airportData.cadran[1].x1 >> airportData.cadran[1].x2 >> airportData.cadran[1].y1 >> airportData.cadran[1].y2;
		read >> airportData.cadran[2].x1 >> airportData.cadran[2].x2 >> airportData.cadran[2].y1 >> airportData.cadran[2].y2;
		read >> airportData.cadran[3].x1 >> airportData.cadran[3].x2 >> airportData.cadran[3].y1 >> airportData.cadran[3].y2;

		read >> airportData.numberOfRunways;

		for (int i = 0; i < airportData.numberOfRunways;i++)
		{
			read >> airportData.runways[i].direction; // left / right
			read >> airportData.runways[i].heading;
			read >> airportData.runways[i].x >> airportData.runways[i].y;
		}
		
		read.close();
	}
	else if (position == "radar")
	{
		mapSprite.setTexture(assetsManager->GetTexture(country + "Radar.png"));
	}

	return;
}
