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

			map.LoadMap(country, position);
		}
	}
	else
	{
		map.update(mousePosition);

		for (auto& it: airplanes ) {
			it.update(mousePosition);
		}

		SummonNewAirplane();
	}

	return;
}

void Game::SummonNewAirplane()
{
	if (menu.drawMenu == false)
	{
		if (airplanesSpawner.getElapsedTime().asSeconds() >= 5)
		{
			int chance = rand() % 101;

			if (chance >= 70)
			{
				Airplane airplane = Airplane(&assetsManager, &map, airplanes.size());

				airplanes.push_back(airplane);
				airplanesSpawner.restart();
			}
		}
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

		for (auto it : airplanes)
		{
			it.render(&gameWindow);
		}
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
				else
				{
					if (windowEvent.mouseButton.button == sf::Mouse::Left)
					{
						for (auto &it : airplanes)
						{
							it.HandleClick();
						}
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

	assetsManager.LoadTexture("romania.png", "../Resources/images/flags");

	assetsManager.LoadTexture("romaniaGround.png", "../Resources/images/maps/romania");
	assetsManager.LoadTexture("romaniaRadar.png", "../Resources/images/maps/romania");

	assetsManager.LoadSoundBuffer("buttonClick.wav");

	menu = Menu(&assetsManager);
	map = Map(&assetsManager);

	return;
}
