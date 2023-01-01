#include "Engine.h"

Engine::Engine()
{
	initAssets();

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window.create(sf::VideoMode(assetsManager.getResolution().width, assetsManager.getResolution().height),
		"Radar Contact - Level Editor",
		sf::Style::Titlebar | sf::Style::Close, settings);
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

void Engine::load(std::string icao, std::string airportName)
{
	if (texture.loadFromFile("../../Resources/images/" + icao + ".png"))
	{
		std::cout << icao << ".png has been loaded.\n";

		sprite.setTexture(texture);

		sprite.setScale(sf::Vector2f(
			(float)assetsManager.getResolution().width / texture.getSize().x,
			(float)assetsManager.getResolution().height / texture.getSize().y
		));

		out = std::ofstream("../../Resources/airports/"+icao + ".airport");
		out << icao << std::endl;
		out << airportName << std::endl;
	}
	else
	{
		std::cout << icao << ".png could not be loaded.\n";
	}
}

void Engine::update()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	for (auto& it : runways)
	{
		it.update(mousePosition);
	}

	return;
}

void Engine::render()
{
	window.clear();

	window.draw(sprite);

	for (auto it : runways)
	{
		it.render(&window);
	}

	window.display();

	return;
}


void Engine::processEvents()
{
	sf::Event windowEvent;

	sf::Vector2i mousePosition;

	mousePosition = sf::Mouse::getPosition(window);

	while (window.pollEvent(windowEvent))
	{
		switch (windowEvent.type)
		{
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			case sf::Event::KeyPressed:
			{
				if (windowEvent.key.code == sf::Keyboard::Escape)
				{
					out << runways.size() << std::endl;
					for (auto it : runways)
					{
						out << it.factor.x << ' ' << it.factor.y << ' ' << it.heading << std::endl;
					}

					window.close();
				}
				else if (windowEvent.key.code == sf::Keyboard::R)
				{
					Runway runway = Runway(&assetsManager);

					runways.push_back(runway);
					
				}
				else if (windowEvent.key.code == sf::Keyboard::Delete)
				{
					runways.pop_back();
				}

				break;
			}
			case sf::Event::MouseButtonPressed:
			{

				for (auto& it : runways)
				{
					it.processEvent(windowEvent);
				}

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
	assetsManager.setResolution(sf::VideoMode::getDesktopMode().width - 100, sf::VideoMode::getDesktopMode().height - 100);

	assetsManager.loadFont("MerriweatherSans-Regular.ttf");
}