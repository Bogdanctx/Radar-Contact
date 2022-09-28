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
	}
	else if (position == "radar")
	{
		mapSprite.setTexture(assetsManager->GetTexture(country + "Radar.png"));
	}

	return;
}
