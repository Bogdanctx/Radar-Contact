#include "Airplane.h"
#include "Math.h"
#include "Constants.h"

Airplane::Airplane()
{

}

Airplane::Airplane(AssetsManager *assetsManager, Map::MapData mapData, unsigned short gamemode)
{
	this->assetsManager = assetsManager;
	this->mapData = mapData;

	this->gamemode = gamemode;

	airplaneSelected = false;
	settingNewHeading = false;
	destroyPlane = false;
	headingFixed = false;

	airplane.setSize(sf::Vector2f(10, 10));
	airplane.setFillColor(sf::Color::Transparent);
	airplane.setOutlineColor(sf::Color::White);
	airplane.setOutlineThickness(3);

	CreateAirplane();
	initText();
}

void Airplane::update(sf::Vector2i mousePosition)
{
	if (destroyPlane)
		return;

	this->mousePosition = mousePosition;

	route.update(mousePosition);

	HandleInternEvents();

	UpdateData();
	UpdateText();

	if (updateTimer.getElapsedTime().asMilliseconds() >= 700)
	{
		airplane.move(sf::Vector2f(
			sin( (_heading + 0) * PI / 180) * velocity.x,
			cos( (_heading + 180) * PI / 180) * velocity.y
		));
		
		CheckNode();
		
		if (gamemode == GAMEMODE_TOWER)
		{
			CheckLanding();
		}
		else if(gamemode == GAMEMODE_RADAR && _altitude <= 11000 && _speed <= 250 && Math::DistanceToPoint(airplane.getPosition(), mapData.airportsPin[randomChoice].position) <= 5.f) // Plane has reached its final point
		{
			destroyPlane = 1;
		}

		updateTimer.restart();
	}

	return;
}

void Airplane::render(sf::RenderTarget* window)
{
	route.render(window);

	window->draw(airplane);
	window->draw(callsign);

	if (airplaneSelected)
	{
		window->draw(directionShape);
	
		if (settingNewHeading)
			window->draw(newHeading);
		if (settingNewAltitude)
			window->draw(newAltitude);
		if (settingNewSpeed)
			window->draw(newSpeed);

		window->draw(altitude);
		window->draw(speed);
		window->draw(heading);
		window->draw(arrivalAirport);
	}

	return;
}

void Airplane::HandleClick()
{
	if (airplane.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
	{
		directionShape.setFillColor(sf::Color::Cyan);
		airplaneSelected = true;
		route.draw();

	}
	else
	{
		directionShape.setFillColor(sf::Color::White);
		airplaneSelected = false;
		route.HidePath();
	}

	return;
}

void Airplane::HandleButtonPressed(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::R) // back to course
	{
		if (route.length() && airplaneSelected == true)
		{
			_heading = _newHeading = Math::DirectionToPoint(airplane.getPosition(), route.NextPointPosition());
		}
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

		_newHeading = (int)(-atan2(x2 - x1, y2 - y1) * 180 / PI);

		if (_newHeading < 0)
			_newHeading += 360;

		directionShape.setRotation(_newHeading - 180);
		newHeading.setString(std::to_string(_newHeading));

		settingNewHeading = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		directionShape.setSize(sf::Vector2f(
			2, Math::DistanceToPoint(
				airplane.getPosition(), 
				sf::Vector2f(mousePosition.x, mousePosition.y)
			)
		));
		directionShape.setRotation(Math::DirectionToPoint(
			sf::Vector2f(mousePosition.x, mousePosition.y),
			airplane.getPosition()
		));

		directPoint = route.PointHovered();
	}
	else
	{
		if (directPoint != -1)
		{
			route.RemoveUntilPoint(directPoint);
			_newHeading = Math::DirectionToPoint(
				airplane.getPosition(),
				route.NextPointPosition()
			);
		}

		_heading = _newHeading;
		heading.setString(std::to_string(_heading));
		settingNewHeading = false;

		directionShape.setSize(sf::Vector2f(DIRECTION_SHAPE_WIDTH, DIRECTION_SHAPE_HEIGHT));
		directionShape.setRotation(_heading-180);
	}

	return;
}

void Airplane::HandleAltitudeChange()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		settingNewAltitude = true;

		if (altitudeChangeTimer.getElapsedTime().asMilliseconds() >= 40)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (_newAltitude + 100 <= mapData.maxAltitude)
				{
					_newAltitude += 100;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (_newAltitude - 100 >= mapData.minAltitude)
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

			speedChangeTimer.restart();
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
	if (altitudeChangeTimer.getElapsedTime().asMilliseconds() >= 600)
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

	if (speedChangeTimer.getElapsedTime().asMilliseconds() >= 700)
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

	return;
}

void Airplane::CheckNode()
{
	double dist;

	if (route.length())
	{
		dist = Math::DistanceToPoint(airplane.getPosition(), route.NextPointPosition());

		if (dist <= 15.f && !headingFixed) // fix heading error
		{
			_heading = _newHeading = (int)Math::DirectionToPoint(airplane.getPosition(), route.NextPointPosition());
			headingFixed = true;
		}

		if (dist <= 4.f)
		{
			airplane.setPosition(route.NextPointPosition());

			route.RemoveFirstPoint();

			if (route.length() > 1)
			{
				_heading = _newHeading = (int) Math::DirectionToPoint(airplane.getPosition(), route.NextPointPosition());

				heading.setString(std::to_string(_heading));
				headingFixed = false;
			}
		}
	}

	return;
}

void Airplane::CheckLanding()
{
	sf::Vector2f airplanePosition = airplane.getPosition();

	for (unsigned short i = 0; i < mapData.numberOfRunways; i++)
	{
		sf::Vector2f runwayPosition(mapData.runways[i].x, mapData.runways[i].y);

		double dist = Math::DistanceToPoint(airplanePosition, runwayPosition);

		if (dist < 10.f)
		{
			short runwayHeading = mapData.runways[i].heading;

			short leftError;
			short rightError;

			leftError = runwayHeading - 10 + 360 * (runwayHeading - 10 < 0);
			rightError = runwayHeading + 10 - 360 * (runwayHeading + 10 > 360);

			if (leftError <= _heading && _heading <= rightError) // aici este conflict in caz de 360/0 grade (fixat)
			{
				if (_speed <= 180 && _altitude <= 2000)
				{
					destroyPlane = 1;
				}
			}

		}
	}

	return;
}

void Airplane::CreateAirplane()
{
	unsigned short _t = rand() % 4;
	/*
		_t values:
		0 -> right screen
		1 -> top screen
		2 -> left screen
		3 -> bottom screen
	*/

	if (_t == 0)
	{
		spawnPosition.x = 1200 - 10;
		spawnPosition.y = rand() % (900 - 10);
	}
	else if (_t == 1)
	{
		spawnPosition.x = rand() % (1200 - 10);
		spawnPosition.y = 10;
	}
	else if (_t == 2)
	{
		spawnPosition.x = 10;
		spawnPosition.y = rand() % (900 - 10);
	}
	else
	{
		spawnPosition.x = rand() % (1200 - 10);
		spawnPosition.y = 900 - 10;
	}

	if (gamemode == 1) // playing as tower
	{
		randomChoice = rand() % mapData.numberOfRunways;

		mapData.GenerateRoute(route, spawnPosition, mapData.runways[randomChoice].coordsTowardsRunway);
	}
	else // playing as radar
	{
		randomChoice = rand() % mapData.numberOfAirports;

		mapData.GenerateRoute(route, spawnPosition, mapData.airportsPin[randomChoice].position);
	}

	airplane.setPosition(spawnPosition);

	_heading = _newHeading = (short) Math::DirectionToPoint(spawnPosition, route.NextPointPosition()) ;

	_altitude = rand() % (mapData.maxAltitude - mapData.minAltitude) + mapData.minAltitude;
	_altitude -= _altitude % 100;
	_newAltitude = _altitude;

	_speed = _newSpeed = rand() % (320 - 230) + 230;

	if (gamemode == GAMEMODE_RADAR)
		arrivalAirport.setString(mapData.airportsPin[randomChoice].icao);
	else
		arrivalAirport.setString(mapData.arrivalAirportIcao);

	velocity.x = velocity.y = (float)_speed / 100;

	std::vector<std::string>callsigns {
		"ROT", "KLM", "AFR", "WZZ", "TAP"
	};

	s_callSign = callsigns[rand() % callsigns.size()] + std::to_string(rand() % 9999);

	return;
}

void Airplane::SetTCAS(unsigned short level)
{
	if(level == 0)
		airplane.setOutlineColor(sf::Color::White);
	else if (level == 1)
		airplane.setOutlineColor(sf::Color(189, 143, 19));
	else
		airplane.setOutlineColor(sf::Color(171, 12, 12));

	return;
}

void Airplane::UpdateText()
{
	sf::FloatRect bounds = airplane.getGlobalBounds();
	sf::Vector2f airplanePosition = airplane.getPosition();

	callsign.setPosition(sf::Vector2f(airplanePosition.x, CALLSIGN_POSITION_Y(airplanePosition.y, !airplaneSelected)));

	altitude.setPosition(sf::Vector2f(airplanePosition.x, ALTITUDE_POSITION_Y(airplanePosition.y, !airplaneSelected)));

	newAltitude.setPosition(sf::Vector2f(altitude.getGlobalBounds().left+altitude.getLocalBounds().width+3, NEW_ALTITUDE_POSITON_Y(airplanePosition.y)));

	speed.setPosition(sf::Vector2f(airplanePosition.x, SPEED_POSITION_Y(airplanePosition.y, !airplaneSelected)));

	newSpeed.setPosition(sf::Vector2f(speed.getGlobalBounds().left+speed.getLocalBounds().width+3, NEW_SPEED_POSITION_Y(airplanePosition.y)));

	heading.setPosition(sf::Vector2f(airplanePosition.x, HEADING_POSITION_Y(airplanePosition.y)));

	newHeading.setPosition(sf::Vector2f(heading.getGlobalBounds().left+heading.getLocalBounds().width+3, NEW_HEADING_POSITION_Y(airplanePosition.y)));

	arrivalAirport.setPosition(sf::Vector2f(airplanePosition.x, ARRIVAL_AIRPORT_POSITION_Y(airplanePosition.y)));

	directionShape.setPosition(sf::Vector2f(airplanePosition.x+5, DIRECTION_SHAPE_POSITION_Y(airplanePosition.y)));

	return;
}

void Airplane::initText()
{
	callsign.setPosition(sf::Vector2f(spawnPosition.x, CALLSIGN_POSITION_Y(spawnPosition.y, !airplaneSelected)));
	callsign.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	callsign.setString(s_callSign);
	callsign.setCharacterSize(AIRPLANE_TEXT_SIZE);

	altitude.setPosition(sf::Vector2f(spawnPosition.x, ALTITUDE_POSITION_Y(spawnPosition.y, !airplaneSelected)));
	altitude.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	altitude.setString(std::to_string(_altitude));
	altitude.setCharacterSize(AIRPLANE_TEXT_SIZE);

	newAltitude.setPosition(sf::Vector2f(spawnPosition.x, NEW_ALTITUDE_POSITON_Y(spawnPosition.y)));
	newAltitude.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	newAltitude.setString(std::to_string(_newAltitude));
	newAltitude.setCharacterSize(AIRPLANE_TEXT_SIZE);
	newAltitude.setFillColor(sf::Color::Cyan);

	speed.setPosition(sf::Vector2f(spawnPosition.x, SPEED_POSITION_Y(spawnPosition.y, !airplaneSelected)));
	speed.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	speed.setString(std::to_string(_speed));
	speed.setCharacterSize(AIRPLANE_TEXT_SIZE);

	newSpeed.setPosition(sf::Vector2f(spawnPosition.x, NEW_SPEED_POSITION_Y(spawnPosition.y)));
	newSpeed.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	newSpeed.setString(std::to_string(_newSpeed));
	newSpeed.setCharacterSize(AIRPLANE_TEXT_SIZE);
	newSpeed.setFillColor(sf::Color::Cyan);

	heading.setPosition(sf::Vector2f(spawnPosition.x, HEADING_POSITION_Y(spawnPosition.y)));
	heading.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	heading.setString(std::to_string(_heading));
	heading.setCharacterSize(AIRPLANE_TEXT_SIZE);

	newHeading.setPosition(sf::Vector2f(spawnPosition.x, NEW_HEADING_POSITION_Y(spawnPosition.y)));
	newHeading.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	newHeading.setString(std::to_string(_heading));
	newHeading.setCharacterSize(AIRPLANE_TEXT_SIZE);
	newHeading.setFillColor(sf::Color::Cyan);

	arrivalAirport.setPosition(sf::Vector2f(spawnPosition.x, ARRIVAL_AIRPORT_POSITION_Y(spawnPosition.y)));
	arrivalAirport.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	arrivalAirport.setCharacterSize(AIRPLANE_TEXT_SIZE);

	directionShape.setPosition(sf::Vector2f(spawnPosition.x+5, DIRECTION_SHAPE_POSITION_Y(spawnPosition.y)));
	directionShape.setRotation(_heading - 180);
	directionShape.setSize(sf::Vector2f(DIRECTION_SHAPE_WIDTH, DIRECTION_SHAPE_HEIGHT));

	return;
}