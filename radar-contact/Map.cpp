#include "Map.h"

/*

Map image data
Contrast: 100
Exposure: -40
Hightlights: -100
Clarity: 100

*/

Map::Map()
{

}

void Map::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;
}

void Map::render(sf::RenderTarget* window)
{
	window->draw(map);
}

void Map::processEvents(sf::Event event)
{
	switch(event.type)
	{
	
	}
}

void Map::load(const std::string icao)
{
	texture.loadFromFile("../Resources/images/" + icao + ".png");

	map.setTexture(texture);
}