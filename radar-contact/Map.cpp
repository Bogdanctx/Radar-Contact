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

Map::Map(AssetsManager assetsManager)
{
	this->assetsManager = assetsManager;
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

	map.setScale(sf::Vector2f(
		(float)assetsManager.getResolution().width / texture.getSize().x,
		(float)assetsManager.getResolution().height / texture.getSize().y
	));
}
