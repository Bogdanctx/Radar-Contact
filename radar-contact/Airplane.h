#pragma once

#include <SFML/Graphics.hpp>
#include "AssetsManager.h"

class Airplane
{
public:
    Airplane();
    Airplane(AssetsManager assetsManager);

    void render(sf::RenderTarget *window);
    void update(sf::Vector2i mousePosition);

    void processEvents(sf::Event event);

    sf::RectangleShape body;
private:
    void initShapes();

    AssetsManager assetsManager;
    sf::Vector2i mousePosition;

};
