#include "ControlArea.h"

ControlArea::ControlArea()
{

}

ControlArea::ControlArea(AssetsManager assetsManager)
{
	this->assetsManager = assetsManager;

	initShapes();
}

void ControlArea::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;
}

void ControlArea::render(sf::RenderTarget* window)
{
	window->draw(area);
}

void ControlArea::processEvents(sf::Event event)
{

}

void ControlArea::initShapes()
{
	area.setSize(sf::Vector2f(
		assetsManager.getResolution().width - 200,
		assetsManager.getResolution().height - 150
	));

	area.setFillColor(sf::Color::Transparent);
	area.setOutlineColor(sf::Color(255, 255, 255, 150));
	area.setOutlineThickness(2.5);

	sf::FloatRect bounds = area.getGlobalBounds();
	area.setOrigin(sf::Vector2f(
		bounds.left + bounds.width / 2,
		bounds.top + bounds.height / 2
	));
	area.setPosition(sf::Vector2f(
		assetsManager.getResolution().width / 2,
		assetsManager.getResolution().height / 2
	));
}

bool ControlArea::isInArea(sf::Vector2f position)
{
    return area.getGlobalBounds().contains(position) == true;
}
