#include "Play.h"

Play::Play()
{

}

Play::Play(AssetsManager assetsManager)
{
	this->assetsManager = assetsManager;

	isActive = false;
	handler.first = false;

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
					if (it.first.isButtonClicked(mousePosition))
					{
						handler.first = 1;
						handler.second = it.second;
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
		it.first.update(mousePosition);
	}
}

void Play::render(sf::RenderTarget* window)
{
	for (auto it : airportsList)
	{
		it.first.render(window);
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

		std::pair<Button, std::string>t;

<<<<<<< Updated upstream
		t.first = Button(sf::Vector2f(280, 60), sf::Vector2f(380, 60 * (airportsList.size()+1)));
=======
		t.first = Button(sf::Vector2f(280, 60), sf::Vector2f(assetsManager.getResolution().width*0.30, 60 * (airportsList.size()+1)));
>>>>>>> Stashed changes

		t.first.setText(&assetsManager.getFont("Rajdhani-Regular.ttf"), airportIcao+" ("+airportName+")");
		t.first.setCharSize(28);
		t.first.centerText();
		t.first.setDefaultColor(sf::Color(42, 42, 42));
		t.first.setHoverColor(sf::Color(93, 95, 97, 100));

		t.second = airportIcao;

		airportsList.push_back(t);
<<<<<<< Updated upstream

	}
}
=======
	}
}
>>>>>>> Stashed changes
