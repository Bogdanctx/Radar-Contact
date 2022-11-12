#include "Map.h"

Map::Map()
{

}

void Map::AirportData::GenerateRoute(Path& path, sf::Vector2f pointA, sf::Vector2f pointB)
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

	unsigned short pointsAdded = 0;
	for (std::vector<std::pair<short, short>>::reverse_iterator I = v.rbegin(); I != v.rend(); I++, pointsAdded++)
	{
		if (pointsAdded % 50 == 0)
		{
			path.AddPoint(sf::Vector2f(I->first, I->second), path.length());
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

void Map::LoadMap(const unsigned short position)
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

		for (unsigned short i = 0; i < airportData.numberOfRunways;i++)
		{
			read >> airportData.runways[i].heading >> airportData.runways[i].x >> airportData.runways[i].y >> airportData.nodes[i].x >> airportData.nodes[i].y;
		}

		read >> airportData.airportsBoundsTopLeft.x >> airportData.airportsBoundsTopLeft.y >> airportData.airportBoundsBottomRight.x >> airportData.airportBoundsBottomRight.y;

		airportData.map = std::vector<std::vector<short>>(1201, std::vector<short>(901));

		for (unsigned short j = airportData.airportsBoundsTopLeft.x; j <= airportData.airportBoundsBottomRight.x; j++)
		{
			airportData.map[j][airportData.airportsBoundsTopLeft.y] = 1;
			airportData.map[j][airportData.airportBoundsBottomRight.y] = 1;
		}
		for (unsigned short i = airportData.airportsBoundsTopLeft.y; i <= airportData.airportBoundsBottomRight.y; i++)
		{
			airportData.map[airportData.airportsBoundsTopLeft.x][i] = 1;
			airportData.map[airportData.airportBoundsBottomRight.x][i] = 1;
		}

	}


	return;
}
