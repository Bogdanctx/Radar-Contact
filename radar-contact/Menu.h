#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "AssetsManager.h"
#include "Button.h"
#include "Constants.h"
#include "Settings.h"
#include "Play.h"

class Menu
{
public:
	Menu();
	Menu(AssetsManager assetsManager);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget *window);

	void processEvents(sf::Event event);

	bool isActive;

	Settings __settings;
	Play __play;

private:
	void initSprites();
	void initTexts();
	void initShapes();
	void initButtons();
	void initObjects();

	AssetsManager assetsManager;

	Button play;
	Button settings;

	sf::Sprite background;
	sf::RectangleShape leftCard;
	sf::Text gameTitle;

	sf::Vector2i mousePosition;
};

