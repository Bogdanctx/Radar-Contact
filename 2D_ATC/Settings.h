#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"

class Settings
{
public:
	Settings();

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void HandleClick();

	bool draw;

private:
	void initSounds();
	void initButtons();
	void initFonts();

	sf::Font comfortaa;

	sf::SoundBuffer buttonClickBuffer;
	sf::Sound buttonClickSound;

	Button applyButton;
	sf::Vector2i mousePosition;
};

