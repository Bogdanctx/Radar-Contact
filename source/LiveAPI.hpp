#pragma once

#include <nlohmann/json.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Region.hpp"

class LiveAPI {
public:
    explicit LiveAPI(const Region& region) : m_region(region) {}
    virtual ~LiveAPI() = default;

    virtual nlohmann::json downloadFlyingEntities();
    virtual std::string getWeatherPath();
    virtual std::vector<sf::Texture>& downloadWeatherTextures(sf::RenderWindow* window);
protected:
    Region m_region;

    std::vector<sf::Texture> m_downloadedWeatherTextures;
};
