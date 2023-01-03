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

    for(auto &it: runways)
    {
        it.update(mousePosition);
    }
    for (auto& it : points)
    {
        it.update(mousePosition);
    }
}

void Map::render(sf::RenderTarget* window)
{
	window->draw(map);

	for(auto it: runways)
    {
        it.render(window);
    }
    for (auto it : points)
    {
        it.render(window);
    }
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

    std::ifstream in("../Resources/airports/" + icao + ".airport");

    std::getline(in, airportIcao);
    std::getline(in, airportName);

    in>>airportRunways;

    for(unsigned short i=0;i<airportRunways;i++)
    {
        float x, y, length;
        unsigned short heading;
        in>>x>>y>>heading>>length;
        Runway runway = Runway(assetsManager, sf::Vector2f(x, y), heading, length);
        runways.push_back(runway);
    }
    in >> numberOfPoints;
    for (unsigned short i = 0; i < numberOfPoints; i++)
    {
        std::string name;
        float x, y;
        in >> name >> x >> y;
        Point point = Point(&assetsManager, name, sf::Vector2f(x, y));
        
        points.push_back(point);
    }

    in.close();
}
