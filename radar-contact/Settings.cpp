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

	}
}

void Settings::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	fps.update(mousePosition);
}

void Settings::render(sf::RenderTarget* window)
{
	fps.render(window);
	apply.render(window);
}

void Settings::initObjects()
{
	fps.setSize(300, 12);
	fps.setPosition(sf::Vector2f(400, 100));
	fps.setBounds(10, 60);
	fps.setFont(&assetsManager.getFont("Rajdhani-Regular.ttf"));
	fps.setName("FPS", 20);

	apply = Button(sf::Vector2f(150, 50), sf::Vector2f(400, WINDOW_HEIGHT - 200));
	apply.setDefaultColor(sf::Color(50, 50, 50));
	apply.setText(&assetsManager.getFont("Rajdhani-Regular.ttf"), "APPLY");
	apply.setCharSize(30);
	apply.centerText();

}