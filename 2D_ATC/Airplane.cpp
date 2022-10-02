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

	velocity.x = velocity.y = 1.5f;

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

	_altitude = (rand() % 9 + 1) * std::pow(10, rand() % 2 + 2);

	s_callSign = callsigns[rand() % CALLSIGNS] + std::to_string(rand() % 9999);

	dataStick.setSize(sf::Vector2f(2, 40));
	dataStick.setPosition(sf::Vector2f(
		spawnPosition.x+5,
		spawnPosition.y - 40
	));

	callsign.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	callsign.setPosition(sf::Vector2f(
		spawnPosition.x + 10,
		spawnPosition.y - 45
	));
	callsign.setCharacterSize(12);
	callsign.setString(s_callSign);

	heading.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	heading.setPosition(sf::Vector2f(
		spawnPosition.x + 10,
		spawnPosition.y - 33
	));
	heading.setCharacterSize(12);
	heading.setString(std::to_string(_heading));

	newHeading.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	newHeading.setPosition(sf::Vector2f(
		spawnPosition.x + 35,
		spawnPosition.y - 33
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
		spawnPosition.y - 21
	));
	altitude.setCharacterSize(12);
	altitude.setString(std::to_string(_altitude));
}

void Airplane::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	if (updateTimer.getElapsedTime().asMilliseconds() >= 700)
	{
		airplane.move(sf::Vector2f(
			sin( (_heading + 0) * PI / 180) * velocity.x,
			cos( (_heading + 180) * PI / 180) * velocity.y
		));
		sf::Vector2f airplanePosition = airplane.getPosition();

		dataStick.setPosition(sf::Vector2f(
			airplanePosition.x + 5,
			airplanePosition.y - 40
		));
		callsign.setPosition(sf::Vector2f(
			airplanePosition.x + 10,
			airplanePosition.y - 45
		));
		
		heading.setPosition(sf::Vector2f(
			airplanePosition.x + 10,
			airplanePosition.y - 33
		));
		newHeading.setPosition(sf::Vector2f(
			airplanePosition.x + 35,
			airplanePosition.y - 33
		));
		altitude.setPosition(sf::Vector2f(
			airplanePosition.x + 10,
			airplanePosition.y - 21
		));

		directionShape.setPosition(sf::Vector2f(
			airplanePosition.x + 5,
			airplanePosition.y + 5
		));

		updateTimer.restart();
	}

	HandleInternEvents();

	return;
}

void Airplane::render(sf::RenderTarget* window)
{
	window->draw(airplane);
	window->draw(dataStick);
	window->draw(callsign);
	window->draw(heading);
	window->draw(altitude);

	if (airplaneSelected)
	{
		window->draw(directionShape);
	}
	if (settingNewHeading)
	{
		window->draw(newHeading);
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (_altitude + 100 <= 40000 && altitudeChangeTimer.getElapsedTime().asMilliseconds() >= 150)
			{
				_altitude += 100;
				altitude.setString(std::to_string(_altitude));
				altitudeChangeTimer.restart();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && altitudeChangeTimer.getElapsedTime().asMilliseconds() >= 150)
		{
			if (_altitude - 100 >= 100)
			{
				_altitude -= 100;
				altitude.setString(std::to_string(_altitude));
				altitudeChangeTimer.restart();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			short x1, x2;
			short y1, y2;

			x1 = airplane.getPosition().x;
			x2 = mousePosition.x;
			y1 = airplane.getPosition().y;
			y2 = mousePosition.y;

			_newHeading = -atan2(x2-x1, y2 - y1) * 180 / PI;

			if (_newHeading < 0)
				_newHeading += 360;

			directionShape.setRotation(_newHeading - 180);
			newHeading.setString(std::to_string(_newHeading));
			
			settingNewHeading = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) == false && _newHeading != NULL)
		{
			heading.setString(std::to_string(_newHeading));
			_heading = _newHeading;

			settingNewHeading = false;
		}
	}
	else
	{
		_newHeading = NULL;
	}

	return;
}

