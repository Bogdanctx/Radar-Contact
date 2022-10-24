#include "Airplane.h"

#define PI 3.14159265
#define CALLSIGNS 5

Airplane::Airplane()
{

}

Airplane::Airplane(AssetsManager* assetsManager, Map *map)
{
	this->assetsManager = assetsManager;
	this->map = map;
	
	airplaneSelected = false;
	settingNewHeading = false;
	destroyPlane = false;

	airplane.setSize(sf::Vector2f(10, 10));
	airplane.setFillColor(sf::Color::Transparent);
	airplane.setOutlineColor(sf::Color::White);
	airplane.setOutlineThickness(3);

	routeLength = 0;
	currNode = 0;

	CreateAirplane();
	initText();
}

void Airplane::update(sf::Vector2i mousePosition)
{
	if (destroyPlane)
		return;

	this->mousePosition = mousePosition;

	HandleInternEvents();

	if (updateTimer.getElapsedTime().asMilliseconds() >= 100)
	{
		UpdateData();

		airplane.move(sf::Vector2f(
			sin( (_heading + 0) * PI / 180) * velocity.x,
			cos( (_heading + 180) * PI / 180) * velocity.y
		));
		
		CheckNode();
		CheckLanding();

		updateTimer.restart();
	}

	return;
}

void Airplane::render(sf::RenderTarget* window)
{
	window->draw(airplane);
	window->draw(dataStick);
	window->draw(callsign);
	window->draw(heading);
	window->draw(altitude);
	window->draw(speed);

	if (airplaneSelected)
	{
		window->draw(directionShape);
	
		if (settingNewHeading)
			window->draw(newHeading);
		if (settingNewAltitude)
			window->draw(newAltitude);
		if (settingNewSpeed)
			window->draw(newSpeed);
	}

	return;
}

void Airplane::HandleClick()
{
	if (airplane.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
	{
		directionShape.setFillColor(sf::Color::Cyan);
		airplaneSelected = true;
	}
	else
	{
		directionShape.setFillColor(sf::Color::White);
		airplaneSelected = false;
	}

	return;
}

void Airplane::HandleInternEvents()
{
	if (airplaneSelected == true)
	{
		HandleHeadingChange();
		HandleAltitudeChange();
		HandleSpeedChange();
	}

	return;
}

void Airplane::HandleHeadingChange()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		short x1, x2;
		short y1, y2;

		x1 = airplane.getPosition().x;
		x2 = mousePosition.x;
		y1 = airplane.getPosition().y;
		y2 = mousePosition.y;

		_newHeading = -atan2(x2 - x1, y2 - y1) * 180 / PI;

		if (_newHeading < 0)
			_newHeading += 360;

		directionShape.setRotation(_newHeading - 180);
		newHeading.setString(std::to_string(_newHeading));

		settingNewHeading = true;
	}
	else
	{
		_heading = _newHeading;
		heading.setString(std::to_string(_heading));
		settingNewHeading = false;
	}

	return;
}

void Airplane::HandleAltitudeChange()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		settingNewAltitude = true;

		if (altitudeChangeTimer.getElapsedTime().asMilliseconds() >= 150)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (_newAltitude + 100 <= map->airportData.maxAltitude)
				{
					_newAltitude += 100;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (_newAltitude - 100 >= map->airportData.minAltitude)
				{
					_newAltitude -= 100;
				}
			}

			altitudeChangeTimer.restart();
		}

		newAltitude.setString(std::to_string(_newAltitude));

		if (_newAltitude != _altitude)
			altitudeUpdated = true;
		else
			altitudeUpdated = false;

	}
	else
	{
		settingNewAltitude = false;
	}

	return;
}

void Airplane::HandleSpeedChange()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		settingNewSpeed = true;

		if (speedChangeTimer.getElapsedTime().asMilliseconds() >= 50)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (_newSpeed + 1 <= 350)
				{
					_newSpeed++;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (_newSpeed - 1 >= 140)
				{
					_newSpeed--;
				}
			}
		}

		newSpeed.setString(std::to_string(_newSpeed));

		if (_newSpeed != _speed)
			speedUpdated = true;
		else
			speedUpdated = false;
	}
	else
	{
		settingNewSpeed = false;
	}

	return;
}

void Airplane::UpdateData()
{
	if (altitudeChangeTimer.getElapsedTime().asMilliseconds() >= 1000)
	{
		if (altitudeUpdated)
		{
			if (_newAltitude > _altitude)
			{
				_altitude += 100;
			}
			if (_newAltitude < _altitude)
			{
				_altitude -= 100;
			}

			altitude.setString(std::to_string(_altitude));
		}

		altitudeChangeTimer.restart();
	}

	if (speedChangeTimer.getElapsedTime().asMilliseconds() >= 200)
	{
		if (_newSpeed != _speed)
		{
			if (_newSpeed > _speed)
				_speed++;
			if (_newSpeed < _speed)
				_speed--;
			speed.setString(std::to_string(_speed));

			velocity.x = velocity.y = (float)_speed / 100;
		}
		speedChangeTimer.restart();
	}

	sf::Vector2f airplanePosition = airplane.getPosition();

	dataStick.setPosition(sf::Vector2f(
		airplanePosition.x + 5,
		airplanePosition.y - 50
	));
	callsign.setPosition(sf::Vector2f(
		airplanePosition.x + 10,
		airplanePosition.y - 55
	));

	heading.setPosition(sf::Vector2f(
		airplanePosition.x + 10,
		airplanePosition.y - 43
	));
	newHeading.setPosition(sf::Vector2f(
		airplanePosition.x + heading.getLocalBounds().width + 13,
		airplanePosition.y - 43
	));
	altitude.setPosition(sf::Vector2f(
		airplanePosition.x + 10,
		airplanePosition.y - 31
	));
	newAltitude.setPosition(sf::Vector2f(
		airplanePosition.x + altitude.getLocalBounds().width + 13,
		airplanePosition.y - 31
	));
	speed.setPosition(sf::Vector2f(
		airplanePosition.x + 10,
		airplanePosition.y - 19
	));
	newSpeed.setPosition(sf::Vector2f(
		airplanePosition.x + speed.getLocalBounds().width + 13,
		airplanePosition.y - 19
	));

	directionShape.setPosition(sf::Vector2f(
		airplanePosition.x + 5,
		airplanePosition.y + 5
	));

	return;
}

void Airplane::GenerateRoute()
{
	bool used[50] = { 0 };
	used[route[0]] = 1;

	for (int j = 0; j < map->airportData.numberOfNodes; j++)
	{
		if (map->airportData.connection[route[routeLength - 1]][j] == 1 && used[j] == 0)
		{
			route[routeLength++] = j;
			used[j] = 1;

			if (map->airportData.nodes[j].finalNode == 1)
			{
				break;
			}

			j = 0;
		}
	}

	for (int i = 0; i < routeLength; i++)
	{
		printf("%d ", route[i]);
	}

	return;
}

void Airplane::CheckNode()
{
	sf::Vector2f airplanePosition = airplane.getPosition();
	sf::Vector2f nodePosition(map->airportData.nodes[route[currNode]].x,
								map->airportData.nodes[route[currNode]].y);

	int distX = airplanePosition.x - nodePosition.x;
	int distY = airplanePosition.y - nodePosition.y;

	int len = sqrt(distX * distX + distY * distY);

	if (len <= 15)
	{
		if (currNode + 1 < routeLength)
		{
			++currNode;
			_heading = HeadingToNode(route[currNode]);

			if (currNode + 1 == routeLength)
			{
				airplane.setFillColor(sf::Color::Blue);
			}
		}
	}

	return;
}

void Airplane::CheckLanding()
{
	sf::Vector2f airplanePosition = airplane.getPosition();

	for (int i = 0; i < map->airportData.numberOfRunways; i++)
	{
		sf::Vector2i runwayCoords(map->airportData.runways[i].x,
			map->airportData.runways[i].y);

		int distX = runwayCoords.x - airplanePosition.x;
		int distY = runwayCoords.y - airplanePosition.y;

		int len = sqrt(distX*distX + distY * distY);

		if (len < 10)
		{
			int runwayHeading = map->airportData.runways[i].heading;

			if (runwayHeading - 10 <= _heading && _heading <= runwayHeading + 10)
			{
				destroyPlane = 1;
			}
		}
	}

	return;
}

short Airplane::HeadingToNode(int node)
{

	
}

void Airplane::CreateAirplane()
{
	int randPosition = rand() % map->airportData.numberOfNodes;
	randPosition = 6;
	
	route[routeLength++] = randPosition;

	GenerateRoute();

	spawnPosition.x = map->airportData.spawns[randPosition].x;
	spawnPosition.y = map->airportData.spawns[randPosition].y;
	airplane.setPosition(spawnPosition);

	_heading = HeadingToNode(route[routeLength - 1]);

	_newHeading = _heading;	

	_altitude = rand() % (map->airportData.maxAltitude - map->airportData.minAltitude) + map->airportData.minAltitude;
	_altitude -= _altitude % 100;
	_newAltitude = _altitude;

	_speed = rand() % (320 - 140) + 140;
	_newSpeed = _speed;

	velocity.x = velocity.y = (float)_speed / 100;

	std::string callsigns[CALLSIGNS] = { "ROT", "KLM", "AFR", "WZZ", "TAP" };
	s_callSign = callsigns[rand() % CALLSIGNS] + std::to_string(rand() % 9999);

	return;
}

void Airplane::initText()
{
	dataStick.setPosition(sf::Vector2f(spawnPosition.x + 5, spawnPosition.y - 50));
	callsign.setPosition(sf::Vector2f(spawnPosition.x + 10, spawnPosition.y - 55));
	heading.setPosition(sf::Vector2f(spawnPosition.x + 10, spawnPosition.y - 43));
	newHeading.setPosition(sf::Vector2f(spawnPosition.x + 35, spawnPosition.y - 43));
	directionShape.setPosition(sf::Vector2f(spawnPosition.x + 5, spawnPosition.y + 5));
	altitude.setPosition(sf::Vector2f(spawnPosition.x + 10, spawnPosition.y - 31));
	newAltitude.setPosition(sf::Vector2f(spawnPosition.x + 45, spawnPosition.y - 31));
	speed.setPosition(sf::Vector2f(spawnPosition.x + 10, spawnPosition.y - 19));
	newSpeed.setPosition(sf::Vector2f(spawnPosition.x + 45, spawnPosition.y - 19));

	callsign.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	heading.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	newHeading.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	altitude.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	newAltitude.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	speed.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	newSpeed.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));

	heading.setCharacterSize(12);
	speed.setCharacterSize(12);
	callsign.setCharacterSize(12);
	altitude.setCharacterSize(12);
	newHeading.setCharacterSize(12);
	newAltitude.setCharacterSize(12);
	newSpeed.setCharacterSize(12);

	heading.setString(std::to_string(_heading));
	callsign.setString(s_callSign);
	speed.setString(std::to_string(_speed));
	altitude.setString(std::to_string(_altitude));
	newHeading.setString(std::to_string(_heading));
	newAltitude.setString(std::to_string(_newAltitude));
	newSpeed.setString(std::to_string(_newSpeed));

	directionShape.setFillColor(sf::Color::White);
	speed.setFillColor(sf::Color::White);
	newHeading.setFillColor(sf::Color::Cyan);
	newAltitude.setFillColor(sf::Color::Cyan);
	newSpeed.setFillColor(sf::Color::Cyan);

	directionShape.setRotation(_heading - 180);

	dataStick.setSize(sf::Vector2f(2, 50));
	directionShape.setSize(sf::Vector2f(2, 30));

	return;
}