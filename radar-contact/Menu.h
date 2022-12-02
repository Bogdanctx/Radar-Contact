#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Button.h"
#include "AssetsManager.h"
#include "ContinueGame.h"
#include "NewGame.h"

class Menu
{
public:
	Menu();
	Menu(AssetsManager assetsManager);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget *window);

	void HandleClick();
	void HandleInput(unsigned short unicode);

	bool draw;

	ContinueGame continueGame;
	NewGame newGame;

private:
	void initSounds();
	void initSprites();
	void initButtons();
	void initObjects();

	AssetsManager assetsManager;

	sf::Vector2i mousePosition;

	sf::Sprite backgroundSprite;

	sf::Sound buttonClickSound;

	Button b_continueGame;
	Button b_newGame;
};

