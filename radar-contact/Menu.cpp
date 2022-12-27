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
<<<<<<< Updated upstream
	{
		__settings.update(mousePosition);
	}
	else if (__play.isActive)
	{
=======
	{
		__settings.update(mousePosition);
	}
	else if (__play.isActive)
	{
>>>>>>> Stashed changes
		__play.update(mousePosition);
	}

}

void Menu::render(sf::RenderTarget* window)
{
	window->draw(background);

	window->draw(leftCard);
	window->draw(gameTitle);
<<<<<<< Updated upstream
	
=======

>>>>>>> Stashed changes
	play.render(window);
	settings.render(window);

	if (__settings.isActive)
	{
		__settings.render(window);
	}
	else if (__play.isActive)
	{
		__play.render(window);
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
<<<<<<< Updated upstream
	leftCard.setSize(sf::Vector2f(350, WINDOW_HEIGHT));
=======
	leftCard.setSize(sf::Vector2f(0.25*assetsManager.getResolution().width,
                               assetsManager.getResolution().height));
>>>>>>> Stashed changes
}

void Menu::initObjects()
{
<<<<<<< Updated upstream
	play = Button(sf::Vector2f(350, 80), sf::Vector2f(0, 200));
=======
	play = Button(sf::Vector2f(0.25*assetsManager.getResolution().width, 80), sf::Vector2f(0, 200));
>>>>>>> Stashed changes
	play.setText(&assetsManager.getFont("Rajdhani-Regular.ttf"), "Play");
	play.setDefaultColor(sf::Color::Transparent);
	play.setHoverColor(sf::Color(93, 95, 97, 100));
	play.centerText();

<<<<<<< Updated upstream
	settings = Button(sf::Vector2f(350, 80), sf::Vector2f(0, 280));
=======
	settings = Button(sf::Vector2f(0.25*assetsManager.getResolution().width, 80), sf::Vector2f(0, 280));
>>>>>>> Stashed changes
	settings.setText(&assetsManager.getFont("Rajdhani-Regular.ttf"), "Setting");
	settings.setDefaultColor(sf::Color::Transparent);
	settings.setHoverColor(sf::Color(93, 95, 97, 100));
	settings.centerText();

	__settings = Settings(assetsManager);
	__play = Play(assetsManager);
}

void Menu::processEvents(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (__settings.isActive)
				{
					__settings.processEvents(event);
				}
				else if (__play.isActive)
				{
					__play.processEvents(event);
				}

				if (play.isButtonClicked(mousePosition))
				{
					__play.isActive = true;
				}

				if (settings.isButtonClicked(mousePosition))
				{
					__settings.isActive = true;
				}
			}

			break;
		}
		default:
			break;
	}
<<<<<<< Updated upstream
}
=======
}
>>>>>>> Stashed changes
