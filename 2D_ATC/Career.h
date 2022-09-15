#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "Input.h"
#include <fstream>

class Career
{
public:
	Career();

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void LoadCareer();
	void CreateCareer();

	void HandleClick();
	void HandleInput(unsigned unicode);

	bool isCareerCreated();

	bool drawLoadCareer;
	bool drawCreateCareer;

private:
	void initSounds();
	void initButtons();
	void initFonts();
	void initInputs();

	bool careerCreated;

	sf::Font comfortaa;
	sf::SoundBuffer buttonClickBuffer;
	sf::Sound buttonClickSound;
	sf::Vector2i mousePosition;

	Input playerName;
	Button cancelButton;
	Button submitButton;

	std::ofstream out;
};

