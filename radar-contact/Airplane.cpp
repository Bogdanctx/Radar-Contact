#include "Airplane.h"

Airplane::Airplane()
{

}
#include <iostream>
Airplane::Airplane(AssetsManager assetsManager)
{
    this->assetsManager = assetsManager;

    initShapes();


    unsigned short screenSpawn = rand() % 4;
    switch(screenSpawn)
    {
        case 0: // upper screen
        {
            airplane.setPosition(rand() % assetsManager.getResolution().width, 0);
            break;
        }
        case 1: // left screen
        {
            airplane.setPosition(0, rand() % assetsManager.getResolution().height);
            break;
        }
        case 2: // bottom screen
        {
            airplane.setPosition(rand() % assetsManager.getResolution().width, assetsManager.getResolution().height);
            break;
        }
        case 3:
        {
            airplane.setPosition(assetsManager.getResolution().width, rand() % assetsManager.getResolution().height);
            break;
        }
    }
    velocity = (float)(rand() % 200 + 100)/100;
    heading = Math::DirectionToPoint(airplane.getPosition(), sf::Vector2f(assetsManager.getResolution().width/2, assetsManager.getResolution().height/2));
}

void Airplane::render(sf::RenderTarget *window)
{
    window->draw(airplane);
}

void Airplane::update(sf::Vector2i mousePosition)
{
    this->mousePosition = mousePosition;

    if(radarMovement.getElapsedTime().asMilliseconds() >= 700)
    {
        airplane.move(sf::Vector2f(
			sin((heading + 0) * PI / 180) * velocity,
			cos((heading + 180) * PI / 180) * velocity
		));

		radarMovement.restart();
    }
}

void Airplane::processEvents(sf::Event event)
{

}

void Airplane::initShapes()
{
    airplane.setSize(sf::Vector2f(8, 8));
    airplane.setFillColor(sf::Color::Transparent);
    airplane.setOutlineColor(sf::Color::White);
    airplane.setOutlineThickness(2);
}
