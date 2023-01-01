#include "Runway.h"

Runway::Runway()
{

}

Runway::Runway(AssetsManager *assetsManager)
{
	this->assetsManager = assetsManager;

	runway.setSize(sf::Vector2f(30, 2.7));
	runway.setFillColor(sf::Color::White);

	sf::FloatRect bounds = runway.getGlobalBounds();
	runway.setOrigin(sf::Vector2f(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2));

	runway.setPosition(5, 5);

	heading_text.setFont(assetsManager->getFont("MerriweatherSans-Regular.ttf"));
	heading_text.setCharacterSize(15);
}

void Runway::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	if (isSelected)
	{
		setPosition(sf::Vector2f(mousePosition.x, mousePosition.y));
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			setRotation(-1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			setRotation(1);
		}
	}
}

void Runway::render(sf::RenderTarget* window)
{
	window->draw(runway);
	window->draw(heading_text);
}

void Runway::processEvent(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (runway.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
				{
					isSelected = true;
				}
			}
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				isSelected = false;
				factor.x = runway.getPosition().x / assetsManager->getResolution().width;
				factor.y = runway.getPosition().y / assetsManager->getResolution().height;
			}

			break;
		}
		default:
			break;
	}
}

void Runway::setPosition(sf::Vector2f position)
{
	runway.setPosition(position);
	heading_text.setPosition(position.x - 40, position.y - 20);
}

void Runway::setRotation(int rotation)
{
	runway.setRotation(runway.getRotation() + rotation);

	heading = runway.getRotation() - 90;
	if (heading < 0)
		heading += 360;

	heading_text.setString(std::to_string(heading)+"°");
}