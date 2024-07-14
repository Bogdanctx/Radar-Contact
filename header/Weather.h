//
// Created by bgd on 13.04.2024.
//

#ifndef OOP_WEATHER_H
#define OOP_WEATHER_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <utility>

class Weather {
public:
    enum RainDanger {
        Yellow,
        Blue,
        Red,
        Pink,
        Clear
    };

public:
    Weather();

    void render(sf::RenderWindow *window);
    void fetchWeatherImages(sf::RenderWindow *window);

    int getPixelColor(sf::Image image, sf::Vector2f spritePosition, sf::Vector2i position);

    std::vector<sf::Sprite>& getSprites() {
        return m_sprites;
    }

public:
    std::vector<std::pair<float, float>> m_tiles;
    std::vector<sf::Texture> m_textures;
    std::vector<sf::Sprite> m_sprites;
};


#endif //OOP_WEATHER_H