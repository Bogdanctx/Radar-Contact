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

	if (menu.draw)
	{
		menu.update(mousePosition);
	}
	else
	{
		map.update(mousePosition);

		for (auto &it: airplanes) {
			it.update(mousePosition);

			if (it.destroyPlane)
			{
				airplanes.erase(
					std::remove_if(airplanes.begin(), airplanes.end(),
						[](const Airplane& airplane) {
							return airplane.destroyPlane == 1;
						}), airplanes.end()
				);
			}
		}

		if (airplanes.size() == 0 || (airplanesSpawner.getElapsedTime().asSeconds() >= 40 && airplanes.size() <= 10))
		{
			Airplane airplane = Airplane(&assetsManager, map.airportData);

			airplanes.push_back(airplane);

			airplanesSpawner.restart();
		}
	}

	return;
}

void Game::render()
{
	gameWindow.clear();

	if (menu.draw)
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

	gameWindow.draw(creator);

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
				if (menu.draw)
				{
					menu.HandleInput(windowEvent.text.unicode);
				}

				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (menu.draw)
				{
					if (windowEvent.mouseButton.button == sf::Mouse::Left)
					{
						menu.HandleClick();

						if (menu.draw == false)
						{
							map.LoadMap(menu.continueGame.option);
						}
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

	assetsManager.LoadSoundBuffer("buttonClick.wav");

	menu = Menu(assetsManager);

	creator.setString("© Made by Bogdan. (Bogdan#8334)");
	creator.setPosition(sf::Vector2f(5, 880));
	creator.setFont(assetsManager.GetFont("MerriweatherSans-Regular.ttf"));
	creator.setCharacterSize(11);

	return;
}
