#include "Engine.h"
#include "Math.h"
#include "Constants.h"

Engine::Engine()
{
	initAssets();

	window.create(sf::VideoMode(assetsManager.getResolution().width, assetsManager.getResolution().height), "2D - Air Traffic Controller");
	window.setFramerateLimit(60);
}

void Engine::run()
{
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}

	return;
}

void Engine::update()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	if (menu.isActive)
	{
		menu.update(mousePosition);
	}
	else if (game.isActive)
	{
		game.update(mousePosition);
	}

	return;
}

void Engine::render()
{
	window.clear();

	if (menu.isActive)
	{
		menu.render(&window);
	}
	else if (game.isActive)
	{
		game.render(&window);
	}

	window.display();

	return;
}


void Engine::processEvents()
{
	sf::Event windowEvent;

	while (window.pollEvent(windowEvent))
	{
		switch (windowEvent.type)
		{
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (windowEvent.mouseButton.button == sf::Mouse::Left)
				{
					if (menu.__settings.settingsApplied == true)
					{
						window.setFramerateLimit(menu.__settings.fps.sliderValue);

					}
				}
			}

			case sf::Event::KeyPressed:
            {
                if(windowEvent.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                break;
            }

			default:
				break;
		}

		if (menu.isActive)
		{
			menu.processEvents(windowEvent);

			if (menu.__play.handler.airportSelected == true)
			{
				game.isActive = true;
				menu.isActive = false;

				game.map.load(menu.__play.handler.airportIcao);
			}
		}
		else if (game.isActive)
		{
			game.processEvents(windowEvent);
		}

	}

	return;
}

void Engine::initAssets()
{
	assetsManager.loadFont("Comfortaa-Regular.ttf");
	assetsManager.loadFont("MerriweatherSans-Regular.ttf");
	assetsManager.loadFont("Rajdhani-Regular.ttf");

	assetsManager.loadTexture("menuBackground.png", "../Resources/images");

	assetsManager.loadSoundBuffer("buttonClick.wav");

    assetsManager.setResolution(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

	menu = Menu(assetsManager);
	game = Game(assetsManager);

	creator.setString("© Made by Bogdan. (Bogdan#8334)");
	creator.setPosition(sf::Vector2f(5, assetsManager.getResolution().height-20));
	creator.setFont(assetsManager.getFont("MerriweatherSans-Regular.ttf"));
	creator.setCharacterSize(11);

	return;
}
