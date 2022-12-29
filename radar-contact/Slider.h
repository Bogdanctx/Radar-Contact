#pragma once

#include <SFML/Graphics.hpp>
#include "Math.h"

class Slider
{
public:
	Slider();

	void processEvents(sf::Event event);
	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);

	void setPosition(sf::Vector2f position);
	void setSize(int length, float radius);

	void setLineColor(sf::Color color);

	void setName(const std::string name, unsigned short size);

	void setFont(sf::Font* font);

	void setBounds(int min, int max);

	int sliderValue;

private:
	sf::Vector2i mousePosition;

	sf::CircleShape circle;
	sf::RectangleShape line;
	sf::Text name;
	sf::Text value;

	int min=1, max=1, sliderLength=1;
};

