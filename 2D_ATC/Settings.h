#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "AssetsManager.h"

class Settings
{
public:
	Settings();
	Settings(AssetsManager* assetsManager);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void HandleClick();

	bool draw;

private:
	void initSounds();
	void initButtons();

	sf::Font comfortaa;

	sf::Sound buttonClickSound;

	Button applyButton;
	sf::Vector2i mousePosition;

	AssetsManager* assetsManager;
};

