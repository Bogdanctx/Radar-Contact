#include "Runway.h"

Runway::Runway()
{

}

Runway::Runway(AssetsManager assetsManager, sf::Vector2f positionFactor, unsigned short rotation)
{
    this->assetsManager = assetsManager;

    runway.setSize(sf::Vector2f(100, ));
    runway.setFillColor(sf::Color::White);
    runway.setRotation(rotation+90);

    sf::FloatRect bounds = runway.getGlobalBounds();
    runway.setOrigin(sf::Vector2f(bounds.left+bounds.width/2, bounds.top + bounds.height/2));

    runway.setPosition(sf::Vector2f(
        positionFactor.x,
        positionFactor.y
    ));
}

void Runway::render(sf::RenderTarget *window)
{
    window->draw(runway);
}

void Runway::update(sf::Vector2i mousePosition)
{
    this->mousePosition = mousePosition;
}

void Runway::processEvents(sf::Event event)
{
    switch(event.type)
    {
        default:
            break;
    }
}
