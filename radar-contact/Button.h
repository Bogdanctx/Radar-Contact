#pragma once

#include <SFML/Graphics.hpp>

class Button
{
public:
	Button();
	Button(sf::Vector2f size, sf::Vector2f position);

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void setText(sf::Font* font, sf::String string);
	void setDefaultColor(sf::Color color);
	void setHoverColor(sf::Color color);
	void setBorder(float thickness, sf::Color color = sf::Color::White);
	void centerText();

	void setCharSize(unsigned short size);

	void checkMouseHover();

	bool isButtonClicked(sf::Vector2i mousePosition);

private:
	sf::Vector2i mousePosition;

	sf::RectangleShape buttonBody;
	sf::Text buttonText;

	sf::Color defaultColor;
	sf::Color hoverColor;
};