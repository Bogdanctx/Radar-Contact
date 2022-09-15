#include "Game.h"

Game::Game()
{
	gameWindow.create(sf::VideoMode(1200, 900), "2D - Air Traffic Controller");
	gameWindow.setFramerateLimit(60);

	initTextures();
	initSprites();

	map.GenerateNewMap();
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
				menu.HandleInput(windowEvent.text.unicode);

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

void Game::initTextures()
{

	return;
}

void Game::initSprites()
{

	return;
}
