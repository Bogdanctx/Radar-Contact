#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"

class Career
{
public:
	Career();

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void LoadCareer();
	void CreateCareer();

	void HandleClick();

	bool draw;

private:
	void initSounds();
	void initButtons();
	void initFonts();

	sf::Font comfortaa;

	sf::SoundBuffer buttonClickBuffer;
	sf::Sound buttonClickSound;

	Button cancelButton;
	sf::Vector2i mousePosition;
};

