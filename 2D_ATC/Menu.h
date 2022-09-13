#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Menu.h"
#include "Settings.h"
#include "Career.h"

#include "Button.h"

class Menu
{
public:
	Menu();

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void HandleClick();

	bool drawMenu = true;

private:
	void initSounds();
	void initTextures();
	void initSprites();
	void initFonts();
	void initButtons();

	sf::Vector2i mousePosition;

	sf::Font comfortaa;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::SoundBuffer buttonClickBuffer;
	sf::Sound buttonClickSound;

	Career career;
	Settings settingsTab;

	Button continueCareer;
	Button newCareer;
	Button settingsButton;
};

