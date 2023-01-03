#include "Engine.h"
#include "Math.h"
#include "Constants.h"

Engine::Engine()
{
	initAssets();

    sf::ContextSettings settings;


	if(std::filesystem::exists("../Resources/settings.txt"))
    {
        std::ifstream in("../Resources/settings.txt");

        unsigned short fps, antialiasing;
        in>>fps>>antialiasing;
        in.close();

        settings.antialiasingLevel = antialiasing;
        window.setFramerateLimit(60);
    }

	window.create(sf::VideoMode(assetsManager.getResolution().width, assetsManager.getResolution().height),
				"2D - Air Traffic Controller",
				sf::Style::Titlebar | sf::Style::Close,
				settings);

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

	window.draw(creator);

	window.display();

	return;
}
#include <iostream>

void Engine::processEvents()
{
	sf::Event windowEvent;

	sf::Vector2i mousepos = sf::Mouse::getPosition(window);

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
                    std::cout<<(float)mousepos.x / assetsManager.getResolution().width<<' '<<(float)mousepos.y / assetsManager.getResolution().height<<'\n';
					if (menu.__settings.settingsApplied == true)
					{
					    window.close();

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

	assetsManager.setResolution(1600, 900);

	menu = Menu(assetsManager);
	game = Game(assetsManager);

	creator.setString("© Made by Bogdan. (Bogdan#8334)");
	creator.setPosition(sf::Vector2f(5, assetsManager.getResolution().height-20));
	creator.setFont(assetsManager.getFont("MerriweatherSans-Regular.ttf"));
	creator.setCharacterSize(11);

	return;
}
