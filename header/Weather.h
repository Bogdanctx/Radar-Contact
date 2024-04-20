//
// Created by bgd on 13.04.2024.
//

#ifndef OOP_WEATHER_H
#define OOP_WEATHER_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "DataAPI.h"
#include "ResourcesManager.h"

class Weather {
public:
    Weather() = default;
    explicit Weather(const std::string &region);
    ~Weather() = default;

    void render(sf::RenderWindow *window);
    void fetchWeatherImages(sf::RenderWindow *window);
public:
    std::vector<std::pair<float, float>> m_tiles;
    std::vector<sf::Texture> m_textures;
    std::vector<sf::Sprite> m_sprites;

    const std::string m_selectedRegion;
};


#endif //OOP_WEATHER_H