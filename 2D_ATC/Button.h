#pragma once

#include <SFML/Graphics.hpp>

class Button
{
public:
	Button();
	Button(sf::Vector2f size, sf::Vector2f position);
	~Button();

	void update();
	void render(sf::RenderTarget* window);

	void SetText(sf::Font *font, sf::String string);
	void SetDefaultColor(sf::Color color);
	void SetHoverColor();
	void SetBorder(float thickness, sf::Color color = sf::Color::White);
	void CenterText();

	void CheckMouseHover(sf::Vector2i mousePosition);

	bool isButtonClicked(sf::Vector2i mousePosition);

	sf::RectangleShape buttonBody;
	sf::Text buttonText;

private:
	sf::Color defaultColor;
	sf::Color hoverColor;
};