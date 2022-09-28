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
	Menu(AssetsManager *assetsManager);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void HandleClick();
	void HandleInput(unsigned unicode);

	bool drawMenu = true;

	Career career;
	Settings settingsTab;

private:
	void initSounds();
	void initSprites();
	void initButtons();
	void initObjects();

	AssetsManager *assetsManager;

	sf::Vector2i mousePosition;

	sf::Sprite backgroundSprite;

	sf::Sound buttonClickSound;

	Button continueCareer;
	Button newCareer;
	Button settingsButton;
};

