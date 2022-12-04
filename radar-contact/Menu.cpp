#include "Menu.h"

Menu::Menu()
{

}

Menu::Menu(AssetsManager assetsManager)
{
	this->assetsManager = assetsManager;

	isActive = true;

	initSprites();
	initTexts();
	initShapes();
	initObjects();
}

void Menu::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	play.update(mousePosition);
	settings.update(mousePosition);

	if (__settings.isActive)
	{
		__settings.update(mousePosition);
	}

}

void Menu::render(sf::RenderTarget* window)
{
	window->draw(background);

	window->draw(leftCard);
	window->draw(gameTitle);
	
	play.render(window);
	settings.render(window);

	if (__settings.isActive)
	{
		__settings.render(window);
	}
}


void Menu::initSprites()
{
	background.setTexture(assetsManager.getTexture("menuBackground.png"));
}

void Menu::initTexts()
{
	gameTitle.setString("RADAR CONTACT");
	gameTitle.setFont(assetsManager.getFont("Rajdhani-Regular.ttf"));
	gameTitle.setCharacterSize(38);
	gameTitle.setPosition(sf::Vector2f(50, 20));
}

void Menu::initShapes()
{
	leftCard.setFillColor(sf::Color(30, 30, 30, 180));
	leftCard.setSize(sf::Vector2f(350, WINDOW_HEIGHT));
}

void Menu::initObjects()
{
	play = Button(sf::Vector2f(350, 80), sf::Vector2f(0, 200));
	play.setText(&assetsManager.getFont("Rajdhani-Regular.ttf"), "Play");
	play.setDefaultColor(sf::Color::Transparent);
	play.setHoverColor(sf::Color(93, 95, 97, 100));
	play.centerText();

	settings = Button(sf::Vector2f(350, 80), sf::Vector2f(0, 280));
	settings.setText(&assetsManager.getFont("Rajdhani-Regular.ttf"), "Setting");
	settings.setDefaultColor(sf::Color::Transparent);
	settings.setHoverColor(sf::Color(93, 95, 97, 100));
	settings.centerText();

	__settings = Settings(assetsManager);
}

void Menu::processEvents(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
		{
			if (play.isButtonClicked(mousePosition))
			{
				
			}

			if (settings.isButtonClicked(mousePosition))
			{
				__settings.isActive = true;
			}

		}
		default:
			break;
	}
}