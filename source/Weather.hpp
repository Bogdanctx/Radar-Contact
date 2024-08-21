#pragma once

#include <SFML/Graphics.hpp>

#include <utility>

class Weather {
public:
    void render(sf::RenderWindow *window);
    void updateImages(const std::vector<sf::Texture>& textures, const std::vector<float>& regionBoundaries,
                            const std::vector<std::pair<float, float>>& tiles);

    std::vector<sf::Sprite>& getSprites();

    static int getPixelColor(const sf::Sprite& sprite, sf::Vector2i position);
public:
    enum RainDanger {
        Yellow,
        Blue,
        Red,
        Pink,
        Clear
    };

private:
    const std::vector<std::pair<float, float>> m_tiles;
    std::vector<sf::Texture> m_textures;
    std::vector<sf::Sprite> m_sprites;
};
