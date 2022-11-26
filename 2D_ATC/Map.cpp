#include "Map.h"

#define GAMEMODE_TOWER 1
#define GAMEMODE_RADAR 2

Map::Map()
{

}

Map::Map(AssetsManager assetsManager)
{
	this->assetsManager = assetsManager;
}

void Map::MapData::GenerateRoute(Path& path, sf::Vector2f pointA, sf::Vector2f pointB)
{
	const short dx[] = { -1, 0, 1, 0 },
				dy[] = { 0, 1, 0,-1 };

	unsigned short xstart, ystart;
	xstart = pointA.x;
	ystart = pointA.y;

	std::queue<std::pair<unsigned short, unsigned short>>q;
	q.push(std::make_pair(xstart, ystart));
	map[xstart][ystart] = 1;

	while (!q.empty())
	{
		short x = q.front().first;
		short y = q.front().second;

		for (unsigned short d = 0; d < 4; d++)
		{
			short newx = x + dx[d];
			short newy = y + dy[d];

			if (newx >= 1 && newx <= 1200 && newy >= 1 && newy <= 900 && map[newx][newy] == 0)
			{
				map[newx][newy] = map[x][y] + 1;
				q.push(std::make_pair(newx, newy));
			}
		}
		q.pop();
	}

	std::vector<std::pair<short, short>>v;
	short x = pointB.x, y = pointB.y;
	v.push_back(std::make_pair(x, y));
	do
	{
		short p = -1;
		for (unsigned short d = 0; d < 4&&p==-1; d++)
		{
			if (x + dx[d] <= 1200 && y + dy[d] <= 900)
			{
				if (map[x][y] == map[x + dx[d]][y + dy[d]] + 1)
				{
					p = d;
				}
			}
		}
		x += dx[p];
		y += dy[p];
		v.push_back(std::make_pair(x, y));
	} while (map[x][y] != 1);

	unsigned short pointsAdded = 1;
	for (std::vector<std::pair<short, short>>::reverse_iterator I = v.rbegin(); I != v.rend(); I++, pointsAdded++)
	{
		if (pointsAdded % 50 == 0)
		{
			path.AddPoint(sf::Vector2f(I->first, I->second));
		}
	}

	return;
}

void Map::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	if (gamemode == GAMEMODE_RADAR)
	{
		
	}

	return;
}

void Map::render(sf::RenderTarget* window)
{
	window->draw(mapSprite);

	if (gamemode == GAMEMODE_RADAR)
	{

		for (auto it : mapData.airportsPin)
		{
			window->draw(it.pin);
			window->draw(it.icaoText);
		}

	}

	return;
}

void Map::LoadMap(const unsigned short gamemode)
{
	this->gamemode = gamemode;

	std::ifstream read;

	read.open("../Resources/game.txt");
	std::string country;
	read >> country;
	read.close();

	mapData.map = std::vector<std::vector<unsigned short>>(1205, std::vector<unsigned short>(905));

	if (gamemode == GAMEMODE_TOWER) // Tower
	{
		mapTexture.loadFromFile("../Resources/images/maps/"+country+"/tower.png");
		mapSprite.setTexture(mapTexture);

		mapData.minAltitude = 1000;
		mapData.maxAltitude = 10000;

		read.open("../Resources/airports/" + country + "/tower.txt");

		read >> mapData.numberOfRunways;

		for (unsigned short i = 0; i < mapData.numberOfRunways;i++)
		{
			MapData::Runways runway;

			read >> runway.heading >> runway.x >> runway.y >> runway.coordsTowardsRunway.x >> runway.coordsTowardsRunway.y;
		
			mapData.runways.push_back(runway);
		}

		read >> mapData.airportsBoundsTopLeft.x >> mapData.airportsBoundsTopLeft.y >> mapData.airportBoundsBottomRight.x >> mapData.airportBoundsBottomRight.y;

		for (unsigned short j = mapData.airportsBoundsTopLeft.x; j <= mapData.airportBoundsBottomRight.x; j++)
		{
			mapData.map[j][mapData.airportsBoundsTopLeft.y] = 1;
			mapData.map[j][mapData.airportBoundsBottomRight.y] = 1;
		}
		for (unsigned short i = mapData.airportsBoundsTopLeft.y; i <= mapData.airportBoundsBottomRight.y; i++)
		{
			mapData.map[mapData.airportsBoundsTopLeft.x][i] = 1;
			mapData.map[mapData.airportBoundsBottomRight.x][i] = 1;
		}

	}
	else // Radar
	{
		mapTexture.loadFromFile("../Resources/images/maps/" + country + "/radar.png");
		mapSprite.setTexture(mapTexture);

		mapData.minAltitude = 10000;
		mapData.maxAltitude = 40000;

		read.open("../Resources/airports/" + country + "/radar.txt");
		read >> mapData.numberOfAirports;

		for (unsigned short i = 0; i < mapData.numberOfAirports; i++)
		{
			MapData::AirportPin airportPin;
			airportPin.assetsManager = &assetsManager;
			read >> airportPin.position.x >> airportPin.position.y >> airportPin.icao;
			airportPin.StylePin();

			mapData.airportsPin.push_back(airportPin);
		}
	}


	return;
}

Map::MapData::AirportPin::AirportPin()
{
	pin = sf::CircleShape(4, 3);
	pin.setFillColor(sf::Color::Transparent);
	pin.setOutlineColor(sf::Color::White);
	pin.setOutlineThickness(2);
}

void Map::MapData::AirportPin::StylePin()
{
	icaoText.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	icaoText.setString(icao);
	icaoText.setCharacterSize(12);

	sf::FloatRect bounds = icaoText.getGlobalBounds();
	icaoText.setOrigin(sf::Vector2f(
		bounds.left + bounds.width / 2,
		bounds.top + bounds.height / 2
	));
	icaoText.setPosition(sf::Vector2f(position.x, position.y - 15));

	bounds = pin.getGlobalBounds();
	pin.setOrigin(sf::Vector2f(
		bounds.left + bounds.width / 2,
		bounds.top + bounds.height / 2
	));
	pin.setPosition(position);
	
	return;
}