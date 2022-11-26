#pragma once

#include <SFML/Graphics.hpp>
#include "AssetsManager.h"
#include "Map.h"
#include "Path.h"

class Airplane
{
public:
	Airplane();
	Airplane(AssetsManager *assetsManager, Map::MapData mapData, unsigned short gamemode);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);
	void HandleClick();
	void HandleButtonPressed(sf::Keyboard::Key key);

	unsigned short _altitude;
	unsigned long long id;
	bool destroyPlane;

	void SetTCAS(unsigned short level);

	sf::RectangleShape airplane;

private:
	void initText();

	void HandleInternEvents();

	void HandleHeadingChange();
	void HandleAltitudeChange();
	void HandleSpeedChange();

	void UpdateData();
	void CheckLanding();
	void CreateAirplane();
	void GenerateRoute();
	void CheckNode();

	sf::RectangleShape dataStick;
	sf::RectangleShape directionShape;
	sf::Vector2i mousePosition;
	sf::Clock updateTimer;

	sf::Vector2f spawnPosition;

	sf::Vector2f velocity;
	
	unsigned short gamemode;

	unsigned short _newAltitude;
	unsigned short _speed, _newSpeed;
	short _heading, _newHeading;

	bool airplaneSelected;
	bool settingNewHeading;
	bool settingNewAltitude;
	bool settingNewSpeed;

	bool altitudeUpdated;
	bool speedUpdated;

	bool headingFixed;

	unsigned short randomChoice;

	AssetsManager *assetsManager;
	Map::MapData mapData;
	Path route;

	sf::Text callsign;
	sf::Text heading, newHeading;
	sf::Text altitude, newAltitude;
	sf::Text speed, newSpeed;
	std::string s_callSign;

	sf::Clock altitudeChangeTimer;
	sf::Clock speedChangeTimer;
};

