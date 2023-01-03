#include "Point.h"

Point::Point()
{

}

Point::Point(AssetsManager *assetsManager, const std::string name, sf::Vector2f positionFactor)
{
	this->assetsManager = assetsManager;

	point.setPosition(positionFactor.x * assetsManager->getResolution().width,
					positionFactor.y * assetsManager->getResolution().height);
	point.setFillColor(sf::Color::Transparent);
	point.setOutlineColor(sf::Color(255, 255, 255, 130));
	point.setOutlineThickness(1.5);

	pointText.setPosition( (positionFactor.x - 0.005) * assetsManager->getResolution().width,
					(positionFactor.y - 0.03) * assetsManager->getResolution().height);
	pointText.setFont(assetsManager->getFont("MerriweatherSans-Regular.ttf"));
	pointText.setString(name);
	pointText.setCharacterSize(12);
	pointText.setFillColor(sf::Color(255, 255, 255, 130));
}

void Point::render(sf::RenderTarget* window)
{
	window->draw(point);
	window->draw(pointText);
}

void Point::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;
}


