#pragma once

#include "LiveAPI.hpp"

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

class MockAPI : public LiveAPI {
public:
    nlohmann::json getFlyingEntities() override;
    std::string getWeatherPath() override;
    std::vector<sf::Texture> getWeatherTextures(sf::RenderWindow* window) override;
};
