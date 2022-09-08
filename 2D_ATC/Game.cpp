#include "Game.h"

Game::Game()
{
	gameWindow.create(sf::VideoMode(1200, 900), "2D - Air Traffic Controller");

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
	processEvents();
	menu.update();

	return;
}

void Game::render()
{
	gameWindow.clear();

	menu.render(&gameWindow);
	map.render(&gameWindow);

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
