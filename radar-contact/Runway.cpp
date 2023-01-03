#include "Runway.h"

Runway::Runway()
{

}

Runway::Runway(AssetsManager assetsManager, sf::Vector2f positionScale, unsigned short rotation, float length)
{
    this->assetsManager = assetsManager;

    runway.setSize(sf::Vector2f(length, 4));
    runway.setFillColor(sf::Color::White);

    sf::FloatRect bounds = runway.getGlobalBounds();
    runway.setOrigin(sf::Vector2f(bounds.left+bounds.width/2, bounds.top + bounds.height/2));

    runway.setRotation(rotation+90);
    runway.setPosition(positionScale.x * assetsManager.getResolution().width, positionScale.y*assetsManager.getResolution().height);
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
