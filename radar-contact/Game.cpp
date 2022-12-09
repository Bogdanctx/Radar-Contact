#include "Game.h"
#include "Math.h"
#include "Constants.h"

Game::Game()
{
	gameWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "2D - Air Traffic Controller");
	gameWindow.setFramerateLimit(60);

	initAssets();
}

void Game::run()
{
	while (gameWindow.isOpen())
	{
		processEvents();
		update();
		render();
	}

	return;
}

void Game::update()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(gameWindow);

	if (menu.isActive)
	{
		menu.update(mousePosition);
	}

	return;
}

void Game::render()
{
	gameWindow.clear();

	if (menu.isActive)
	{
		menu.render(&gameWindow);
	}

	gameWindow.display();

	return;
}


void Game::processEvents()
{
	sf::Event windowEvent;

	while (gameWindow.pollEvent(windowEvent))
	{
		switch (windowEvent.type)
		{
			case sf::Event::Closed:
			{
				gameWindow.close();
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (windowEvent.mouseButton.button == sf::Mouse::Left)
				{
					if (menu.__settings.settingsApplied == true)
					{
						gameWindow.setFramerateLimit(menu.__settings.fps.sliderValue);
					}
				}
			}
			
			default:
				break;
		}

		if (menu.isActive)
		{
			menu.processEvents(windowEvent);
		}


	}

	return;
}

void Game::initAssets()
{
	assetsManager.loadFont("Comfortaa-Regular.ttf");
	assetsManager.loadFont("MerriweatherSans-Regular.ttf");
	assetsManager.loadFont("Rajdhani-Regular.ttf");

	assetsManager.loadTexture("menuBackground.png", "../Resources/images");

	assetsManager.loadSoundBuffer("buttonClick.wav");

	menu = Menu(assetsManager);

	creator.setString("© Made by Bogdan. (Bogdan#8334)");
	creator.setPosition(sf::Vector2f(5, WINDOW_HEIGHT-20));
	creator.setFont(assetsManager.getFont("MerriweatherSans-Regular.ttf"));
	creator.setCharacterSize(11);

	return;
}
