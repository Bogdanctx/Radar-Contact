#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Math.h"
#include "Constants.h"
#include "AssetsManager.h"
#include "ControlArea.h"

class Airplane
{
public:
    Airplane();
    Airplane(AssetsManager *assetsManager, ControlArea controlArea);

    void render(sf::RenderTarget *window);
    void update(sf::Vector2i mousePosition);

    void processEvents(sf::Event event);

    sf::RectangleShape airplane;

    bool isInControlArea = false;
    bool isSelected = false;
private:
    void initShapes();
    void initData();

    void HandleAltitudeChange();
    void HandleAirspeedChange();
    void HandleHeadingChange();
    void UpdateData();

    AssetsManager *assetsManager;
    ControlArea controlArea;

    std::pair<short, sf::Text>airspeed;
    std::pair<short, sf::Text>altitude;
    sf::Text callsign;

    std::pair<short, sf::Text>newAirspeed;
    std::pair<short, sf::Text>newAltitude;
    std::pair<float, sf::Text>newHeading;

    std::tuple<float, sf::Text, sf::RectangleShape>heading;

    sf::Vector2i mousePosition;
    sf::Clock radarMovement,
                dataUpdate,
                altitudeChanged,
                airspeedChanged;

    float velocity;

    bool settingNewData = false;
};
