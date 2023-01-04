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

	Button apply;
private:
	void initObjects();

	AssetsManager assetsManager;

	Slider fps;
	Slider antialiasing;

	sf::Vector2i mousePosition;

	std::string resolutionSelected;
	std::vector<std::string>str_resolutions = { "1024x576", "1280x720", "1366x768", "1600x900", "1920x1080" };
	std::vector<Button>resolutions;
};

