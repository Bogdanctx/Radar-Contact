#pragma once

#include <SFML/Graphics.hpp>
#include "AssetsManager.h"
#include "Map.h"

class Airplane
{
public:
	Airplane();
	Airplane(AssetsManager* assetsManager, Map *map);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);
	void HandleClick();

private:
	void HandleInternEvents();

	void HandleHeadingChange();
	void HandleAltitudeChange();
	void HandleSpeedChange();

	void UpdateData();

	sf::RectangleShape airplane;
	sf::RectangleShape dataStick;
	sf::RectangleShape directionShape;
	sf::Vector2i mousePosition;
	sf::Clock updateTimer;

	sf::Vector2f velocity;
	int _altitude, _newAltitude, _newAltHelper;
	int _speed, _newSpeed, _newSpeedHelper;
	short _heading, _newHeading;
	unsigned short cadrans[4] = { 0, 1, 2, 3 };
	bool airplaneSelected;
	bool settingNewHeading;
	bool settingNewAltitude;
	bool settingNewSpeed;


	AssetsManager* assetsManager;
	Map* map;

	sf::Text callsign;
	sf::Text heading, newHeading;
	sf::Text altitude, newAltitude;
	sf::Text speed, newSpeed;
	std::string s_callSign;

	sf::Clock altitudeChangeTimer;
	sf::Clock speedChangeTimer;
};

