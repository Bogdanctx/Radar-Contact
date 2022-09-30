#include "Airplane.h"

#define PI 3.14159265
#define CALLSIGNS 5

Airplane::Airplane()
{

}
#include <iostream>
Airplane::Airplane(AssetsManager* assetsManager, Map *map)
{
	this->assetsManager = assetsManager;
	this->map = map;

	std::string callsigns[CALLSIGNS] = { "ROT", "KLM", "AFR", "WZZ", "TAP" };
	airplaneSelected = false;

	velocity.x = velocity.y = 1.5f;

	airplane.setSize(sf::Vector2f(10, 10));
	airplane.setFillColor(sf::Color::Transparent);
	airplane.setOutlineColor(sf::Color::White);
	airplane.setOutlineThickness(3);

	int cadran = cadrans[rand()%4];
	sf::Vector2f spawnPosition;

	spawnPosition.x = rand() % (map->airportData.cadran[cadran].x2 - map->airportData.cadran[cadran].x1) + map->airportData.cadran[cadran].x1;
	spawnPosition.y = rand() % (map->airportData.cadran[cadran].y2 - map->airportData.cadran[cadran].y1) + map->airportData.cadran[cadran].y1;

	std::cout << spawnPosition.x << ' '<< spawnPosition.y << '\n';

	if (cadran == 0)
	{
		heading = rand() % (210 - 120) + 120 + 90;
	}
	else if (cadran == 1)
	{
		heading = rand() % (330 - 210) + 180;
	}
	else if (cadran == 2)
	{
		heading = rand() % (300 - 60) + 60;
	}
	else if (cadran == 3)
	{
		heading = rand() % (150 - 30) - 30;
	}

	if (heading < 0)
		heading = -heading;

	airplane.setPosition(spawnPosition);

	s_callSign = callsigns[rand() % CALLSIGNS] + std::to_string(rand() % 9999);

	dataStick.setSize(sf::Vector2f(2, 40));
	dataStick.setPosition(sf::Vector2f(
		spawnPosition.x+5,
		spawnPosition.y - 40
	));

	airplaneCallsign.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	airplaneCallsign.setPosition(sf::Vector2f(
		spawnPosition.x + 10,
		spawnPosition.y - 45
	));
	airplaneCallsign.setCharacterSize(12);
	airplaneCallsign.setString(s_callSign);

	airplaneHeading.setFont(assetsManager->GetFont("MerriweatherSans-Regular.ttf"));
	airplaneHeading.setPosition(sf::Vector2f(
		spawnPosition.x + 10,
		spawnPosition.y - 33
	));
	airplaneHeading.setCharacterSize(12);
	airplaneHeading.setString(std::to_string(heading));

	directionShape.setSize(sf::Vector2f(2, 30));
	directionShape.setPosition(sf::Vector2f(
		spawnPosition.x + 5,
		spawnPosition.y + 5
	));
	directionShape.setFillColor(sf::Color::White);
	directionShape.setRotation(heading - 180);
}

void Airplane::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	if (updateTimer.getElapsedTime().asMilliseconds() >= 700)
	{
		airplane.move(sf::Vector2f(
			sin( (heading + 0) * PI / 180) * velocity.x,
			cos( (heading + 180) * PI / 180) * velocity.y
		));
		sf::Vector2f airplanePosition = airplane.getPosition();

		dataStick.setPosition(sf::Vector2f(
			airplanePosition.x + 5,
			airplanePosition.y - 40
		));
		airplaneCallsign.setPosition(sf::Vector2f(
			airplanePosition.x + 10,
			airplanePosition.y - 45
		));
		airplaneHeading.setPosition(sf::Vector2f(
			airplanePosition.x + 10,
			airplanePosition.y - 33
		));
		directionShape.setPosition(sf::Vector2f(
			airplanePosition.x + 5,
			airplanePosition.y + 5
		));
		directionShape.setRotation(heading - 180);

		updateTimer.restart();

	}

	return;
}

void Airplane::render(sf::RenderTarget* window)
{
	window->draw(airplane);
	window->draw(dataStick);
	window->draw(airplaneCallsign);
	window->draw(airplaneHeading);

	if (airplaneSelected)
	{
		window->draw(directionShape);
	}

	return;
}

void Airplane::HandleClick()
{
	if (airplane.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
	{
		airplaneSelected = true;
	}
	else
	{
		airplaneSelected = false;
	}

	return;
}

