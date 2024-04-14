//
// Created by bgd on 13.04.2024.
//

#ifndef OOP_WEATHER_H
#define OOP_WEATHER_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "ResourcesManager.h"
#include "DataAPI.h"

class Weather {
public:
    explicit Weather(ResourcesManager &resourcesManager, const std::string region);
    ~Weather() = default;

    void render(sf::RenderWindow *window);
public:
    void fetchWeatherImages();

    std::vector<std::pair<float, float>> m_tiles;
    std::vector<sf::Texture> m_textures;
    std::vector<sf::Sprite> m_sprites;

    ResourcesManager m_resourcesManager;
    const std::string m_selectedRegion;
};


#endif //OOP_WEATHER_H
