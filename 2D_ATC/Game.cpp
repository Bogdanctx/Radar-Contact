#include "Game.h"
#include "Math.h"

#define GAMEMODE_TOWER 1
#define GAMEMODE_RADAR 2

Game::Game()
{
	gameWindow.create(sf::VideoMode(1200, 900), "2D - Air Traffic Controller");
	gameWindow.setFramerateLimit(60);

	initAssets();

	planeIds = 0;
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

			for (auto& _it : airplanes)
			{
				if (abs(it._altitude - _it._altitude) <= 300 && it.id != _it.id)
				{
					double distance = Math::DistanceToPoint(it.airplane.getPosition(), _it.airplane.getPosition());

					if (distance > 50.f)
						it.SetTCAS(0), _it.SetTCAS(0);
					if (distance >= 30.f && distance <= 50.f)
						it.SetTCAS(1), _it.SetTCAS(1);
					else if (distance >= 10.f && distance < 30.f)
						it.SetTCAS(2), _it.SetTCAS(2);
					else if(distance < 10.f)
						it.destroyPlane = _it.destroyPlane = 1;
				}
			}

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
			Airplane airplane = Airplane(&assetsManager, map.mapData, menu.continueGame.option);
			airplane.id = planeIds++;

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

				if (menu.draw)
				{

				}
				else
				{
					for (auto& it : airplanes)
					{
						it.HandleButtonPressed(windowEvent.key.code);
					}
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
	map = Map(assetsManager);

	creator.setString("© Made by Bogdan. (Bogdan#8334)");
	creator.setPosition(sf::Vector2f(5, 880));
	creator.setFont(assetsManager.GetFont("MerriweatherSans-Regular.ttf"));
	creator.setCharacterSize(11);

	return;
}
