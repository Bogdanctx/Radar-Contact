#include "Map.h"

Map::Map()
{
	maps.push_back("romania");
}

void Map::update()
{

	return;
}

void Map::render(sf::RenderTarget* window)
{
	window->draw(mapSprite);

	return;
}

void Map::GenerateNewMap()
{
	std::string randomMap = maps[rand() % maps.size()];

	mapTexture.loadFromFile("../Resources/images/maps/" + randomMap + ".png");
	mapSprite.setTexture(mapTexture);

	return;
}
