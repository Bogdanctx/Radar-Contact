#include "Game.h"

Game::Game()
{
	gameWindow.create(sf::VideoMode(1200, 900), "2D - Air Traffic Controller");
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

	if (menu.drawMenu)
	{
		menu.update(mousePosition);
	
		if (menu.career.isCareerCreated() && menu.drawMenu == true)
		{
			playerName = menu.career._playerName;
			country = menu.career.selectedMap;
			position = menu.career.atcPosition;

			menu.drawMenu = false;

			map.GenerateMap(country, position);
		}
	}
	else
	{
		map.update(mousePosition);
	}

	return;
}

void Game::render()
{
	gameWindow.clear();

	if (menu.drawMenu)
	{
		menu.render(&gameWindow);
	}
	else
	{
		map.render(&gameWindow);
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
			case sf::Event::KeyPressed:
			{
				if (windowEvent.key.code == sf::Keyboard::Escape)
				{
					gameWindow.close();
				}
				break;
			}
			case sf::Event::TextEntered:
			{
				if (menu.drawMenu)
				{
					menu.HandleInput(windowEvent.text.unicode);
				}

				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (menu.drawMenu)
				{
					if (windowEvent.mouseButton.button == sf::Mouse::Left)
					{
						menu.HandleClick();
					}
				}
			}
			default:
				break;
		}
	}

	return;
}

void Game::initAssets()
{
	assetsManager.LoadFont("Comfortaa-Regular.ttf");
	assetsManager.LoadFont("MerriweatherSans-Regular.ttf");

	assetsManager.LoadTexture("menu.png", "../Resources/images/menu");

	assetsManager.LoadSoundBuffer("buttonClick.wav");

	menu = Menu(&assetsManager);

	return;
}
