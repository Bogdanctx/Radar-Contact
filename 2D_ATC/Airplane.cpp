#include "Airplane.h"

#define PI 3.14159265
#define CALLSIGNS 5

Airplane::Airplane()
{

}

Airplane::Airplane(AssetsManager* assetsManager)
{
	this->assetsManager = assetsManager;

	std::string callsigns[CALLSIGNS] = { "ROT", "KLM", "AFR", "WZZ", "TAP" };

	velocity.x = velocity.y = 1.5f;

	airplane.setSize(sf::Vector2f(10, 10));
	airplane.setFillColor(sf::Color::Transparent);
	airplane.setOutlineColor(sf::Color::White);
	airplane.setOutlineThickness(3);

	int cadran = cadrans[rand()%4];
	sf::Vector2f spawnPosition;

	if (cadran == 0)
	{
		spawnPosition.x = rand() % (1200-1000) + 1000;
		spawnPosition.y = rand() % (870 - 20) + 20;
		heading = rand() % (270 - 90) + 90;
	}
	else if (cadran == 1)
	{
		spawnPosition.x = rand() % (1180 - 20) + 20;
		spawnPosition.y = rand() % (200 - 15) + 15;
		heading = rand() % (360 - 180) + 180;
		
	}
	else if (cadran == 2)
	{
		spawnPosition.x = rand() % (125 - 5) + 5;
		spawnPosition.y = rand() % (870 - 20) + 20;
		heading = rand() % (270 - 90) + 180;
		
	}
	else if (cadran == 3)
	{
		spawnPosition.x = rand() % (1200 - 1000) + 1000;
		spawnPosition.y = rand() % (880 - 730) + 730;
		heading = rand() % 180;
	}

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
}

void Airplane::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	if (updateTimer.getElapsedTime().asMilliseconds() >= 700)
	{
		airplane.move(sf::Vector2f(
			sin((PI/180) * (heading + 90)) * velocity.x,
			cos((PI / 180) * (heading + 90)) * velocity.y
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

	return;
}

