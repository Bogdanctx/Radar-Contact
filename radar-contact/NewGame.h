#pragma once

#include <SFML/Graphics.hpp>
#include "AssetsManager.h"
#include "Button.h"

class NewGame
{
public:
	NewGame();
	NewGame(AssetsManager assetsManager);

	void render(sf::RenderTarget* window);
	void update(sf::Vector2i mousePosition);

	void HandleClick();

	bool draw;
	bool applyGame;

private:
	void initButtons();
	void initSounds();
	void initFlags();
	void initText();

	sf::Vector2i mousePosition;
	sf::Sound buttonClickSound;
	sf::Text countrySelected;

	AssetsManager assetsManager;

	Button cancel;
	Button apply;

	struct Flag {
		public:
			Flag(sf::Texture *texture, sf::Vector2f position, sf::Font *font, std::string name);
	
			sf::Sprite sprite;
			sf::Texture* texture;
			sf::Text text;
			std::string country;
	};
	std::vector<Flag>flags;
};