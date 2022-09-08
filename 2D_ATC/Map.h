#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Map
{
public:
	Map();

	void update();
	void render(sf::RenderTarget* window);
	void GenerateNewMap();

private:

	std::vector<std::string>maps;

	sf::Texture mapTexture;
	sf::Sprite mapSprite;
};

