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

void Map::LoadMap(const int position)
{
	std::ifstream read;

	read.open("../Resources/game.txt");
	std::string country;
	read >> country;
	read.close();

	if (position == 1) // Tower
	{
		mapTexture.loadFromFile("../Resources/images/maps/"+country+"/tower.png");
		mapSprite.setTexture(mapTexture);

		airportData.minAltitude = 1000;
		airportData.maxAltitude = 10000;

		read.open("../Resources/airports/" + country + "/tower.txt");

		read >> airportData.numberOfRunways;

		for (int i = 0; i < airportData.numberOfRunways;i++)
		{
			read >> airportData.runways[i].direction; // left / right
			read >> airportData.runways[i].heading;
			read >> airportData.runways[i].x >> airportData.runways[i].y;
		}
		
		read.close();

		read.open("../Resources/airports/" + country + "/arrivalRoutes.txt");
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


	return;
}
