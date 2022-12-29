#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Math.h"
#include "Constants.h"
#include "AssetsManager.h"

class Airplane
{
public:
    Airplane();
    Airplane(AssetsManager assetsManager);

    void render(sf::RenderTarget *window);
    void update(sf::Vector2i mousePosition);

    void processEvents(sf::Event event);

    sf::RectangleShape airplane;

    bool isInControlArea = false;
    bool isSelected = false;
private:
    void initShapes();

    AssetsManager assetsManager;

    sf::Vector2i mousePosition;
    sf::Clock radarMovement;

    float velocity;
    float heading;
};
