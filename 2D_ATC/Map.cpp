#include "Map.h"

Map::Map()
{
	maps.push_back("romania");
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

void Map::GenerateMap(std::string country, std::string position)
{
	std::string airport = "lrop";

	mapTexture.loadFromFile("../Resources/images/maps/" + country + "/" + position + "/" + airport + ".png");
	mapSprite.setTexture(mapTexture);

	return;
}