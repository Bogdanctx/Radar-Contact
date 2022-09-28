#pragma once

#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "Input.h"
#include "AssetsManager.h"

#define FLAGS 1

class Career
{
public:
	Career();
	Career(AssetsManager* assetsManager);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void LoadCareer();

	void HandleClick();
	void HandleInput(unsigned unicode);

	bool isCareerCreated();

	bool drawCreateCareer;

	std::string selectedMap;
	std::string _playerName;
	std::string atcPosition;

private:
	void initSounds();
	void initButtons();
	void initInputs();
	void initFlags();
	void initText();

	void setFlag(unsigned flagId);

	bool careerCreated;

	short flagIndex;
	std::string flags[FLAGS] = {
		"romania"
	};

	AssetsManager* assetsManager;

	sf::Sound buttonClickSound;
	sf::Vector2i mousePosition;

	sf::Text countrySelectedInfo;

	sf::Sprite flagsSprite[FLAGS];
	sf::Texture flagTexture;

	Input playerName;

	Button cancelButton;
	Button submitButton;

	std::ofstream out;
	std::ifstream in;
};

