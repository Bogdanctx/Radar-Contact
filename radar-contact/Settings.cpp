#include "Settings.h"

Settings::Settings()
{

}

Settings::Settings(AssetsManager assetsManager)
{
	this->assetsManager = assetsManager;

	isActive = false;

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

                    std::ofstream out("../Resources/settings.txt");
                    out<<fps.sliderValue<<std::endl;
                    out<<antialiasing.sliderValue<<std::endl;
					
					if (resolutionSelected == "1024x576")
						out << 1024 << ' ' << 576 << std::endl;
					else if (resolutionSelected == "1280x720")
						out << 1280 << ' ' << 720 << std::endl;
					else if (resolutionSelected == "1366x768")
						out << 1366 << ' ' << 768 << std::endl;
					else if (resolutionSelected == "1600x900")
						out << 1600 << ' ' << 900 << std::endl;
					else if (resolutionSelected == "1920x1080")
						out << 1920 << ' ' << 1080 << std::endl;
					else
						out << 1600 << ' ' << 900 << std::endl;

                    out.close();
				}

				for (auto it : resolutions)
				{
					if (it.isButtonClicked(mousePosition))
					{
						resolutionSelected = it.getText();
					}
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

	for (auto& it : resolutions)
	{
		it.update(mousePosition);
	}
}

void Settings::render(sf::RenderTarget* window)
{
	fps.render(window);
	antialiasing.render(window);
	apply.render(window);

	for (auto it : resolutions)
	{
		it.render(window);
	}
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

	for (unsigned short it=0;it<str_resolutions.size();it++)
	{
		Button button = Button(sf::Vector2f(200, 54), sf::Vector2f(assetsManager.getResolution().width * 0.84, assetsManager.getResolution().height * 0.06*(it+1)));
		button.setDefaultColor(sf::Color(50, 50, 50));
		button.setText(&assetsManager.getFont("Rajdhani-Regular.ttf"), str_resolutions[it]);
		button.setCharSize(25);
		button.centerText();
		button.setBorder(1);
	
		resolutions.push_back(button);
	}
}
