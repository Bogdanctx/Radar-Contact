#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "AssetsManager.h"

class ContinueGame
{
public:
	ContinueGame();
	ContinueGame(AssetsManager assetsManager);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);
	
	void HandleClick();

	bool draw;
	short option; // 1->tower, 2->radar
private:
	void initButtons();
	void initSounds();

	sf::Vector2i mousePosition;
	sf::Sound buttonClickSound;

	Button playTower;
	Button playRadar;
	Button cancel;
	AssetsManager assetsManager;
};

