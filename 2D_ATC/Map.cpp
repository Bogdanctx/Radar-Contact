#include "Map.h"

Map::Map()
{

}

void Map::AirportData::GenerateRoute(Path &path, int startingNode)
{
	sf::Vector2f nodePosition(nodes[startingNode].x, nodes[startingNode].y);

	path.AddPoint(nodePosition, startingNode);

	bool usedNode[50] = { 0 };
	usedNode[startingNode] = 1;

	std::vector<int>tempPath;
	tempPath.push_back(startingNode);

	for (int j = 0; j < numberOfNodes; j++)
	{
		int prevNode = tempPath[tempPath.size()-1];

		if (connection[prevNode][j] == 1 && usedNode[j] == 0)
		{
			tempPath.push_back(j);
			usedNode[j] = 1;
			path.AddPoint(sf::Vector2f(nodes[j].x, nodes[j].y), j);

			if (nodes[j].finalNode == 1)
			{
				break;
			}

			j = 0;
		}
	}

	return;
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
	mapTexture.loadFromFile("../Resources/images/maps/" + country + "/" + position + ".png");

	if (position == "ground")
	{
		mapSprite.setTexture(mapTexture);
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
		mapSprite.setTexture(mapTexture);
	}

	return;
}
