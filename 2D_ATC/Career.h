#pragma once

#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "Input.h"

#define FLAGS 1

class Career
{
public:
	Career();

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
	void initFonts();
	void initInputs();
	void initFlags();
	void initText();

	void setFlag(unsigned flagId);

	bool careerCreated;

	short flagIndex;
	std::string flags[FLAGS] = {
		"romania"
	};

	sf::Font comfortaa;
	sf::SoundBuffer buttonClickBuffer;
	sf::Sound buttonClickSound;
	sf::Vector2i mousePosition;

	sf::Text countrySelectedInfo;

	sf::Sprite flagsSprite[10];
	sf::Texture flagTexture;

	Input playerName;
	Button cancelButton;
	Button submitButton;

	std::ofstream out;
	std::ifstream in;
};

