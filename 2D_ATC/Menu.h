#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Menu.h"
#include "Settings.h"
#include "Career.h"

#include "Button.h"
#include "AssetsManager.h"

class Menu
{
public:
	Menu();

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void HandleClick();
	void HandleInput(unsigned unicode);

	bool drawMenu = true;

	Career career;
	Settings settingsTab;

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

	Button continueCareer;
	Button newCareer;
	Button settingsButton;
};

