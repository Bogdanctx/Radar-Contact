#include "Engine.h"
#include "Math.h"
#include "Constants.h"

Engine::Engine()
{
	createWindow();

	initAssets();
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

void Engine::createWindow()
{
	sf::ContextSettings settings;
	unsigned short fps, antialiasing;
	unsigned short width, height;

	fps = 60;
	antialiasing = 8;
	width = 1600;
	height = 900;


	if (std::filesystem::exists("../Resources/settings.txt"))
	{
		std::ifstream in("../Resources/settings.txt");

		in >> fps;
		in>>antialiasing;
		in >> width >> height;

		in.close();

		settings.antialiasingLevel = antialiasing;
	}

	assetsManager.setResolution(width, height);

	window.create(sf::VideoMode(width, height),
		"Radar Contact",
		sf::Style::Close,
		settings);

	window.setFramerateLimit(fps);

	initAssets();
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

void Engine::processEvents()
{
	sf::Event windowEvent;

	sf::Vector2i mousepos = sf::Mouse::getPosition(window);

	while (window.pollEvent(windowEvent))
	{
		if (menu.isActive)
		{
			menu.processEvents(windowEvent);

			if (menu.__play.handler.airportSelected == true)
			{
				game.isActive = true;
				menu.isActive = false;

				game.map.load(menu.__play.handler.airportIcao);
			}

			if (windowEvent.mouseButton.button == sf::Mouse::Left)
			{
				if (menu.__settings.apply.isButtonClicked(mousepos))
				{
					window.close();

					createWindow();
				}
			}
		}
		else if (game.isActive)
		{
			game.processEvents(windowEvent);
		}

		switch (windowEvent.type)
		{
			case sf::Event::Closed:
			{
				window.close();
				break;
			}

			default:
				break;
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

	menu = Menu(assetsManager);
	game = Game(assetsManager);

	creator.setString("© Made by Bogdan. (Bogdan#8334)");
	creator.setPosition(sf::Vector2f(5, assetsManager.getResolution().height-20));
	creator.setFont(assetsManager.getFont("MerriweatherSans-Regular.ttf"));
	creator.setCharacterSize(11);

	return;
}
