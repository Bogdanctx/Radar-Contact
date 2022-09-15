#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Map
{
public:
	Map();

	void update(sf::Vector2i mousePosition);
	void render(sf::RenderTarget* window);
	
	void GenerateMap(std::string map);

private:

	std::vector<std::string>maps;

	sf::Texture mapTexture;
	sf::Sprite mapSprite;
	sf::Vector2i mousePosition;
};