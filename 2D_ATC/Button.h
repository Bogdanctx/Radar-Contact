#pragma once

#include <SFML/Graphics.hpp>

class Button
{
public:
	Button();

	void update();
	void render(sf::RenderTarget* window);

	void setSize(sf::Vector2f size);
	void setText(sf::Font *font, sf::String string);
	void setTextInMiddle();
	void setPosition(sf::Vector2f position);
	void setDefaultColor(sf::Color color);
	void setBackgroundColor(sf::Color color);
	void setBorderColor(sf::Color color);
	void setBorderThickness(float thickness);

	void CheckMouseHover(sf::Vector2i mousePosition);

	bool isButtonClicked(sf::Vector2i mousePosition);

	sf::RectangleShape buttonBody;
	sf::Text buttonText;

private:
	sf::Color defaultColor;
	sf::Color hoverColor;
};