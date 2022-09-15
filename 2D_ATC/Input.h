#pragma once

#include <SFML/Graphics.hpp>

class Input
{
public:
	Input();

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);
	void setBackgroundColor(sf::Color color);
	void setBorderColor(sf::Color color);
	void setBorderThickness(float thickness);
	void setMaxChars(unsigned max);

	void setInputDescription(std::string text);
	void setCharactersSize(unsigned size);
	
	void HandleInput(unsigned unicode);

	std::string GetInputData();

private:
	void initFonts();
	void initTexts();

	unsigned maxChars;

	std::string inputDataString;
	sf::Vector2i mousePosition;
	sf::Font merriweather;
	sf::Text inputDescription;
	sf::Text inputDataText;
	sf::RectangleShape inputBody;
};

