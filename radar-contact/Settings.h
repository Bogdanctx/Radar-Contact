#pragma once

#include <fstream>

#include <SFML/Graphics.hpp>

#include "AssetsManager.h"
#include "Slider.h"
#include "Button.h"
#include "Constants.h"

class Settings
{
public:
	Settings();
	Settings(AssetsManager assetsManager);

	void processEvents(sf::Event event);
	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	bool isActive;
	bool settingsApplied;

	Slider fps;
	Slider antialiasing;

private:
	void initObjects();

	AssetsManager assetsManager;

	Button apply;


	sf::Vector2i mousePosition;
};

