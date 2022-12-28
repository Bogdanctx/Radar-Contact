#include "Play.h"

Play::Play()
{

}

Play::Play(AssetsManager assetsManager)
{
	this->assetsManager = assetsManager;

	isActive = false;

	initObjects();
}

void Play::processEvents(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				for (auto it : airportsList)
				{
					if (it.button.isButtonClicked(mousePosition))
					{
						handler.airportSelected = true;
						handler.airportIcao = it.airportName;
						isActive = false;
						break;
					}
				}
			}

		}
	}
}

void Play::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	for (auto &it : airportsList)
	{
		it.button.update(mousePosition);
	}
}

void Play::render(sf::RenderTarget* window)
{
	for (auto it : airportsList)
	{
		it.button.render(window);
	}
}

void Play::initObjects()
{
	std::string path = "../Resources/airports";

	for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
	{
		std::ifstream in(entry.path());
		std::string airportIcao, airportName;

		std::getline(in, airportIcao);
		std::getline(in, airportName);

		Airport airport;

		airport.button = Button(sf::Vector2f(280, 60), sf::Vector2f(assetsManager.getResolution().width*0.30, 60 * (airportsList.size()+1)));

		airport.button.setText(&assetsManager.getFont("Rajdhani-Regular.ttf"), airportIcao+" ("+airportName+")");
		airport.button.setCharSize(28);
		airport.button.centerText();
		airport.button.setDefaultColor(sf::Color(42, 42, 42));
		airport.button.setHoverColor(sf::Color(93, 95, 97, 100));

		airport.airportName = airportIcao;

		airportsList.push_back(airport);
	}
}
