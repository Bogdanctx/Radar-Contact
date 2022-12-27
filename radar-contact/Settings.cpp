#include "Settings.h"

Settings::Settings()
{
<<<<<<< Updated upstream
	
=======

>>>>>>> Stashed changes
}

Settings::Settings(AssetsManager assetsManager)
{
	this->assetsManager = assetsManager;

	isActive = false;
	settingsApplied = false;

	initObjects();
}

void Settings::processEvents(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (apply.isButtonClicked(mousePosition))
				{
					this->isActive = false;
					settingsApplied = true;
				}
			}
		}
	}
}

void Settings::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	fps.update(mousePosition);
	apply.update(mousePosition);
}

void Settings::render(sf::RenderTarget* window)
{
	fps.render(window);
	apply.render(window);
}

void Settings::initObjects()
{
	fps.setSize(300, 12);
<<<<<<< Updated upstream
	fps.setPosition(sf::Vector2f(400, 100));
=======
	fps.setPosition(sf::Vector2f(assetsManager.getResolution().width*0.30, assetsManager.getResolution().height*0.1));
>>>>>>> Stashed changes
	fps.setBounds(10, 60);
	fps.setFont(&assetsManager.getFont("Rajdhani-Regular.ttf"));
	fps.setName("FPS", 20);

<<<<<<< Updated upstream
	apply = Button(sf::Vector2f(300, 50), sf::Vector2f(400, WINDOW_HEIGHT - 100));
=======
	apply = Button(sf::Vector2f(300, 50), sf::Vector2f(assetsManager.getResolution().width*0.30, assetsManager.getResolution().height*0.90));
>>>>>>> Stashed changes
	apply.setDefaultColor(sf::Color(50, 50, 50));
	apply.setText(&assetsManager.getFont("Rajdhani-Regular.ttf"), "APPLY");
	apply.setCharSize(30);
	apply.centerText();
	apply.setBorder(1);
<<<<<<< Updated upstream
}
=======
}
>>>>>>> Stashed changes
