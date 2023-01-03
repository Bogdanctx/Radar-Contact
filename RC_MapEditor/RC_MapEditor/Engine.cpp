#include "Engine.h"

Engine::Engine()
{
	window.create(sf::VideoMode(1600, 900), "Radar Contact - Map editor");

	window.setFramerateLimit(60);

	assetsManager.setResolution(1600, 900);
}

void Engine::run()
{
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Engine::load(const std::string icao, const std::string airportName)
{
	if (texture.loadFromFile("../../Resources/images/" + icao + ".png"))
	{
		sprite.setTexture(texture);
		std::cout << icao + ".png has been loaded." << std::endl;

		this->icao = icao;
		this->airportName = airportName;
	}
	else
	{
		std::cout << icao + ".png could not be loaded." << std::endl;
		window.close();
	}
}

void Engine::update()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	if (pointActive)
	{
		points.back().setPosition(mousePosition.x, mousePosition.y);
	}
}

void Engine::processEvents()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					std::ofstream out("../../Resources/airports/"+icao+".airport");
					out << icao << std::endl;
					out << airportName << std::endl;
					out << points.size() << std::endl;
					for (auto it : points)
					{
						out << it.name << ' ' << (float)it.x / assetsManager.getResolution().width << ' ' << (float)it.y / assetsManager.getResolution().height << std::endl;
						std::cout << "Added: " << it.name << ' ' << (float)it.x / assetsManager.getResolution().width << ' ' << (float)it.y / assetsManager.getResolution().height << std::endl;
					}

					out.close();

					window.close();
				}
				else if (event.key.code == sf::Keyboard::P)
				{
					std::string name;
					std::cout << "Enter point name: "; std::cin >> name;

					Point point = Point(0, 0, name);

					points.push_back(point);
					pointActive = true;
				}
				else if (event.key.code == sf::Keyboard::Enter)
				{
					pointActive = false;
				}
				else if (event.key.code == sf::Keyboard::Delete)
				{
					points.pop_back();
				}
				break;
			}
			default:
				break;
		}
	}
}

void Engine::render()
{
	window.clear();

	window.draw(sprite);

	for (auto it : points)
	{
		window.draw(it.point);
	}

	window.display();
}

Engine::Point::Point()
{

}

Engine::Point::Point(float x, float y, const std::string name)
{
	point.setFillColor(sf::Color::Transparent);
	point.setOutlineColor(sf::Color::White);
	point.setOutlineThickness(1.5);
	
	this->name = name;
	this->x = x, this->y = y;
}

void Engine::Point::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;

	point.setPosition(x, y);
}
