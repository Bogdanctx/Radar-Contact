#pragma once

#include <nlohmann/json.hpp>
#include <vector>
#include <SFML/Graphics.hpp>

class LiveAPI {
public:
    virtual ~LiveAPI() = default;

    virtual nlohmann::json getFlyingEntities();
    virtual std::string getWeatherPath();
    virtual std::vector<sf::Texture> getWeatherTextures(sf::RenderWindow* window);
};
