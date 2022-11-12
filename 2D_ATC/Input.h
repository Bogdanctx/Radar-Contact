#pragma once

#include <SFML/Graphics.hpp>
#include "AssetsManager.h"

class Input
{ 
public:
	Input();
	Input(AssetsManager assetsManager, sf::Vector2f size, sf::Vector2f position);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);
	void HandleInput(unsigned short unicode);

	void SetBorder(float thickness, sf::Color color);
	void SetDescription(const std::string text);
	void SetMaxLength(const unsigned short max);
	void SetCharsSize(const unsigned short size);
	void SetBackgroundColor(sf::Color color);

	std::string GetInput();

private:
	AssetsManager assetsManager;

	sf::RectangleShape inputBody;
	sf::Text inputDescription;
	sf::Text inputDataText;
	sf::Vector2i mousePosition;
	std::string inputDataString;

	unsigned short maxLength;
};

