#include "Runway.h"

Runway::Runway()
{

}

Runway::Runway(AssetsManager assetsManager, sf::Vector2f position, unsigned short rotation)
{
    this->assetsManager = assetsManager;

    runway.setSize(sf::Vector2f(30, 2.7));
    runway.setFillColor(sf::Color::White);
    runway.setRotation(rotation);

    sf::FloatRect bounds = runway.getGlobalBounds();
    runway.setOrigin(sf::Vector2f(bounds.left+bounds.width/2, bounds.top + bounds.height/2));

    runway.setPosition(position);
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
