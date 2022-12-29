#include "Settings.h"

Settings::Settings()
{

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

                    std::ofstream out("../Resources/settings.txt");
                    out<<fps.sliderValue<<std::endl;
                    out<<antialiasing.sliderValue<<std::endl;
                    out.close();
				}
			}
			break;
		}
		default:
            break;
	}
}

void Settings::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	fps.update(mousePosition);
	antialiasing.update(mousePosition);
	apply.update(mousePosition);
}

void Settings::render(sf::RenderTarget* window)
{
	fps.render(window);
	antialiasing.render(window);
	apply.render(window);
}

void Settings::initObjects()
{
	fps.setSize(300, 12);
	fps.setName("FPS", 20);
	fps.setPosition(sf::Vector2f(assetsManager.getResolution().width*0.30, assetsManager.getResolution().height*0.1));
	fps.setBounds(10, 60);
	fps.setFont(&assetsManager.getFont("Rajdhani-Regular.ttf"));

	antialiasing.setSize(300, 12);
    antialiasing.setName("Antialiasing", 20);
	antialiasing.setPosition(sf::Vector2f(assetsManager.getResolution().width*0.30, assetsManager.getResolution().height*0.2));
    antialiasing.setBounds(1, 8);
    antialiasing.setFont(&assetsManager.getFont("Rajdhani-Regular.ttf"));

	apply = Button(sf::Vector2f(300, 50), sf::Vector2f(assetsManager.getResolution().width*0.30, assetsManager.getResolution().height*0.90));
	apply.setDefaultColor(sf::Color(50, 50, 50));
	apply.setText(&assetsManager.getFont("Rajdhani-Regular.ttf"), "APPLY");
	apply.setCharSize(30);
	apply.centerText();
	apply.setBorder(1);
}
