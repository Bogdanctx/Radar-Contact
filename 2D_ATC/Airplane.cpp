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

	std::string callsigns[CALLSIGNS] = { "ROT", "KLM", "AFR", "WZZ", "TAP" };
	
	airplaneSelected = false;
	settingNewHeading = false;

	airplane.setSize(sf::Vector2f(10, 10));
	airplane.setFillColor(sf::Color::Transparent);
	airplane.setOutlineColor(sf::Color::White);
	airplane.setOutlineThickness(3);

	int cadran = cadrans[rand()%4];
	sf::Vector2f spawnPosition;

	spawnPosition.x = rand() % (map->airportData.cadran[cadran].x2 - map->airportData.cadran[cadran].x1) + map->airportData.cadran[cadran].x1;
	spawnPosition.y = rand() % (map->airportData.cadran[cadran].y2 - map->airportData.cadran[cadran].y1) + map->airportData.cadran[cadran].y1;

	if (cadran == 0)
	{
		_heading = rand() % (210 - 120) + 120 + 90;
	}
	else if (cadran == 1)
	{
		_heading = rand() % (330 - 210) + 180;
	}
	else if (cadran == 2)
	{
		_heading = rand() % (300 - 60) + 60;
	}
	else if (cadran == 3)
	{
		_heading = rand() % (150 - 30) - 30;
	}
	if (_heading < 0)
		_heading += 360;

	airplane.setPosition(spawnPosition);

	_altitude = rand() % (map->airportData.maxAltitude - map->airportData.minAltitude) + map->airportData.minAltitude;
	_altitude -= _altitude % 100;
	_speed = rand() % (320 - 140) + 140;

	velocity.x = velocity.y = (float)_speed / 100;

	s_callSign = callsigns[rand() % CALLSIGNS] + std::to_string(rand() % 9999);

	dataStick.setSize(sf::Vector2f(2, 50));
	dataStick.setPosition(sf::Vector2f(
		spawnPosition.x+5,
		spawnPosition.y - 50
	));

	callsign.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	callsign.setPosition(sf::Vector2f(
		spawnPosition.x + 10,
		spawnPosition.y - 55
	));
	callsign.setCharacterSize(12);
	callsign.setString(s_callSign);

	heading.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	heading.setPosition(sf::Vector2f(
		spawnPosition.x + 10,
		spawnPosition.y - 43
	));
	heading.setCharacterSize(12);
	heading.setString(std::to_string(_heading));

	newHeading.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	newHeading.setPosition(sf::Vector2f(
		spawnPosition.x + 35,
		spawnPosition.y - 43
	));
	newHeading.setCharacterSize(12);
	newHeading.setString(std::to_string(_heading));
	newHeading.setFillColor(sf::Color::Cyan);

	directionShape.setSize(sf::Vector2f(2, 30));
	directionShape.setPosition(sf::Vector2f(
		spawnPosition.x + 5,
		spawnPosition.y + 5
	));
	directionShape.setFillColor(sf::Color::White);
	directionShape.setRotation(_heading - 180);

	altitude.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	altitude.setPosition(sf::Vector2f(
		spawnPosition.x + 10,
		spawnPosition.y - 31
	));
	altitude.setCharacterSize(12);
	altitude.setString(std::to_string(_altitude));

	newAltitude.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	newAltitude.setPosition(sf::Vector2f(
		spawnPosition.x + 45,
		spawnPosition.y - 31
	));
	newAltitude.setCharacterSize(12);
	newAltitude.setString(std::to_string(_newAltitude));
	newAltitude.setFillColor(sf::Color::Cyan);

	speed.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	speed.setPosition(sf::Vector2f(
		spawnPosition.x + 10,
		spawnPosition.y - 19
	));
	speed.setCharacterSize(12);
	speed.setString(std::to_string(_speed));
	speed.setFillColor(sf::Color::White);

	newSpeed.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	newSpeed.setPosition(sf::Vector2f(
		spawnPosition.x + 45,
		spawnPosition.y - 19
	));
	newSpeed.setCharacterSize(12);
	newSpeed.setString(std::to_string(_newSpeed));
	newSpeed.setFillColor(sf::Color::Cyan);
}

void Airplane::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;
	HandleInternEvents();

	if (altitudeChangeTimer.getElapsedTime().asMilliseconds() >= 1000)
	{
		if (_newAltitude != _altitude)
		{
			if (_newAltHelper > _altitude)
			{
				_altitude += 100;
			}
			if (_newAltHelper < _altitude)
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
			if (_newSpeedHelper > _speed)
				_speed++;
			if (_newSpeedHelper < _speed)
				_speed--;
			speed.setString(std::to_string(_speed));
			
			velocity.x = velocity.y = (float)_speed / 100;
		}
		speedChangeTimer.restart();
	}

	if (updateTimer.getElapsedTime().asMilliseconds() >= 700)
	{
		airplane.move(sf::Vector2f(
			sin( (_heading + 0) * PI / 180) * velocity.x,
			cos( (_heading + 180) * PI / 180) * velocity.y
		));
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
			airplanePosition.x + 35,
			airplanePosition.y - 43
		));
		altitude.setPosition(sf::Vector2f(
			airplanePosition.x + 10,
			airplanePosition.y - 31
		));
		newAltitude.setPosition(sf::Vector2f(
			airplanePosition.x + 45,
			airplanePosition.y - 31
		));
		speed.setPosition(sf::Vector2f(
			airplanePosition.x + 10,
			airplanePosition.y - 19
		));
		newSpeed.setPosition(sf::Vector2f(
			airplanePosition.x + 45,
			airplanePosition.y - 19
		));

		directionShape.setPosition(sf::Vector2f(
			airplanePosition.x + 5,
			airplanePosition.y + 5
		));

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
		{
			window->draw(newHeading);
		}
		if (settingNewAltitude)
		{
			window->draw(newAltitude);
		}
		if (settingNewSpeed)
		{
			window->draw(newSpeed);
		}
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
	HandleHeadingChange();
	HandleAltitudeChange();
	HandleSpeedChange();
	
	if(airplaneSelected == false)
	{
		_newHeading = _heading;
		_newAltitude = _altitude;
		_newSpeed = _speed;
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

	if (_newHeading != _heading && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) == false)
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

		settingNewAltitude = true;
	}
	else
	{
		_newAltHelper = _newAltitude;
		settingNewAltitude = false;
	}

	return;
}

void Airplane::HandleSpeedChange()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
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

		settingNewSpeed = true;
	}
	else
	{
		_newSpeedHelper = _newSpeed;
		settingNewSpeed = false;
	}

	return;
}

