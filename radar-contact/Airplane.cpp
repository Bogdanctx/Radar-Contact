#include "Airplane.h"

Airplane::Airplane()
{

}

Airplane::Airplane(AssetsManager assetsManager)
{
    this->assetsManager = assetsManager;

    initShapes();


}

void Airplane::render(sf::RenderTarget *window)
{
    window->draw(body);
}

void Airplane::update(sf::Vector2i mousePosition)
{
    this->mousePosition = mousePosition;
}

void Airplane::processEvents(sf::Event event)
{

}

void Airplane::initShapes()
{
    body.setSize(sf::Vector2f(8, 8));
    body.setFillColor(sf::Color::Transparent);
    body.setOutlineColor(sf::Color::White);
    body.setOutlineThickness(2);

    body.setPosition(sf::Vector2f(rand() % assetsManager.getResolution().width, rand() % assetsManager.getResolution().height));
}
